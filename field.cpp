/*
 * @kangkang,查找cross,可以通过二值图像十字查找，进一步精确查找，可以根据check上的dnb来求坐标均值定位 
 */
#include "field.h"

using namespace std;

vector< vector< pair<int, int> > > field::getField2(image& im, vector< vector< pair<int, int> > > &pos, vector< vector<int> > &cxy){
       vector< vector<pre> > I = im.getImage();
       int row = I.size();
       int col = I[0].size();
       vector< vector< pair<int, int> > > out;
       
       int offsetx = 0, offsety = 0;
       double min = 1e100;
       
       for(int k1 = 0 - rg2; k1 <= rg2; k1++){
               double sum = 0;
               for(int m1 = 0; m1 < cxy[0].size(); m1++){
                       int x = cxy[0][m1] + k1;
                       if(x - r2 / 2> 0 && x + r2 / 2 < I.size()){ 
                            for(int n = x - r2 / 2; n <= x + r2 / 2; n++){
                                    for(int y = 0; y < I[0].size(); y++){
                                            sum += I[n][y];        
                                    }        
                            }
                       }       
               }      
               if(sum < min){
                      min = sum;
                      offsetx = k1;       
               }  
       }
       
       for(int k2 = 0 - rg2; k2 <= rg2; k2++){
               double sum = 0;
               for(int m2 = 0; m2 < cxy[1].size(); m2++){
                       int y = cxy[1][m2] + k2;
                       if(y - r2 / 2 > 0 && y + r2 / 2 < I[0].size()){ 
                            for(int n = y - r2 / 2; n <= y + r2 / 2; n++){
                                    for(int x = 0; x < I.size(); x++){
                                            sum += I[x][n];        
                                    }        
                            }
                       }       
               }  
               if(sum < min){
                      min = sum;
                      offsety = k2;       
               }                      
       }
       
       
       cout<<"Offset:"<<offsetx<<"\t"<<offsety<<endl;
       
       cxy.clear();////////////////////////////////////////////////////////////
       
for(int i = 0; i < pos.size(); i++){
        
                vector< pair<int, int> > position;
                pair<int, int> p1 = make_pair(pos[i][0].first + offsetx, pos[i][0].second + offsety);
                pair<int, int> p2 = make_pair(pos[i][1].first + offsetx, pos[i][1].second + offsety);
                pair<int, int> p3 = make_pair(pos[i][2].first + offsetx, pos[i][2].second + offsety);
                pair<int, int> p4 = make_pair(pos[i][3].first + offsetx, pos[i][3].second + offsety);  
                
                position.push_back(p1);
                position.push_back(p2);
                position.push_back(p3);
                position.push_back(p4); 
                
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
                p1 = make_pair(optx + r / 2 + 1, opty + r / 2 + 1); 
                
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
                p2 = make_pair(optx + r / 2 + 1, opty - r / 2 - 1); 
 
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
                p3 = make_pair(optx - r / 2 - 1, opty + r / 2 + 1); 
                
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
                p4 = make_pair(optx - r / 2 - 1, opty - r / 2 - 1); 
                                                      
                             
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
                
                ////////////////////////////////////////////////////////////////
                vector<int> tp;
                tp.push_back(p1.first);
                tp.push_back(p1.second);                
                cxy.push_back(tp);
                tp.clear();
                tp.push_back(p2.first);
                tp.push_back(p2.second);                
                cxy.push_back(tp);
                tp.clear();
                tp.push_back(p3.first);
                tp.push_back(p3.second);                
                cxy.push_back(tp);
                tp.clear();
                tp.push_back(p4.first);
                tp.push_back(p4.second);                
                cxy.push_back(tp);
                ////////////////////////////////////////////////////////////////                                               
                                     
//*/////////////////////////////////////////////////////////////////////////////////////              
                out.push_back(position);             
}
        return out;
}

double field::winSum(vector< vector<pre> > &v, int x, int y , int downx, int upx, int downy, int upy){
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

