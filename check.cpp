/*
 * @kangkang 
 */
#include "check.h"

using namespace std;

vector< vector< pair<int, int> > > check::getCheck2(image &im, vector< vector<int> > &cxy){
        vector< vector< pair<int, int> > > out;
        vector< vector< pair<int, int> > > pos;
        vector<double> cs = im.colSum();
        vector<double> rs = im.rowSum();
        
        vector< vector<pre> > I = im.getImage(); 

        vector<int> x;
        vector<int> y;
        
        vector<double> xrs;
        vector<double> yrs;
        
        for(int i = r2 / 2; i < im.getHeight() - r2 / 2; i++){
              double temp = 0;
              for(int j = i - r2 / 2; j < i + r2 / 2; j++){
                      temp += rs[j];        
              }  
              xrs.push_back(temp);
        }

        for(int i = r2 / 2; i < im.getWidth() - r2 / 2; i++){
              double temp = 0;
              for(int j = i - r2 / 2; j < i + r2 / 2; j++){
                      temp += cs[j];        
              }  
              yrs.push_back(temp);
        }
        
        for(int i = 0; i < rowNum; i++){
               double min = 1e100;
               int mp;
               for(int j = rg; j < xrs.size() - rg; j++){
                     if(min > xrs[j]){
                            min = xrs[j];
                            mp = j;       
                     }          
               }  
               x.push_back(mp + r2 / 2);
               int down = mp - rg < 0 ? 0 : mp - rg;
               int up = mp + rg > xrs.size() - 1 ? xrs.size() - 1 : mp + rg;
               for(int j = down; j <= up; j++){
                       xrs[j] = 1e100;        
               }      
        }
        
        for(int i = 0; i < colNum; i++){
               double min = 1e100;
               int mp;
               for(int j = rg; j < yrs.size() - rg; j++){
                     if(min > yrs[j]){
                            min = yrs[j];
                            mp = j;       
                     }          
               }  
               y.push_back(mp + r2 / 2);
               int down = mp - rg < 0 ? 0 : mp - rg;
               int up = mp + rg > yrs.size() - 1 ? yrs.size() - 1 : mp + rg;
               for(int j = down; j <= up; j++){
                       yrs[j] = 1e100;        
               }      
        }        
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        
         for(int i = 0; i < rowNum; i++){
                 cout<<x[i]<<"\t";        
         }
         cout<<endl;
         for(int i = 0; i < colNum; i++){
                 cout<<y[i]<<"\t";        
         }
         cout<<endl;
         cxy.push_back(x);
         cxy.push_back(y);
         
/*         
for(int i = 0; i < pox.size() - 1; i++){
        for(int j = 0; j < poy.size() - 1; j++){  
            vector< pair<int, int> > tp; 
            pair<int, int> p1;
            pair<int, int> p2;
            pair<int, int> p3;
            pair<int, int> p4;       
            int min1=10000;
            int min2=10000;
            int min3=10000;
            int min4=10000; 
              
            for(int t1 = 0; t1 < I.size(); t1++){
                    for(int t2 = 0; t2 < I[t1].size(); t2++){
                            
                            if(abs(t2 - poy[j][t1]) + abs(t1 - pox[i][t2]) < min1){
                                  min1 = abs(t2 - poy[j][t1]) + abs(t1 - pox[i][t2]);
                                  p1 = make_pair(t1, t2);
                            }
                            if(abs(t2 - (poy[j+1][t1] - r - 1)) + abs(t1 - pox[i][t2]) < min2){
                                  min2 = abs(t2 - (poy[j+1][t1] - r - 1)) + abs(t1 - pox[i][t2]);
                                  p2 = make_pair(t1, t2);
                            }
                            if(abs(t2 - poy[j][t1]) + abs(t1 - (pox[i+1][t2] -r - 1)) < min3){
                                  min3 = abs(t2 - poy[j][t1]) + abs(t1 - (pox[i+1][t2] -r - 1));
                                  p3 = make_pair(t1, t2);
                            }
                            if(abs(t2 - (poy[j+1][t1] - r - 1)) + abs(t1 - (pox[i+1][t2] -r - 1)) < min4){
                                  min4 = abs(t2 - (poy[j+1][t1] - r - 1)) + abs(t1 - (pox[i+1][t2] -r - 1));
                                  p4 = make_pair(t1, t2);
                            }    
                                
                    }        
            }
            tp.push_back(p1);tp.push_back(p2);tp.push_back(p3);tp.push_back(p4);
            position.push_back(tp);
        }        
}      
*/
    
    
/////////////////////////////////////////////////////////////////////////////////         
         vector< vector<int> > pox;
         for(int i = 0; i < x.size(); i++){
                 vector<int> temp;
                 for(int j = 0; j < im.getWidth(); j++){
                         temp.push_back(x[i]);
                 }
                 pox.push_back(temp);
         }     
         vector< vector<int> > poy;
         for(int i = 0; i < y.size(); i++){
                 vector<int> temp;
                 for(int j = 0; j < im.getHeight(); j++){
                         temp.push_back(y[i]);
                 }
                 poy.push_back(temp);
         }             
        for(int i = 0; i < rowNum - 1; i++){
                for(int j = 0; j < colNum - 1; j++){
                        vector< pair<int, int> > temp;                   
                        temp.push_back(make_pair(x[i], y[j]));
                        temp.push_back(make_pair(x[i], y[j + 1]));
                        temp.push_back(make_pair(x[i + 1], y[j]));
                        temp.push_back(make_pair(x[i + 1], y[j + 1]));
                        pos.push_back(temp);        
                }        
        }
////////////////////////////////////////////////////////////////////////////////     


for(int i = 0; i < pos.size(); i++){
        
                vector< pair<int, int> > position;
                pair<int, int> p1 = make_pair(pos[i][0].first, pos[i][0].second);
                pair<int, int> p2 = make_pair(pos[i][1].first, pos[i][1].second);
                pair<int, int> p3 = make_pair(pos[i][2].first, pos[i][2].second);
                pair<int, int> p4 = make_pair(pos[i][3].first, pos[i][3].second);  
                
                //cout<<"Before:"<<endl;
                //cout<< p1.first<<"\t"<<p1.second<<endl;
                //cout<< p2.first<<"\t"<<p2.second<<endl;
                //cout<< p3.first<<"\t"<<p3.second<<endl;
                //cout<< p4.first<<"\t"<<p4.second<<endl; 
                
                int downx = 0;
                int downy = 0;
                int upx = I.size() - 1;
                int upy = I[0].size() - 1;   
                
                int optx = -1;
                int opty = -1;
                double min = 1e100;
                for(int k1 = 0 - rg; k1 <= rg; k1++){
                        for(int k2 = 0 - rg; k2 <= rg; k2++){
                                int x = p1.first + k1;
                                int y = p1.second + k2;
                                double temp = winSum(I, x, y, downx, upx, downy, upy);     
                                if(temp < min){
                                        min = temp;
                                        optx = x;
                                        opty = y;        
                                }
                        }       
                }          
                p1 = make_pair(optx, opty); 
                
                optx = -1;
                opty = -1;
                min = 1e100;
                for(int k1 = 0 - rg; k1 <= rg; k1++){
                        for(int k2 = 0 - rg; k2 <= rg; k2++){
                                int x = p2.first + k1;
                                int y = p2.second + k2;
                                double temp = winSum(I, x, y, downx, upx, downy, upy);     
                                if(temp < min){
                                        min = temp;
                                        optx = x;
                                        opty = y;        
                                }
                        }       
                }   
                p2 = make_pair(optx, opty); 
 
                optx = -1;
                opty = -1;
                min = 1e100;
                for(int k1 = 0 - rg; k1 <= rg; k1++){
                        for(int k2 = 0 - rg; k2 <= rg; k2++){
                                int x = p3.first + k1;
                                int y = p3.second + k2;
                                double temp = winSum(I, x, y, downx, upx, downy, upy);     
                                if(temp < min){
                                        min = temp;
                                        optx = x;
                                        opty = y;        
                                }
                        }       
                } 
                p3 = make_pair(optx, opty); 
                
                optx = -1;
                opty = -1;
                min = 1e100;
                for(int k1 = 0 - rg; k1 <= rg; k1++){
                        for(int k2 = 0 - rg; k2 <= rg; k2++){
                                int x = p4.first + k1;
                                int y = p4.second + k2;
                                double temp = winSum(I, x, y, downx, upx, downy, upy);     
                                if(temp < min){
                                        min = temp;
                                        optx = x;
                                        opty = y;        
                                }
                        }       
                } 
                p4 = make_pair(optx, opty); 
                                                      
                             
                //cout<<"After:"<<endl;
                //cout<< p1.first<<"\t"<<p1.second<<endl;
                //cout<< p2.first<<"\t"<<p2.second<<endl;
                //cout<< p3.first<<"\t"<<p3.second<<endl;
                //cout<< p4.first<<"\t"<<p4.second<<endl;   
 
                position.clear();
                position.push_back(p1);
                position.push_back(p2);
                position.push_back(p3);
                position.push_back(p4);
                
                out.push_back(position);
 }  

        return out;
              
}

