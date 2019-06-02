/*
 * @kangkang
 */

#ifndef _BB_H_
#define _BB_H_

#include <iostream>
#include <cmath>
#include <utility>
#include <vector>

#include "image.h"
#include "Intensity.h"
#include "LeastSquare.h"
#include "inversion.h"

#define Random(x) (rand() % x)

class BB{
public:
       BB(){
		    matrix = new double*[bbsize];
    		for(int i = 0; i < bbsize; ++i){
	 		        matrix[i] = new double[bbsize];
    		}                         
       }
       ~BB(){ 
    		for(int i = 0; i < bbsize; ++i){
	 		        delete []  matrix[i];
    		} 
		    delete [] matrix;                          
       }
public:   
       void MLR(std::vector<image> &, std::vector< std::vector< std::vector< std::vector< std::pair<float, float> > > > > &);    
              
private:
        const static short prefix = 4; /////////////////////////////
        const static short bsize = 4; //////////////////////////  
        const static short bbsize = 8;/////////////////////////// 
        double **matrix;        
};

#endif 
