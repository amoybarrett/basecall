/*
 * @kangkang,DNB或者cluster重心 
 */
#ifndef _PEAK_POSITION_H_
#define _PEAK_POSITION_H_

#include "image.h"
#include <vector>
#include <utility>

class peakPosition{
public:
       peakPosition(){}
       ~peakPosition(){}  
public:
       std::vector< std::pair<float, float> > getPeak(image &im, std::vector< std::pair<float, float> > &, bool);  
private:
        const static short wsize = 3;     
};

#endif

