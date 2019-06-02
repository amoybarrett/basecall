/*
 * @kangkang
 */
#include "registration.h"

using namespace std;
using namespace cv;

vector< pair<float, float> > registration::getIRPosition(image &ig, float thd, vector< vector<double> > &ala, vector< vector<long long> > &fl, bool lt){

    fl.clear();
    vector< vector<pre> > src = ig.getImage();
    vector< vector<pre> > bg = ig.getNoise();
    
       
    vector< vector<float> > tr(src.size(), vector<float>(src[0].size(), 0));
    for(int i=0; i < src.size(); ++i){
            for(int j=0; j < src[i].size(); ++j){
                    double t1 = src[i][j];
                    double t2 = bg[i][j]+step;
                    double ratio = t1 / t2;
                    //cout<<t1<<"\t"<<t2<<"\t"<<ratio<<endl;
                    tr[i][j] = ratio;
            }
    }   
       
    long long count=0;
    vector< vector<long long> > tempf(src.size(), vector<long long>(src[0].size(), 0));
    for(int i = 0; i < src.size(); i += window){        
            for(int j = 0; j  < src[i].size(); j += window){
                    
                    int downi = i;
                    int ui = i + window > src.size() - 1 ? src.size() - 1 : i + window;
                    int downj = j;
                    int uj = j + window > src[i].size() - 1 ? src[i].size() - 1 : j + window;
                    
                    double sum = 0;
                    long nc = 0;
                    for(int k1 = downi; k1 <= ui; k1++){
                            for(int k2 = downj; k2 <= uj; k2++){
                                  if(tr[k1][k2] > thd / 10){
                                      sum += tr[k1][k2];
                                      nc++; 
                                  }         
                            }        
                    }
                    double tthd = sum / nc * thd;
                    
                    for(int k1 = downi; k1 <= ui; k1++){
                            for(int k2 = downj; k2 <= uj; k2++){                    
                                    if(tr[k1][k2] > tthd){
                                                tempf[k1][k2] = 1;
                                                count ++;
                                    }else{
                                                tempf[k1][k2] = 0;
                                    }
                            }
                    }    
                                                         
            } 
    }    
    fl = tempf;
    
    imReconstruct ir;
    vector< pair<float, float> > resultPosition = ir.getPeakPosition(ig, fl, lt);
    
    vector<double> tala;
    tala.push_back(count);
    tala.push_back(resultPosition.size()); 
    tala.push_back((count * 1.0 / resultPosition.size()));
    ala.push_back(tala);
  
    cout<<count<<":"<<resultPosition.size()<<"(peaks)"<<endl;
    
    return resultPosition;	
}
