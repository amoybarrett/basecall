/*
 * @kangkang,区间概率，极大似然概率,卡方检验(属性独立条件)
 */
#include "bayescall.h"

using namespace std;

void bayescall::train(vector< vector<double> >  &v,vector< vector<double> > &noise,  vector< vector<short> > &base){
             for(long long i = 0; i < v.size(); i++){
                      vector<short> temp;
                      for(int j = prefix; j < v[i].size(); j += bsize){
                             temp.push_back(getBase(v, i, j));        
                      }         
                      base.push_back(temp);
             }
             
             bool flag = false;
             
             for(long long i = 0; i < v.size(); i++){
                      for(int j = prefix; j < v[i].size(); j += bsize){ 
                              if(!flag){
                                        maxa = mina = v[i][j];
                                        maxc = minc = v[i][j + 1];
                                        maxg = ming = v[i][j + 2];
                                        maxt = mint = v[i][j + 3];
                                        maxna = minna = noise[i][j];
                                        maxnc = minnc = noise[i][j + 1];
                                        maxng = minng = noise[i][j + 2];
                                        maxnt = minnt = noise[i][j + 3];   
                                        flag = true;                             
                              }else{
                                    
                                    if(maxa < v[i][j]){
                                            maxa = v[i][j];        
                                    }      
                                    if(mina > v[i][j]){
                                            mina = v[i][j];        
                                    }
                                    if(maxna < noise[i][j]){
                                            maxna = noise[i][j];        
                                    }
                                    if(minna > noise[i][j]){
                                             minna = noise[i][j];         
                                    }

                                    if(maxc < v[i][j + 1]){
                                            maxc = v[i][j + 1];        
                                    }      
                                    if(minc > v[i][j + 1]){
                                            minc = v[i][j + 1];        
                                    }
                                    if(maxnc < noise[i][j + 1]){
                                            maxnc = noise[i][j + 1];        
                                    }
                                    if(minnc > noise[i][j + 1]){
                                             minnc = noise[i][j + 1];         
                                    }
                                    
                                    if(maxg < v[i][j + 2]){
                                            maxg = v[i][j + 2];        
                                    }      
                                    if(ming > v[i][j + 2]){
                                            ming = v[i][j + 2];        
                                    }
                                    if(maxng < noise[i][j + 2]){
                                            maxng = noise[i][j + 2];        
                                    }
                                    if(minng > noise[i][j + 2]){
                                             minng = noise[i][j + 2];         
                                    }
                                    
                                    if(maxt < v[i][j + 3]){
                                            maxt = v[i][j + 3];        
                                    }      
                                    if(mint > v[i][j + 3]){
                                            mint = v[i][j + 3];        
                                    }
                                    if(maxnt < noise[i][j + 3]){
                                            maxnt = noise[i][j + 3];        
                                    }
                                    if(minnt > noise[i][j + 3]){
                                             minnt = noise[i][j + 3];         
                                    }
                              }  
                      }         
             }   

             
         for(int j = 0; j < 8; j++){
             map< pair< pair<double, double>, short>, double> tv;             
             for(float i = 0; i <= group; i ++){
                  tv[make_pair(make_pair(i, i + 1), 0)] = 0;
                  tv[make_pair(make_pair(i, i + 1), 1)] = 0;
                  tv[make_pair(make_pair(i, i + 1), 2)] = 0;
                  tv[make_pair(make_pair(i, i + 1), 3)] = 0;           
             }
             tt.push_back(tv);
         }   
 

 
             for(long long i = 0; i < v.size(); i++){
                      for(int j = prefix; j < v[i].size(); j += bsize){ 
                          
                          tt[0][ make_pair( make_pair( (int)((v[i][j] - mina) / ((maxa - mina) / group)), (int)((v[i][j] - mina) / ((maxa - mina) / group)) + 1), base[i][(j - prefix) / bsize] )] ++;    
                          tt[1][ make_pair( make_pair( (int)((v[i][j + 1] -minc) / ((maxc - minc) / group)), (int)((v[i][j + 1] -minc) / ((maxc - minc) / group)) + 1), base[i][(j - prefix) / bsize] )] ++;
                          tt[2][ make_pair( make_pair( (int)((v[i][j + 2] - ming) / ((maxg - ming) / group)), (int)((v[i][j + 2] - ming) / ((maxg - ming) / group)) + 1), base[i][(j - prefix) / bsize] )] ++;
                          tt[3][ make_pair( make_pair( (int)((v[i][j + 3] - mint) / ((maxt - mint) / group)), (int)((v[i][j + 3] - mint) / ((maxt - mint) / group)) + 1), base[i][(j - prefix) / bsize] )] ++; 
                          tt[4][ make_pair( make_pair( (int)((noise[i][j] - minna) / ((maxna - minna) / group)), (int)((noise[i][j] - minna) / ((maxna - minna) / group)) + 1), base[i][(j - prefix) / bsize] )] ++; 
                          tt[5][ make_pair( make_pair( (int)((noise[i][j + 1] - minnc) / ((maxnc - minnc) / group)), (int)((noise[i][j + 1] - minnc) / ((maxnc - minnc) / group)) + 1), base[i][(j - prefix) / bsize] )] ++;
                          tt[6][ make_pair( make_pair( (int)((noise[i][j + 2] - minng) / ((maxng - minng) / group)), (int)((noise[i][j + 2] - minng) / ((maxng - minng) / group)) + 1), base[i][(j - prefix) / bsize] )] ++; 
                          tt[7][ make_pair( make_pair( (int)((noise[i][j + 3] - minnt) / ((maxnt - minnt) / group)), (int)((noise[i][j + 3] - minnt) / ((maxnt - minnt) / group)) + 1), base[i][(j - prefix) / bsize] )] ++; 
                          
                      }
             } 
             
             double total = 0;
             for(long long i = 0; i < base.size(); i++){
                      total += base[i].size();        
             }
 
             for(register int i = 0; i < bsize; i++){
                          prob[i] = 0;             
             }
             
             for(long long i = 0; i < base.size(); i++){
                      for(int j = 0; j < base[i].size(); j++){
                              prob[base[i][j]] ++;    
                      }         
             }
             
             for(register int i = 0; i < bsize; i++){
                          prob[i] /= total;
             }
             
             for(int i = 0; i < tt.size(); i++){
                     for(map< pair< pair<double, double>, short>, double>::iterator itt = tt[i].begin(); itt != tt[i].end(); itt++){
                              tt[i][itt->first] /= total;     
                              //cout<<  tt[i][itt->first] << "\t"; 
                     } 
                     //cout<<endl;
             }
             
}

