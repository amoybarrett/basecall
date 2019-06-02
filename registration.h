/*
 * @kangkang, DNB或者cluster定位 
 */
#ifndef _REGISTRATION_H_
#define _REGISTRATION_H_

#include "image.h"
#include "imReconstruct.h"

class registration{
public:
       registration(){}
       ~registration(){}  
       
public:
       std::vector< std::pair<float, float> > getIRPosition(image &,float ,std::vector< std::vector<double> > &, std::vector< std::vector<long long> > &, bool);
private:
        const static unsigned short int step = 1;///////////////////////////////
        const static short window = 100;/////////////////////////////////////////
};

#endif


