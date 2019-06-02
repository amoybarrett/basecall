/*
 * @kangkang,Í¼Ïñ·ÂÉä±ä»» 
 */
#ifndef _AFFINE_TRANSFORMATION_H_
#define _AFFINE_TRANSFORMATION_H_

#include "image.h"

/////////////////////////
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
/////////////////////////

class affineTransformation{
public:
      affineTransformation(){}
      ~affineTransformation(){} 
public:
      void affine(image &); 
      void affine2(image &, cv::Mat &); 
      image rotate(image &, double , double); 
      void translation(image &, std::pair<int, int>);  
private:
      cv::Mat transform; 
};

#endif
