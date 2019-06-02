/*
 * @kangkang,¶àÔª»Ø¹é
 */
#ifndef _REGRESSION_H_
#define _REGRESSION_H_

#include<iostream>
#include<cmath>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
 

  class  mregression
  {
  private: 
	       long m, n, nn;
		   std::vector< std::vector<double> >  x;
           std::vector<double> y; 
           double *a;
		   double  q, s, r, *v, u;
		   double  **b;
  public:
	       mregression (std::vector< std::vector<double> >  &xx, std::vector<double> &yy)
		   {
               x = xx;
               y = yy;
			   long i;		   
			   m = x.size(); n = x[0].size();
			   nn = m + 1;
	           a = new double[m+1];
	           v = new double[m];
	           b = new double*[m+1];
	           for (i=0; i<=m; i++) b[i] = new double[m+1];
		   }
		   void analysis();    
           void chol();       
           double* output();  
		   ~mregression()
		   {
			   int i;
			   for (i=0; i<=m; i++) { delete [] b[i]; }
			   delete [] b;
			   delete [] a, v; 
		   }
  };
  
#endif