short bayescall::getBase(vector< vector<double> > &its, long long c, int cc){
      double temp = -1e10;
      short out = 0;
      for(int i = cc; i < cc + bsize; i++){
                    if(its[c][i] > temp){
                                 temp = its[c][i];
                                 out = i % bsize;            
                    }
      }
      return out;
}

double bayescall::getProbability(vector< vector<double> >  &v,vector< vector<double> > &noise,  vector< vector<short> > &base, long long i, int j){
       
    double out[bsize];
       
    for(int k = 0; k < bsize; k ++){
       out[k] = tt[0][make_pair( make_pair( (int)((v[i][j] - mina) / ((maxa - mina) / group)), (int)((v[i][j] - mina) / ((maxa - mina) / group)) + 1), k )] 
       * tt[1][make_pair( make_pair( (int)((v[i][j + 1] - minc) / ((maxc - minc) / group)), (int)((v[i][j + 1] - minc) / ((maxc - minc) / group)) + 1), k )] 
       * tt[2][make_pair( make_pair( (int)((v[i][j + 2] - ming) / ((maxg - ming) / group)), (int)((v[i][j + 2] - ming) / ((maxg - ming) / group)) + 1), k )] 
       * tt[3][make_pair( make_pair( (int)((v[i][j + 3] - mint) / ((maxt - mint) / group)), (int)((v[i][j + 3] - mint) / ((maxt - mint) / group)) + 1), k )] 
       * tt[4][make_pair( make_pair( (int)((noise[i][j] - minna) / ((maxna - minna) / group)), (int)((noise[i][j] - minna) / ((maxna - minna) / group)) + 1), k )] 
       * tt[5][make_pair( make_pair( (int)((noise[i][j + 1] - minnc) / ((maxnc - minnc) / group)), (int)((noise[i][j + 1] - minnc) / ((maxnc - minnc) / group)) + 1), k )] 
       * tt[6][make_pair( make_pair( (int)((noise[i][j + 2] - minng) / ((maxng - minng) / group)), (int)((noise[i][j + 2] - minng) / ((maxng - minng) / group)) + 1), k )] 
       * tt[7][make_pair( make_pair( (int)((noise[i][j + 3] - minnt) / ((maxnt - minnt) / group)), (int)((noise[i][j + 3] - minnt) / ((maxnt - minnt) / group)) + 1), k )];
    }
    
       
        for(int k = 0; k < bsize; k ++){
                out[k] *= prob[k];      
        }
       

       
       double ntp[bsize];
       double tp[bsize];
      for(int t = 0; t < bsize; t++){
              ntp[t] = 0;
              tp[t] = 0;        
      }   
       
       for(int t = 0; t < bsize; t++){ 
       for(int k = 0; k < bsize; k ++){
               if(k != t){
                    ntp[t] += out[k];     
               }
               tp[t] += out[k];
       }
       }
       
       int maxb = -1;
       double maxp = 1e10;
       for(int t = 0; t < bsize; t++){
               if(ntp[t] / tp[t] < maxp){maxp = ntp[t] / tp[t]; maxb = t;}
       }
       
       base[i][(j - prefix) / bsize] = maxb;
       return maxp;
}

