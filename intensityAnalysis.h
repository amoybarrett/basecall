/*
 * @kangkang,ǿ�ȷ��� ,����ǿ�ȴ������в��� 
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
