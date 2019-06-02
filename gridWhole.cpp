/*
 * @kangkang，两种策略：1、微分；2、建立位置函数模型 
 */

#include "gridWhole.h"

using namespace std;
using namespace cv;

void gridWhole::fit(image &im, vector< pair<float, float> >  &peak){
     
     /*   
     vector< vector< pair<pair<float, float>, bool> > > pmb(im.getHeight(), vector< pair<pair<float, float>, bool> >(im.getWidth(), make_pair(make_pair(-1, -1), false)));
     for(vector< pair<float, float> >::iterator it = peak.begin(); it != peak.end(); it++){
          int x = round((*it).first);
          int y = round((*it).second);
          pmb[x][y] = make_pair(*it, true);               
     } 
     */
     
     vector<double> offset1 = makeSample(peak);
     
      double oxx = offset1[0];
      double oyx = offset1[1]; 
      double oxy = offset1[2]; 
      double oyy = offset1[3]; 
      cout<<oxx<<"\t"<<oyx<<"\t"<<oxy<<"\t"<<oyy<<endl;
  
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

std::vector<double> gridWhole::makeSample(vector< pair<float, float> > &peak){
        vector< vector<float> > otx;
        vector< vector<float> > oty; 
        //法1、直线线采样拟合，分横纵 
        //法2、三个点，两个offset对，高斯法解四元一次方程组        
        for(long i = 0; i < peak.size(); i++){
                 for(long j = i + 1; j < peak.size(); j++){
                 vector<float> tempx;
                 vector<float> tempy;                 
                 
                 if(abs(peak[i].second - peak[j].second) <= step * sample_range|| abs(peak[i].first - peak[j].first) <= step * sample_range){
                 bool flag = false;
                     for(int k = 1; k <= sample_distance; k++){                      
                        if(abs(peak[i].second - peak[j].second) <= step * sample_range && abs(peak[i].first - peak[j].first) >= k * step - step * sample_range && abs(peak[i].first - peak[j].first) <= k * step + step * sample_range){  
                            float x,y;
                            if(peak[i].first > peak[j].first){               
                                x = (peak[i].first - peak[j].first) / k;
                                y = (peak[i].second - peak[j].second) / k;
                            }else{
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
                            float x,y;
                            if(peak[i].second > peak[j].second){               
                                x = (peak[i].first - peak[j].first) / k;
                                y = (peak[i].second - peak[j].second) / k;
                            }else{
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

          vector<double> offset;
          double oxx = 0, oxy = 0;
          double oyx = 0, oyy = 0; 
          for(vector< vector<float> >::iterator it = otx.begin(); it != otx.end(); it++){
                      oxx += (*it)[0];
                      oxy += (*it)[1];            
          }
          for(vector< vector<float> >::iterator it = oty.begin(); it != oty.end(); it++){
                      oyx += (*it)[0];
                      oyy += (*it)[1];            
          }
          oxx /= otx.size();
          oxy /= otx.size();
          oyx /= oty.size();
          oyy /= oty.size();
          offset.push_back(oxx);
          offset.push_back(oyx);
          offset.push_back(oxy);
          offset.push_back(oyy);
          return offset;        
          
}
