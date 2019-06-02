/*
 * @kangkang,最小二乘拟合 
 */
#ifndef _LEAST_SQUARE_H_
#define _LEAST_SQUARE_H_

#include <vector>
#include <iostream>

class LeastSquare{  
    double a, b;  
public:  
    LeastSquare(const std::vector<double>& x, const std::vector<double>& y)  
    {  
        double t1=0, t2=0, t3=0, t4=0;  
        for(long i=0; i<x.size(); ++i)  
        {  
            t1 += x[i]*x[i];  
            t2 += x[i];  
            t3 += x[i]*y[i];  
            t4 += y[i];  
        }  
        a = (t3*x.size() - t2*t4) / (t1*x.size() - t2*t2 + 1e-200);  
        //b = (t4 - a*t2) / x.size();  
        b = (t1*t4 - t2*t3) / (t1*x.size() - t2*t2);  
    }  
  
    double getY(const double x) const  
    {  
        return a*x + b;  
    }  
  
    double getCoefficient() const{
        return a;
    }
  
    void print() const  
    {  
        std::cout<<"y = "<<a<<"x + "<<b<<"\n";  
    }  
  
}; 

#endif
