/*
 * @kangkang
 */
#include "charity.h"
#include "readWriteCH.h"

using namespace std;

std::vector< std::vector<double> > charity::getCh(){
             return this->ch;
}

void charity::setCh(std::vector< std::vector<double> > &ch){
     this->ch = ch;
}

void charity::compute(Intensity &its, const string &outfile){
     ch.clear();
     vector< vector<double> > allmax;
     vector< vector<db> > v = its.getIntensity();
     vector< vector<db> > inoise = its.getNoise();
     
     for(long long i = 0; i < v.size(); i ++){
             vector<double> temp;
             vector<double> tmax;
             for(int j = prefix; j < v[i].size(); j += bsize){
                     db max;
                     db secondMax;
                     bool flag = true;
                     int tp = -1;
                     for(int k = j; k < j + bsize; k ++){
                             if(flag){
                                      max = v[i][k];
                                      flag = false;
                                      tp = k;
                             }else{
                                   if(v[i][k] > max){
                                              max = v[i][k];
                                              tp = k;
                                   }
                             }
                     }
                     tmax.push_back(max);
                     flag = true;
                     for(int k = j; k < j + bsize; k ++){
                         if(k != tp){
                             if(flag){
                                      secondMax = v[i][k];
                                      flag = false;
                             }else{
                                   if(v[i][k] > secondMax){
                                              secondMax = v[i][k];
                                   }
                             }
                           }
                     }
                     temp.push_back(max/(max + secondMax + 1e-10));
             }
             ch.push_back(temp);
             allmax.push_back(tmax);
     }
     
     long long i = 0;
     long long counter = 0;
     long long pf = 0;
     long long tatol = v.size() * (v[0].size() - prefix) / bsize;
     long long pft = v.size();
     vector< vector<double> >::iterator itc = ch.begin();
     vector< vector<double> >::iterator itn = inoise.begin();
     vector< vector<double> >::iterator itm = allmax.begin();
     vector<double> ltatol;
     for(vector< vector<db> >::iterator it = v.begin(); it != v.end(); it ++){
           int ct = 0;
           int j = 0;
           for(vector<db>::iterator itt = (*it).begin() + prefix; itt < (*it).end(); itt += bsize){
                 if(ch[i][j] < thd){
                             counter ++;  
                             ct++;         
                 }  
                 j++;
           }
           
           ltatol.push_back(ct);


/*
////////////////////////////////////////////////////////////////////////////
           for(int t = 0; t < ch.size(); t++){
                   if(ch[i][t] < thd){                 
                     v.erase(it);
                     if(0 != inoise.size())
                          inoise.erase(itn + i);
                     ch.erase(itc + i);
                     allmax.erase(itm + i);
                     it--;
                     i--;
                     pf++;
                     break;
                   }
           }
//////////////////////////////////////////////////////////////////////////////
//*/

           i++;
     }
     cout<<"PF:"<<(1 - pf * 1.0 / pft)<<endl;
     cout<<"Charity:"<<(1 - counter * 1.0 / tatol)<<endl;
     readWriteCH rwc;
     rwc.setContent(ch);
     rwc.writeCH(outfile);
     its.setIntensity(v);
     its.setNoise(inoise);
}

/*
int main(void){
    Intensity its;
    its.readIntensity("test.intensity");
    charity ch;
    ch.compute(its);    
    its.writeIntensity("test.res");
}
*/
