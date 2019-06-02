#ifndef _SCORE_H_
#define _SCORE_H_

#include<cmath>
#include<iostream>

class score{
public:
       score(){}
       ~score(){}
public:
       static int phred(float probability){
          if(probability < 1e-6){
                         probability = 1e-6;               
          }
          int out = round(- 10.0 * std::log(probability) / std::log(10) );
          return out;              
       }
       static int solexa(float probability){
          if(probability < 1e-6){
                         probability = 1e-6;               
          }
          int out = round(- 10.0 * std::log((probability) / (1 - (probability))) / std::log(10) );    
          return out;                                   
       }    
};

#endif
