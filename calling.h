/*
 * @kangkang,call碱基和质量 
 */
#ifndef _CALLING_H_
#define _CALLING_H_

#include "Intensity.h"
#include "readWriteGZ.h"
#include "svm.h"////////////////////////////
#include "ANN.h"////////////////////////////
#include "bayescall.h"//////////////////////
#include "score.h"
#include "readWriteCH.h"

#include <cstdlib>
#include <cmath>
#include <cstring> 

#ifndef PI
#define PI 3.1415926535898
#endif

#ifndef E
#define E 2.718281828
#endif

class calling{
public:
       calling(){
                 sigma = 0.2;////////////////////////          
       }
       ~calling(){}   
public:
       void call(Intensity &, const std::string &, const std::string &);
       short getBase(std::vector< std::vector<db> > &, long long , int );
       short getScore(double);
       double erf(db, db);
       double getProbability(std::vector< std::vector<db> > &, long long, int , int, std::vector<db> &,std::vector<db> &);
       double getRoughProbability(std::vector< std::vector<db> > &, long long, int , int);
       
private:
        const static unsigned short int prefix = 4;//////
        const static unsigned short int bsize = 4;////
        const static short QualitySystem = 64;///////////////////////
        const static double precision = 0.001;///////////////////////
        
        float mu;
        float sigma;
};

#endif
