/*
 * @kangkang
 */
 
#include "block.h"

using namespace std;
using namespace GT;
using namespace cv;


void block::fit2(image &im, vector< pair<float, float> > &peak){
      vector< vector< pair<int, int> > > resPosition; 
            
      //细分，取平均值，加快速度 //////////////////////////////////////////////           
      int width = im.getWidth();
      int height = im.getHeight();   
      
      vector< pair<float, float> > fpeak;
      int dx = height / 2 - sample_sq / 2 < 0?0:height / 2 - sample_sq / 2;
      int ux = height / 2 + sample_sq / 2 > height?height:height / 2 + sample_sq / 2;
      int dy = width / 2 - sample_sq / 2 < 0?0:width / 2 - sample_sq / 2;
      int uy = width / 2 + sample_sq / 2 > width?width:width / 2 + sample_sq / 2;
      
      for(vector< pair<float, float> >::iterator it = peak.begin(); it != peak.end(); it++){
                  if((*it).first > dx && (*it).first < ux && (*it).second > dy && (*it).second < uy)
                                 fpeak.push_back(*it);            
      }
        
      vector< vector<float> > samplex;
      vector< vector<float> > sampley;
      makeSample(peak, samplex, sampley);
      float oxx = 0; 
      float oxy = 0;
      float oyx = 0;
      float oyy = 0;
           
              
for(vector< vector<float> >::iterator itas = samplex.begin(); itas != samplex.end(); itas++){
      oxx += (*itas)[0];
      oxy += (*itas)[1];     
}       
for(vector< vector<float> >::iterator itast = sampley.begin(); itast != sampley.end(); itast++){
      oyx += (*itast)[0];
      oyy += (*itast)[1];
}      
      oxx /= samplex.size();
      oxy /= samplex.size();
      oyx /= sampley.size();
      oyy /= sampley.size();
      
      cout<<oxx<<"\t"<<oxy<<endl;
      cout<<oyx<<"\t"<<oyy<<endl; 
   
	  vector<Point2f> corners(3);
  	  corners[0] = Point2f(0,0);  
  	  corners[1] = Point2f(step,0);  
  	  corners[2] = Point2f(0,step);
  	  vector<Point2f> corners_trans(3);  
  	  corners_trans[0] = Point2f(0,0);  
      corners_trans[1] = Point2f(oyy,oyx);  
  	  corners_trans[2] = Point2f(oxy,oxx); 

      Mat warp_mat( 2, 3, CV_32FC1 );
      warp_mat = getAffineTransform( corners_trans, corners);
       
      affineTransformation atf;
      
      atf.affine2(im, warp_mat);      
}

void block::makeSample(vector< pair<float, float> > &peak, vector< vector<float> > &otx, vector< vector<float> > &oty){
                
        for(long i = 0; i < peak.size(); i++){
                 for(long j = i + 1; j < peak.size(); j++){
                 vector<float> tempx;
                 vector<float> tempy;
                 
                 
                 if(abs(peak[i].second - peak[j].second) <= step * sample_range|| abs(peak[i].first - peak[j].first) <= step * sample_range){
                 bool flag = false;
                     for(int k = 1; k <= sample_distance; k++){                      
                        if(abs(peak[i].second - peak[j].second) <= step * sample_range && abs(peak[i].first - peak[j].first) >= k * step - step * sample_range && abs(peak[i].first - peak[j].first) <= k * step + step * sample_range){
                            data d;
                            d.distance = abs(peak[i].first - peak[j].first) + abs(peak[i].second - peak[j].second);   
                            float x,y;
                            if(peak[i].first > peak[j].first){               
                                d.p1 = peak[i];
                                d.p2 = peak[j];
                                x = (peak[i].first - peak[j].first) / k;
                                y = (peak[i].second - peak[j].second) / k;
                            }else{
                                d.p1 = peak[j];
                                d.p2 = peak[i];
                                x = (peak[j].first - peak[i].first) / k;
                                y = (peak[j].second - peak[i].second) / k;                                 
                            } 
                            tempx.push_back(x);
                            tempx.push_back(y);
                            otx.push_back(tempx);
                            flag = true;
                            break;
                        }                   
                     }
                     if(!flag){
                     for(int k = 1; k <= sample_distance; k++){                      
                        if(abs(peak[i].first - peak[j].first) <= step * sample_range && abs(peak[i].second - peak[j].second) >= k * step - step  * sample_range && abs(peak[i].second - peak[j].second) <= k * step + step * sample_range){
                            data d;
                            d.distance = abs(peak[i].first - peak[j].first) + abs(peak[i].second - peak[j].second);   
                            float x,y;
                            if(peak[i].second > peak[j].second){               
                                d.p1 = peak[i];
                                d.p2 = peak[j];
                                x = (peak[i].first - peak[j].first) / k;
                                y = (peak[i].second - peak[j].second) / k;
                            }else{
                                d.p1 = peak[j];
                                d.p2 = peak[i];
                                x = (peak[j].first - peak[i].first) / k;
                                y = (peak[j].second - peak[i].second) / k;                                 
                            }
                            tempy.push_back(x);
                            tempy.push_back(y); 
                            oty.push_back(tempy);                           
                            break;
                        }                   
                     }   
                     }                      
                 }    
               
                                     
                 }
        }   
}


