#ifndef _GRID_WHOLE_H_
#define _GRID_WHOLE_H_

#include "image.h"
#include "gauElimi.h"
#include "affineTransformation.h"
#include "registration.h"

//////////////////////////
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
/////////////////////////

#include <vector>
#include <utility>

class gridWhole{
public:
       gridWhole(){}
       ~gridWhole(){}
public:
        void fit(image &, std::vector< std::pair<float, float> > &);  
        std::vector<double> makeSample(std::vector< std::pair<float, float> >  &);

private:
        const static float step = 3;/////////////////////////////////////////////// 
        const static int sample_distance = 15;///////////////////////////////////// 
        const static float sample_range = 0.5;////////////////////////////////////        
};

#endif
