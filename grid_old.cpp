/*
 * @kangkang,假设图像为线性畸变
 */
#include "grid.h"

using namespace std;
using namespace cv;
using namespace GT;

double grid::modifyGrid(vector< vector< pair<float, float> > >  &gd, map< pair<float, float>, pair<float, float> > &peak, vector< vector< bool > > &flag){
double counter = 0; 
int i = 0;       
	for(vector< vector< pair<float, float> > >::iterator it = gd.begin(); it != gd.end(); it++, i++){  
        int j = 0;      
	    for(vector< pair<float, float> >::iterator itt = (*it).begin(); itt != (*it).end(); itt++, j++){ 
             float x = (*itt).first;
             float y = (*itt).second;  
             for(float k1 = x - rc; k1 <= x + rc; k1 += precision){      
                 for(float k2 = y - rc; k2 <= y + rc; k2 += precision){
                     map< pair<float, float>, pair<float, float> >::iterator mit = peak.find(make_pair(round(k1), round(k2)));                             
                     if(mit != peak.end())
                                       {counter ++; flag[i][j] = true;gd[i][j] = peak[make_pair(round(k1), round(k2))]; break;} 
                     } 
                     if(flag[i][j] == true){break;}
             }          
         }                       	
     }	           
    return counter; 
}

double grid::alignGrid(vector< vector< bool > > &flag, vector< vector< bool > > & tflag, vector< vector< pair<float, float> > > &pr){
     double snr;
     double min, sum, sumSqr;
     double avg, stdDev, signal; 
     
     min = sum = sumSqr = 0;
     
     
     //*/////////////////////////////////////////////////////////////////////////
     double peaknumber = 0, deletion = 0;
     
     for(int i = 0; i < flag.size(); i++){
        for(int j = 0; j < flag[i].size(); j++){
                if(flag[i][j] || tflag[i][j]){
                              peaknumber ++;                              
                }        
                if((!flag[i][j] && !tflag[i][j])){
                              deletion ++;              
                }
        }     
     }
     snr = 1 / (deletion + 1e-100);
     //*////////////////////////////////////////////////////////////////////////
     
     
     /*/////////////////////////////////////////////////////////////////////////
     double snrrow = 0;
     sum = 0;
     sumSqr = 0;
     min = 1e100;
     for(int i = 0; i < flag.size(); i++){
        double temp = 0;
        for(int j = 0; j < flag[i].size(); j++){
             if(!flag[i][j]){
                    temp++;       
             }   
        }
        sum += temp;
        sumSqr += temp * temp;
        if(temp < min) min = temp;
     }
     sum -= min;
     sumSqr -= (min * min);
     avg = sum / (flag.size() - 1);
     stdDev = sqrt((sumSqr - sum * sum / (flag.size() - 1)) / (flag.size() - 2));
     signal = avg - min; 
     if(stdDev > 0)
               snrrow = signal / stdDev;
     else
               snrrow = 0;
     
     
     double snrcol = 0;
     sum = 0;
     sumSqr = 0;
     min = 1e100;
     for(int i = 0; i < flag[0].size(); i++){
        double temp = 0;
        for(int j = 0; j < flag.size(); j++){
             if(!flag[j][i]){
                    temp++;       
             }   
        }
        sum += temp;
        sumSqr += temp * temp;
        if(temp < min) min = temp;
     }
     sum -= min;
     sumSqr -= (min * min);
     avg = sum / (flag[0].size() - 1);
     stdDev = sqrt((sumSqr - sum * sum / (flag[0].size() - 1)) / (flag[0].size() - 2));
     signal = avg - min; 
     if(stdDev > 0)
               snrcol = signal / stdDev;
     else
               snrcol = 0; 
     
     snr = snrrow + snrcol;
     //*/////////////////////////////////////////////////////////////////////////
     
     return snr;
}

