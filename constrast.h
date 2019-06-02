#ifndef _CONSTRAST_H_
#define _CONSTRAST_H_

#include <vector>
#include <cmath>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef dt
#define dt float
#endif

#ifndef E
#define E 2.718281828
#endif

class constrast{

public:
       constrast(){}
       ~constrast(){}
  
public:
       std::vector<double> evaluate(cv::Mat &);
       std::vector<double> subEvaluate(cv::Mat &);
       cv::Mat one(cv::Mat &);
       std::vector<double> run(cv::Mat &, int , int , int , int);
             
private:
        const static short int window = 11;    
        const static int number = 50; 
        const static long N = 1; 
};

#endif