double check::winSum(vector< vector<pre> > &v, int x, int y , int downx, int upx, int downy, int upy){
      double sum = 0; 
      double counter = 0;
      
      if(x - r / 2 < downx || x + r / 2 > upx || y - r / 2 < downy || y + r / 2 > upy)
           return 1e100;
           
      int dy = y - rd <= downy ? downy : y - rd;
      int uy = y + rd >= upy ? upy : y + rd;
      
          for(int i = x - r / 2; i <= x + r / 2; i++){
            if(i < x - ns + 1 || i > x + ns - 1)
              for(int j = dy; j<= uy; j++){
                      sum += v[i][j];
                      counter++;       
              }        
          }
          
      int dx = x - rd <= downx ? downx : x - rd;
      int ux = x + rd >= upx ? upx : x + rd;       
          
          for(int j = y - r / 2; j<= y + r / 2; j++){
            if(j < y - ns + 1 || j > y + ns - 1)
               for(int i = dx; i <= ux; i++){
                      sum += v[i][j];
                      counter++;    
              }        
          }   
                         
      return sum / counter;
}


/*
#include "readWriteTIFF.h"
int main(void){
        readWriteTIFF rwt;
        rwt.load("test_check_dnb9.tif");
        image im(rwt);
        check ck;
        ck.getCheck(im, false); 
}
*/
