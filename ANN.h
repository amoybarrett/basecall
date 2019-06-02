/*
 * @kangkang,ANN(Éñ¾­ÍøÂç)
 */

#ifndef _ANN_H_
#define _ANN_H_

#include <vector>

#include "ML.h"

class ANN : public virtual ML{
public:
       ANN(){}
       ~ANN(){}
       
public:
       void sample();
       void train(std::vector< std::vector<double> > &, std::vector< std::vector<double> >&, std::vector< std::vector<short> > &);
       
};

#endif
