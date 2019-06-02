/*
 * @kangkang,假设图像为线性畸变
 */
#include "grid.h"

using namespace std;
using namespace cv;
using namespace GT;

double grid::modifyGrid(vector< vector< pair<float, float> > >  &gd, map< pair<float, float>, pair<float, float> > &peak, vector< vector< bool > > &flag){
    vector< vector< pair<float, float> > > out = gd;
    vector< vector< pair<float, float> > > aos;
    double counter = 0; 
    int i = 0;       
	for(vector< vector< pair<float, float> > >::iterator it = gd.begin(); it != gd.end(); it++, i++){  
        int j = 0;     
        vector< pair<float, float> > os; 
	    for(vector< pair<float, float> >::iterator itt = (*it).begin(); itt != (*it).end(); itt++, j++){ 
             float x = (*itt).first;
             float y = (*itt).second; 
             pair<float, float> ost; 
             flag[i][j] = false;
             for(float k1 = x - rc; k1 <= x + rc; k1 += precision){      
                 for(float k2 = y - rc; k2 <= y + rc; k2 += precision){
                     map< pair<float, float>, pair<float, float> >::iterator mit = peak.find(make_pair(round(k1), round(k2)));                             
                     if(mit != peak.end())
                            if(abs((mit->second).first - (*itt).first) <= rg && abs((mit->second).second - (*itt).second) <= rg)
                                       {ost = make_pair((mit->second).first - (*itt).first, (mit->second).second - (*itt).second);
                                       counter ++; flag[i][j] = true;out[i][j] = peak[make_pair(round(k1), round(k2))];break;} 
                     } 
                     if(flag[i][j]){break;}
             }  
             if(!flag[i][j]){ost = make_pair(0, 0);}     
             os.push_back(ost);      
         }  
         aos.push_back(os);                     	
     }	   
    gd = out;         
    return counter; 
}

void grid::osmSample(vector< vector< pair<float, float> > >  &gd, map< pair<float, float>, pair<float, float> > &peak){

    vector< vector< bool > > af;
    vector< vector< pair<float, float> > > aos;
	for(vector< vector< pair<float, float> > >::iterator it = gd.begin(); it != gd.end(); it++){  
        vector< bool > temp;
        vector< pair<float, float> > os;     
	    for(vector< pair<float, float> >::iterator itt = (*it).begin(); itt != (*it).end(); itt++){ 
             int x = round((*itt).first);
             int y = round((*itt).second);  
             bool flag = false;
             pair<float, float> ost;
             for(int k1 = x - rc; k1 <= x + rc; k1 ++){      
                 for(int k2 = y - rc; k2 <= y + rc; k2 ++){
                     map< pair<float, float>, pair<float, float> >::iterator mit = peak.find(make_pair(k1, k2));                             
                     if(mit != peak.end())
                            if(abs((mit->second).first - (*itt).first) <= rk && abs((mit->second).second - (*itt).second) <= rk)
                                       {ost = make_pair((mit->second).first - (*itt).first, (mit->second).second - (*itt).second); flag = true; break;} 
                     } 
                     if(flag){break;}
             }  
             temp.push_back(flag); 
             if(!flag){ost = make_pair(0, 0);}     
             os.push_back(ost);  
         }                       
         af.push_back(temp);
         aos.push_back(os);	
     }	      
     
     for(int i = 0; i < gd.size(); i++){
             int di = i - FN < 0 ? 0 : i - FN;  
             int ui = i + FN > gd.size() - 1 ? gd.size() - 1 : i + FN;             
             for(int j = 0; j < gd[i].size(); j++){
                     float oi = 0, oj = 0;
                     float counter = 0;
                     int dj = j - FN < 0 ? 0 : j - FN;
                     int uj = j + FN > gd[i].size() - 1 ? gd[i].size() - 1 : j + FN;
                     for(int k1 = di; k1 <= ui; k1++){
                             for(int k2 = dj; k2 <= uj; k2++){
                                    if(af[k1][k2]){
                                        oi += aos[k1][k2].first;
                                        oj += aos[k1][k2].second;  
                                        counter ++;                        
                                    }                 
                             }        
                     }  
                     
                     oi /= (counter + 1e-100);
                     oj /= (counter + 1e-100);
                     
                     gd[i][j].first += oi;
                     gd[i][j].second += oj;     
             }        
     }  
            
}

double grid::alignGrid(vector< vector< bool > > &flag, vector< vector< bool > > & tflag, vector< vector< pair<float, float> > > &pr){
     double snr;
      
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
     snr = peaknumber / (deletion + 1e-100);
    
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
                    if((*itp).first >= minx && (*itp).first <= maxx && (*itp).second >= miny && (*itp).second <= maxy)
                                 totalNumber++;
        }

    	
    double maxRate = -1;
    double minSNR = 1e100;
    
      float x1 = (*it)[0].first;
      float y1 = (*it)[0].second;
      float x2 = (*it)[1].first;
      float y2 = (*it)[1].second;
      float x3 = (*it)[2].first;
      float y3 = (*it)[2].second;
      float x4 = (*it)[3].first;
      float y4 = (*it)[3].second;

      //边缘采用grid抽样，得到平行四边形的四个参数，然后对每个图画出固定grid 
      //细致画网格：通过找出所有check点，求解网格 
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
    
    double rate = 0;
    
    osmSample(prt, fpeak);
    osmSample(prt, fpeak);
    rate = modifyGrid(prt, fpeak, tflag) / totalNumber;

    if(istpf){
          if(rate > maxRate){////////////////////////循环遍历mr最高或平均距离最小,offsetx, offsety 
            maxRate = rate;
            pr = prt;
            flag = tflag;      
          }              
    }else{          
          double snr = alignGrid(tflag, tpf[tcn], prt);    
          if(snr < minSNR && rate > maxRate){/////////////////////循环遍历snr最高 
            maxRate = rate;
            minSNR = snr;
            pr = prt;
            flag = tflag;    
          }
    }
    
     
    //cout<<"Rate:"<<maxRate<<endl;
    //cout<<"SNR:"<<minSNR<<endl;                         
    
    
    if(istpf){
            tpf.push_back(flag);                    
    }
    

    outflag.push_back(flag);
    resPosition.push_back(pr);
}
	return resPosition;
}

