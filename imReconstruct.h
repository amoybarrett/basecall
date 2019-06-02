/*
 * @kangkang, DNB或者cluster重构 
 */
 
#ifndef _IM_RECONSTRUCT_H_
#define _IM_RECONSTRUCT_H_


#include "image.h"

class imReconstruct{
public:
       imReconstruct(){}
       ~imReconstruct(){}
public:
       std::vector< std::pair<float, float> > getPeakPosition(image &, std::vector< std::vector<long long> > &, bool);
private:
        const static unsigned short int gsize = 3;
};
#endif
