/*
 * @kangkang,≤È’“field
 */
#ifndef _FIELD_H_
#define _FIELD_H_

#include <vector>
#include <utility>
#include "image.h"

/*
 * multithread
 */
class field{
public:
       field(){            
       }
       ~field(){}
public:
       std::vector< std::vector< std::pair<int, int> > > getField2(image& , std::vector< std::vector< std::pair<int, int> > > &, std::vector< std::vector<int> > &);
       double winSum(std::vector< std::vector<pre> > &, int , int , int , int , int , int);       
private:
       const static short int rg = 9;//////////////////////////////////////
       const static short int r = 9;/////////////////////////////////////// 
       const static short int ns = 2;///////////////////////////////////////
       const static short int rd = 75;/////////////////////////////////////
       const static short int rg2 = 30;/////////////////////////////////////
       const static short int r2 = 11;//////////////////////////////////////
};
#endif 
