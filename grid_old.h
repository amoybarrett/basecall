/*
 * @kangkang,Íø¸ñÄâºÏ 
 */
#ifndef _GRID_H_
#define _GRID_H_

#include "image.h"
#include "global.hpp"

#include <vector>
#include <utility>
#include <map>
#include <cmath>

#ifndef PI
#define PI 3.1415926535898
#endif

class grid{
public:
       grid(){
              step = 3; /////////////////////////////////////////
              rowNum = 8;////////////////////////////
              colNum = 8;////////////////////////////   
              cdnb = 3;////////////////////////////// 
              rg = 4;////////////////////////////////3 
              FN = 8;////////////////////////////////8»ò1 
              precision = 0.5;///////////////////////
              rc = 0.5;//////////////////////////////////
              
         //////////////////////////////////////////////////////////////     
         dnbx.push_back(80 - cdnb);
         dnbx.push_back(80 - cdnb);
         dnbx.push_back(190 - cdnb);
         dnbx.push_back(60 - cdnb);
         dnbx.push_back(70 - cdnb);
         dnbx.push_back(70 - cdnb);
         dnbx.push_back(60 - cdnb);
         dnbx.push_back(60 - cdnb);
         
         dnby.push_back(70 - cdnb);
         dnby.push_back(100 - cdnb);
         dnby.push_back(75 - cdnb);
         dnby.push_back(199 - cdnb);
         dnby.push_back(90 - cdnb);
         dnby.push_back(80 - cdnb);
         dnby.push_back(90 - cdnb);
         dnby.push_back(65 - cdnb); 
         /////////////////////////////////////////////////////////////
                                    
       }
       ~grid(){}  
public:
       std::vector< std::vector< std::vector< std::pair<float, float> > > > fit(image &, std::vector< std::vector< std::pair<int, int> > > &, std::vector< std::pair<float, float> > &, std::vector< std::vector< std::vector< bool > > > &, std::vector<double> &, std::vector<std::vector<std::vector<bool> > >&, bool); 
       double modifyGrid(std::vector< std::vector< std::pair<float, float> > >  &, std::map< std::pair<float, float>, std::pair<float, float> > &, std::vector< std::vector< bool > > &);
       double alignGrid(std::vector< std::vector< bool > > &, std::vector< std::vector< bool > > &, std::vector< std::vector< std::pair<float, float> > > &);
       void coarseFit();/////////////////////////////////////////////////////3*3
       void fineFit();///////////////////////////////////////////////////////5*5
       
private:
        float step;    
        std::vector<int> dnbx;
        std::vector<int> dnby;  
        int rowNum;
        int colNum;
        int cdnb; 
        int rg;       
        int FN;   
        float precision;
        float rc;
};

#endif
