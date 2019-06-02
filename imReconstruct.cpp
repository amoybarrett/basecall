/*
 * @kangkang, DNB或者cluster的简单重构,考虑等峰情况,4联通或8联通 
 */
 
 #include "imReconstruct.h"
 
 using namespace std;
 
 vector< pair<float, float> > imReconstruct::getPeakPosition(image &im, std::vector< std::vector<long long> > &fl, bool lt){
       vector< pair<float, float> > out;
       vector< vector<pre> > v = im.getImage();
       vector< vector<pre> > noise = im.getNoise();
       double thd = 0;
       double counter = 0;
       
       
       for(long long i = 0; i < v.size(); i++){
               for(long long j = 0; j < v[i].size(); j++){
                   bool flag = true;
                   if(fl[i][j] == 0) continue;
                   for(int k1 = i - 1; k1 <= i + 1; k1++){
                                for(int k2 = j - 1; k2 <= j + 1; k2 ++){
                                    if(k1 == i && k2 == j) continue;
                                    if(k1 >= 0 && k1 < v.size() && k2 >= 0 && k2 < v[i].size()){   
                                    if(lt){                                                           
                                             if(v[k1][k2] >= v[i][j]){
                                                           flag = false;
                                                           break;              
                                             }  
                                             if((k1 == i || k2 == j)){
                                                    if(fl[k1][k2] == 0){
                                                                  flag = false;
                                                                  break;              
                                                    }
                                             }
                                    }else{                                          
                                        if((k1 == i || k2 == j)){    
                                             if(v[k1][k2] >= v[i][j] || fl[k1][k2] == 0){
                                                           flag = false;
                                                           break;              
                                             } 
                                        } 
                                     } 
                                                                                                                                 
                                     }     
                                }             
                                if(!flag){break;}
                   }
                   
                   if(flag){
                            out.push_back(make_pair(i, j));
                   }   
                    
               }        
       }                         
       
       return out;
 }
