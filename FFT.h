/*
 * @kangkang,快速傅里叶变换 
 */
#ifndef _FFT_H_
#define _FFT_H_

#include <fftw3.h>

#include "image.h"

class FFT{
public:
       FFT(){
                   
       }     
       ~FFT(){
              
       } 
       
public:
       void op_fFFT(image &);
       void op_rFFT(cv::Mat &);
       ///////////////////
       std::pair<int, int> minMax(image &, image &, bool);
       fftw_complex* fFFT(image &);
       double* rFFT(fftw_complex *, int , int);
       
        
};

#endif
