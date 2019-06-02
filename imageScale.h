/*
 * @kangkang,假设图像为线性畸变
 */
 
#ifndef _IMAGE_SCALE_H_
#define _IMAGE_SCALE_H_

#include <algorithm>
#include <cmath>
#include <vector>

#include "image.h"

class imageScale{
public:
       imageScale(){}
       ~imageScale(){}  
public:
       void scale(image &im){
                std::vector< std::vector<pre> > imt = im.getImage();
                std::vector< pre > data;
                for(int i = 0; i < imt.size(); i++){
                        for(int j = 0; j < imt[i].size(); j++){
                              data.push_back(imt[i][j]);  
                        }        
                } 
                sort(data.begin(), data.end());
                
                pre td = data[data.size() - thd];
                for(int i = 0; i < imt.size(); i++){
                        for(int j = 0; j < imt[i].size(); j++){
                              if(imt[i][j] > td)  
                                  imt[i][j] = td;
                        }        
                }                 
                im.setImage(imt);   
       }
private:
        const static unsigned int thd = 100;/////////////////////////////////////
};

#endif
