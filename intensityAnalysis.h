/*
 * @kangkang,强度分析 ,包括强度处理所有步骤 
 */
#ifndef _INTENSITY_ANALYSIS_H_
#define _INTENSITY_ANALYSIS_H_
#include "Intensity.h"
#include "readWriteCH.h"

class intensityAnalysis{
public:
      intensityAnalysis(){}
      ~intensityAnalysis(){} 
public:
       void draw(Intensity &, const std::string &);     
};

#endif
