/*
 * @kangkang 
 */
 
#ifndef _ML_H_
#define _ML_H_

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class ML{
public:
       virtual void sample() = 0;
       virtual void train() = 0;      
};


#endif