vector< vector< vector< pair<float, float> > > > grid::fit(image &im, vector< vector< pair<int, int> > > &ckp, vector< pair<float, float> > &peak, vector< vector< vector< bool > > > &outflag, vector<double> &mr, vector<vector<vector<bool> > >& tpf, bool istpf){
	 vector< vector< vector< pair<float, float> > > > resPosition;
         int tcn = 0;
         map< pair<float, float>, pair<float, float> > fpeak;
         for(vector< pair<float, float> >::iterator itp = peak.begin(); itp != peak.end(); itp++){
                     int x = round((*itp).first);
                     int y = round((*itp).second); 
                     fpeak[make_pair(x, y)] = *itp;                    
         }
         
for(vector< vector< pair<int, int> > >::iterator it = ckp.begin(); it != ckp.end(); it++, tcn++){
 
         //cout<<"Field "<<tcn<<endl; 
      
      vector< vector< pair<float, float> > > pr;
      vector< vector< bool > > flag;
      double totalNumber = 0;  
 
    	float maxx = (*it)[2].first > (*it)[3].first ? (*it)[2].first : (*it)[3].first;  
    	float minx = (*it)[0].first < (*it)[1].first ? (*it)[0].first : (*it)[1].first;  
    	float maxy = (*it)[1].second > (*it)[3].second ? (*it)[1].second : (*it)[3].second;  
    	float miny = (*it)[0].second < (*it)[2].second ? (*it)[0].second : (*it)[2].second;	
    	
    	for(vector< pair<float, float> >::iterator itp = peak.begin(); itp != peak.end(); itp++){
                    if((*itp).first >= minx - rg && (*itp).first <= maxx + rg && (*itp).second >= miny - rg && (*itp).second <= maxy + rg)
                                 totalNumber++;
        }

    	
    double maxRate = -1;
    double minSNR = 1e100;
    
  for(int cs = 0; cs < FN; cs++){
     int good = 0;	
     for(int k = 0 - rg; k <= rg; k++){
      float x1 = (*it)[0].first;
      float y1 = (*it)[0].second;
      float x2 = (*it)[1].first;
      float y2 = (*it)[1].second;
      float x3 = (*it)[2].first;
      float y3 = (*it)[2].second;
      float x4 = (*it)[3].first;
      float y4 = (*it)[3].second;
     
      switch(cs){
        case 0:
             x1 += k;break;
        case 1:
             y1 += k;break;
        case 2:
             x2 += k;break;
        case 3:
             y2 += k;break;
        case 4:
             x3 += k;break;
        case 5:
             y3 += k;break;
        case 6:
             x4 += k;break;
        case 7:
             y4 += k;break;
      }

      
      vector< vector< pair<float, float> > > prt;
      for(int l1 = 0; l1 < dnbx[tcn / rowNum]; l1++){
              vector< pair<float, float> > ptt;
              float xb = x1 + (x3 - x1) * 1.0 / (dnbx[tcn / rowNum] - 1) * l1;
              float yb = y1 + (y3 - y1) * 1.0 / (dnbx[tcn / rowNum] - 1) * l1;
              float xe = x2 + (x4 - x2) * 1.0 / (dnbx[tcn / rowNum] - 1) * l1;
              float ye = y2 + (y4 - y2) * 1.0 / (dnbx[tcn / rowNum] - 1) * l1;
              for(int l2 = 0; l2 < dnby[tcn % colNum]; l2++){                    
                    float x = xb + (xe - xb) * 1.0 / (dnby[tcn % colNum] - 1) * l2;
                    float y = yb + (ye - yb) * 1.0 / (dnby[tcn % colNum] - 1) * l2;
                    ptt.push_back(make_pair(x, y));                                                       
              }        
              prt.push_back(ptt);
      }       
 
      //用于确定尺寸/////////////////////////////////////////// 
      //cout<<minx<<"\t"<<maxx<<"\t"<<miny<<"\t"<<maxy<<endl;      
      //cout<<dnbx[tcn / rowNum]<<"\t"<<dnby[tcn % colNum]<<endl;
          
    
    vector< vector< bool > > tflag(prt.size(), vector< bool >(prt[0].size(), false));
    
    double rate = modifyGrid(prt, fpeak, tflag) / totalNumber;////////////////////////////////////////////    


    if(istpf){
          if(rate > maxRate){
            maxRate = rate;
            pr = prt;
            flag = tflag;  
            good = k;      
          }              
    }else{
          
          double snr = alignGrid(tflag, tpf[tcn], prt);    
          if(/*snr < minSNR &&*/ rate > maxRate){
            maxRate = rate;
            //minSNR = snr;
            pr = prt;
            flag = tflag;  
            good = k;      
          }
    }


   }
      switch(cs){
        case 0:
             (*it)[0].first += good;break;
        case 1:
             (*it)[0].second += good;break;
        case 2:
             (*it)[0].first += good;break;
        case 3:
             (*it)[0].second += good;break;
        case 4:
             (*it)[0].first += good;break;
        case 5:
             (*it)[0].second += good;break;
        case 6:
             (*it)[0].first += good;break;
        case 7:
             (*it)[0].second += good;break;
      }   
      
      //cout<<"Grid "<<cs<<":"<<"\t"<<good<<endl;
  }
     
    cout<<"Rate:"<<maxRate<<endl;
    //cout<<"SNR:"<<minSNR<<endl;                         
    
    
    if(istpf){
            tpf.push_back(flag);                    
    }
    

    outflag.push_back(flag);
    resPosition.push_back(pr);
}
	return resPosition;
}

