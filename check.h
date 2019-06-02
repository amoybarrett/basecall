/*
 * @kangkang,≤È’“check 
 */
#ifndef _CHECK_H_
#define _CHECK_H_

#include "image.h"

class check{
public:
       check(){
               r2 = 11;////////////////////////////////
               rg = 20;///////////////////////////////
               r = 9;/////////////////////////////////
               rowNum = 9;////////////////////////////
               colNum = 9;////////////////////////////
               ns = 2;/////////////////////////////////
               rd = 75;////////////////////////////////
       }
       ~check(){} 
public:
       std::vector< std::vector< std::pair<int, int> > > getCheck2(image &, std::vector< std::vector<int> > &);
       double winSum(std::vector< std::vector<pre> > &, int , int , int , int , int , int);
private:
        int r2;
        int rowNum;
        int colNum;
        int rg;
        int r;
        int ns;
        int rd;
};

#endif
