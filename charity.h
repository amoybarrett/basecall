/*
 * @kangkang,º∆À„charity 
 */
#ifndef _CHARITY_H_
#define _CHARITY_H_

#include "Intensity.h"

class charity{
public:
       charity(){
       }
       ~charity(){
       } 
public:
       std::vector< std::vector<double> > getCh();
       void setCh(std::vector< std::vector<double> > &);
       void compute(Intensity &, const std::string &);
       
private:
       std::vector< std::vector<double> >  ch; 
       const static unsigned short prefix = 4;///////////////////////
       const static unsigned short bsize = 4; ///////////////////////
       const static float thd = 0.6;///////////////////////////////// 
};

#endif
