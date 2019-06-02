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
              rowNum = 8;////////////////////////////
              colNum = 8;////////////////////////////   
              cdnb = 3;////////////////////////////// 
              FN = 5;//////////////////////////////// 
              precision = 0.5;///////////////////////
              rc = 1;//////////////////////////////////
              rg = 1.3;////////////////////////////////
              rk = 1.3;////////////////////////////////
  
/*
#ifdef IMPORTCHIP
// before
int m_gridSizeX[] = {75,100,70,85,65,90,80,90,199};
int m_gridSizeY[] = {80,80,50,60,60,70,70,60,190};
#else
// after(chip made in china)
int m_gridSizeX[] = {65,82,95,105,105,95,82,65,160};
int m_gridSizeY[] = {55,63,77,90,90,77,63,55,150};
#endif  
*/  
              
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
       void osmSample(std::vector< std::vector< std::pair<float, float> > >  &, std::map< std::pair<float, float>, std::pair<float, float> > &);
       double alignGrid(std::vector< std::vector< bool > > &, std::vector< std::vector< bool > > &, std::vector< std::vector< std::pair<float, float> > > &);
       void coarseFit();/////////////////////////////////////////////////////3*3
       void fineFit();///////////////////////////////////////////////////////5*5
       
private:   
        std::vector<int> dnbx;
        std::vector<int> dnby;  
        int rowNum;
        int colNum;
        int cdnb;     
        int FN;  
        float precision;
        float rc;
        float rg;
        float rk;
};

#endif
