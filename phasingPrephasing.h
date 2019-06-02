/*
 * @kangkang,PPÏßÐÔ½ÃÕý 
 */
#ifndef _PHASING_PREPHASING_H_
#define _PHASING_PREPHASING_H_

#include <cmath>
#include "Intensity.h"
#include "LeastSquare.h"
#include "inversion.h"

/*
 * run on / lag
 */
class phasingPrephasing{
public:
      phasingPrephasing(){
      }
      ~phasingPrephasing(){
      }
      
public:
       std::vector<double> phasing(Intensity &);
       std::vector<double> prephasing(Intensity &);
       
       double* oneNotMax(std::vector< std::vector<db> > &, int, bool);
       double* twoNotMax(std::vector< std::vector<db> >&, int, bool);
       int max(std::vector< std::vector<db> >&, long long , int);
       void correct(Intensity &, std::vector<double> &);
private:
        const static unsigned short int prefix = 4;
        const static unsigned short int bsize = 4; 
        double **matrix;     
};

#endif
