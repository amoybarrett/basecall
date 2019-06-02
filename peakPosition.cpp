/*
 * @kangkang
 */
#include "peakPosition.h"

using namespace std;

vector< pair<float, float> > peakPosition::getPeak(image &im, vector< pair<float, float> > &peak, bool flag){
   vector< pair<float, float> > out;
   vector< vector<pre> > v = im.getImage();
   for(vector< pair<float, float> >::iterator it = peak.begin(); it != peak.end(); it++){
               float x = 0;
               float y = 0;
               
       if(flag){
               if((*it).first > wsize/2 && (*it).second > wsize/2 && (*it).first < v.size() - wsize/2 && (*it).second < v[0].size() - wsize/2){
                     float sum = 0;
                     for(int i = (*it).first - wsize/2; i <= (*it).first + wsize/2; i++){
                         for(int j = (*it).second - wsize/2; j <= (*it).second + wsize/2; j++){
                                 sum += v[i][j];  
                         }
                     }
                     for(int i = (*it).first - wsize/2; i <= (*it).first + wsize/2; i++){
                         for(int j = (*it).second - wsize/2; j <= (*it).second + wsize/2; j++){
                              x += v[i][j] / sum * i;
                              y += v[i][j] / sum * j; 
                         }
                     }           
               }else{
                     x = (*it).first;
                     y = (*it).second;     
               }  
       }else{
   
              x = (*it).first;
              y = (*it).second;
       }
               
               out.push_back(make_pair(x, y));          
   }
   return out;     
}

