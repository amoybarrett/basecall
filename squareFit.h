/*
 * @kangkang,矩形区域最小二乘拟合和插值强度 
 */
 
 #ifndef _SQUARE_FIT_H_
 #define _SQUARE_FIT_H_
                           
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  #include  <cstdlib>
  #include  <vector>
  #include  <utility>
 
  class  squareFit
  {
  private: 
           int n, m, p, q;
		   std::vector<double>  x, y; 
           std::vector< std::vector<double> > z;
           double **a, dt[3];
		   double **v;
  public:
	       squareFit (std::vector< std::vector<double> > &z, int gsize)
		   {
			   int k;
			   //////////////////////////////
			   for(int t1 = 0 - gsize/2; t1 <= gsize/2; t1++){x.push_back(t1);y.push_back(t1);}
		       p = 4; q = 4;
		       //////////////////////////////
			   this->z = z;
			   n = x.size(); m = y.size();               
	           v = new double*[20];
	           for (k=0; k<20; k++) { v[k] = new double[m]; }
	           a = new double*[p+1]; 
	           for (k=0; k<=p; k++)  { a[k] = new double[q+1]; }
		   }
		   void fit ();       
           double interpolation(std::pair<float, float> &pos); 
		   ~squareFit ()
		   {
			   int k;
			   for (k=0; k<=p; k++) { delete [] a[k]; }
			   delete [] a;
			   for (k=0; k<20; k++) { delete [] v[k]; }
			   delete [] v;
		   }
		   
  private:
          const static float precision = 0.05;//////////////////////////////////
          const static float rg = 0.6;//////////////////////////////////////////
  };

#endif

