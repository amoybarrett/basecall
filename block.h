/*
 * @kangkang
 */
 
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>

#include "image.h"
#include "global.hpp"
#include "affineTransformation.h"

//////////////////////////
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
/////////////////////////

#ifndef _LL_
#define _LL_
typedef long long ll;
#endif

class block{
public:
       block(){
              step = 3; /////////////////////////////////////////                
       }
       ~block(){}
public:
       void fit2(image &, std::vector< std::pair<float, float> > &);
       void makeSample(std::vector< std::pair<float, float> > &, std::vector< std::vector<float> > &, std::vector< std::vector<float> > & );
private:
        float step;  
        const static int sample_distance = 20;//////////////////////////////////// 
        const static float sample_range = 0.5;///////////////////////////////////
        const static float sample_sq = 1e100;/////////////////////////////////
};

#endif
