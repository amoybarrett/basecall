/*
 * @kangkang,高斯滤波, 可以通过先行卷积后列卷积加速 
 */
#ifndef _GAUSS_WEIGHTING_H_
#define _GAUSS_WEIGHTING_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "image.h"

#ifndef PI
#define PI 3.1415926535898
#endif

class gaussWeighting{
public:
       gaussWeighting(){
		gaussKernel = new float*[gsize];
    		for(int i = 0; i < gsize; ++i){
	 		gaussKernel[i] = new float[gsize];
    		}                         
       }
       ~gaussWeighting(){
    		for(int i = 0; i < gsize; ++i){
	 		        delete []  gaussKernel[i];
    		} 
		    delete [] gaussKernel;                         
       }  
       void print() const{
            for(int i = 0; i < gsize; i ++){
                    for(int j = 0; j < gsize; j++){
                            std::cout<<gaussKernel[i][j]<<"\t";        
                    }        
                    std::cout<<std::endl;
            }     
       }
      
public:
       void filter(image &);
       void gaussFun( float );
       void mr( float );
       void one();
///////////////////////////////////////////////////////////// 
       void op_filter(image &);   
/////////////////////////////////////////////////////////////
private:
        float **gaussKernel;  
        const static unsigned short int gsize = 9;////////////////////////////////////////
        const static double segma = 1.1;         //////////////mr:1.5,gauss:0.75////////// 
};

#endif
