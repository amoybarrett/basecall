/*
 * @kangkang,svm∑÷¿‡∆˜ 
 */
#ifndef _SVM_H_
#define _SVM_H_

#include <vector>

#include "ML.h"

class svm : public virtual ML{
public:
      svm(){}
      ~svm(){}
      
public:
       void sample();
       void train(std::vector< std::vector<double> > &, std::vector< std::vector<double> >&, std::vector< std::vector<short> > &);
     
};

#endif
