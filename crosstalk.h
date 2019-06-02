/*
 * @kangkang,crosstalk½ÃÕý 
 */
#ifndef _CROSSTALK_H_
#define _CROSSTALK_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>

#include "Intensity.h"
#include "image.h"
#include "LeastSquare.h"
#include "inversion.h"
#include "standard.h"

#ifndef PI
#define PI 3.1415926535898
#endif



class crosstalk{
      
#define RG 90

public:
       crosstalk(){     
		    matrix = new double*[bsize];
    		for(int i = 0; i < bsize; ++i){
	 		matrix[i] = new double[bsize];
    		}      
       }
       ~crosstalk(){
    		for(int i = 0; i < bsize; ++i){
	 		delete []  matrix[i];
    		} 
		delete [] matrix;
       }
public:

       void linearFit(Intensity &);
       void polar(Intensity &);
       void correct(std::vector< std::vector<db> > &, int &);
       
public:
       void print();
       double** getMatrix();
       void setMatrix(double **);
       double getArray(double* , std::vector<double>);
       
private:
        const static short prefix = 4; /////////////////////////////
        const static short bsize = 4; ////////////////////////// 
        const static float step = 0.5; //////////////////////////////////
        double **matrix;    
};


 #endif
