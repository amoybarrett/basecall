/*
 * @kangkang,¶şÎ¬Î¬ÄÉÂË²¨ 
 */
 
#ifndef _WIENER_H_
#define _WIENER_H_

#include "image.h"
#include <iostream>
#include <cstdlib>


class wiener{
public:
      wiener(){}
      ~wiener(){}
public:
       void filtering(image &);
private:
        const static unsigned short gsize = 3;///////////////////////////////////       
};

#endif
