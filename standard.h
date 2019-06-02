/*
 * @kangkang,数据的标准化 
 */
#ifndef _STANDARD_H_
#define _STANDARD_H_

#include "Intensity.h"

class standard{
public:
       standard(){}
       ~standard(){}
public:
       void positive(Intensity &);
       
private:
        const static unsigned short int prefix = 4;
        const static unsigned short int bsize = 4;
};

#endif
