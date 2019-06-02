#ifndef _GAU_ELIMI_H_
#define _GAU_ELIMI_H_

#include <vector>
#include <iostream>
#include <cmath>

class gauElimi{
public:
       gauElimi(){}
       ~gauElimi(){}
       
public:
	   void input (int , std::vector< std::vector<double> > &, std::vector<double> &);
       void gauss ();    
       std::vector<double> output ();    
       
private: 
       int n;
	   std::vector< std::vector<double> > a;
       std::vector<double> b;             
};

#endif
