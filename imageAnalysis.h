/*
 * @kangkang,图像分析 ,包括图像处理所有步骤 
 */
#ifndef _IMAGE_ANALYSIS_H_
#define _IMAGE_ANALYSIS_H_

#include "readWriteTIFF.h"
#include "image.h"
#include "erodeDilate.h"
#include "gaussWeighting.h"
#include "imageFiltering.h"
#include "readWriteCH.h"

/*
 * multithread
 */
class imageAnalysis{
    
      
public:
       imageAnalysis(){}
       ~imageAnalysis(){} 
 
public:
    void draw(std::vector<image> &, const std::string &);
        
};

#endif
