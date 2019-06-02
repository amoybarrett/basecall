#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#include <boost/math/special_functions/erf.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp> 

#include "../xuweibin/cluster.h"


class calculateScore
{
public:
	calculateScore(void){}
	~calculateScore(void){}
public:
	static void calculate(std::vector< std::vector<float>* > &,  std::vector< char > &, std::vector< char >&);
	static void calculate2(std::vector< std::vector<float>* > &, std::vector< char > &, std::vector< char >&);
    static char phred(float probability){
          int out = (int)(-10.0 * std::log(probability) / std::log(10.0) + 0.5) + 33;
          return (char)out;              
    }
private:
	const static int window = 5;////////////////////////////////////////////////////////////////
};

static cv::Mat cholesky(cv::Mat&   mat){ 
	cv::Mat u;
	if(mat.rows != mat.cols)
		std::cerr<<"Error : Matrix Must Be Square\n";
	for(int i = 0; i < mat.rows; i++)
		for(int j = 0; j < mat.cols; j++)
			if(mat.at<double>(i,j) != mat.at<double>(j,i)){
				std::cerr<<"Warning : Bad Matrix\n";
			}
	int n = mat.cols;
	u = cv::Mat::zeros(n, n, CV_64F);
	for(int i = 0; i < n; i++){
		u.at<double>(i,i) = mat.at<double>(i,i);
		for(int k = 0; k <= i - 1; k++)
			u.at<double>(i, i) = u.at<double>(i, i) - u.at<double>(k, i) * u.at<double>(k, i);
		u.at<double>(i, i) = std::sqrt(u.at<double>(i, i));
		for(int j = i+1; j < n; j++){
			u.at<double>(i, j) = mat.at<double>(i, j);
			for(int k = 0; k <= i - 1; k++)
				u.at<double>(i, j) = u.at<double>(i, j) - u.at<double>(k, i) * u.at<double>(k, j);
			u.at<double>(i, j) = u.at<double>(i, j) / u.at<double>(i, i);
		}
	}
	return u;
 }   

static double tfs(cv::Mat &DV, float* temp){
		double sum = 0;
		for(int i = 0; i < DV.rows; i++){
			double ts = 0;
			for(int k = 0; k < DV.cols; k++){
				ts += DV.at<double>(i, k) * temp[k];
			}
			sum += ts * ts;
		}
		return std::sqrt(sum);	
} 

static double jdz(float* v1, float* v2, int len){
		double sum = 0;
		for(int i = 0; i < len; i++){
			sum += v1[i] * v2[i];
		}
		return std::abs(sum);	
} 

static double mo(float* v1, int len){
		double sum = 0;
		for(int i = 0; i < len; i++){
			sum += std::pow(v1[i], 2);
		}
		return std::sqrt(sum);	
} 

