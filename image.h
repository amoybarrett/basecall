/*
 * @kangkang,ÕºœÒ¿‡ ,◊”ÕºœÒ¿‡ 
 */
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <vector>
#include <cmath>

#include "readWriteTIFF.h"

#ifndef _PRE_
#define _PRE_
typedef unsigned short int pre;//ALL CLASS
#endif

#ifndef TIFF_UP
#define TIFF_UP 65535//ALL CLASS
#endif

#ifndef TIFF_DOWN
#define TIFF_DOWN 0//ALL CLASS
#endif

namespace IMAGE{

class image{   
      
public:
       image(std::string filename,
        unsigned short slide,
        unsigned short lane,
        unsigned short field,
        unsigned int tile,
        long id = -1):filename(filename),slide(slide),lane(lane),field(field),tile(tile),id(id){}
       image(readWriteTIFF &rwt){
            im = rwt.getIm();
	    if(!im.empty()){
  	    	    this->width = (this->im)[0].size();
            	this->height = (this->im).size();
	    }
//////////////////////////////////////
	    op_im = rwt.getOp_im();
	    op_width = op_im.cols;
	    op_height = op_im.rows;
//////////////////////////////////////
       }
       image(const image &imt){
                   this->im = imt.im;
                   this->width = imt.width;
                   this->height = imt.height;
                   this->noise = imt.noise;
	               this->op_im = (imt.op_im).clone();
	               this->op_width = imt.op_width;
                   this->op_height = imt.op_height;
	               this->op_noise = (imt.op_noise).clone();                   
       }
       image(){                    
       }
       ~image(){
                im.clear();
                noise.clear();
       }
               
public:
       void setImage(const std::vector< std::vector<pre> > &);
       std::vector< std::vector<pre> > getImage();
       std::vector< std::vector<pre> >  &getImageYY(){return im;}
       pre getWidth();
       pre getHeight();
       pre** getArray();
       
       void setNoise(const std::vector< std::vector<pre> > &);
       std::vector< std::vector<pre> > getNoise();
       
       double average();
       long double sum();
       pre max();
       pre min();
       long double variance();
       
//////////////////////////////////////////////////////////////////////////////
       long double LaplacianGradient();
//////////////////////////////////////////////////////////////////////////////    
   
       std::vector<pre> rowMax();
       std::vector<pre> rowMin();
       std::vector<pre> colMax();
       std::vector<pre> colMin();
       std::vector<double> rowSum();
       std::vector<double> colSum();
       std::vector<double> rowAve();
       std::vector<double> colAve();     
              
       void print() const;
    
    
public:
//////////////////////////////////////////////////////////////////////////////
       static cv::Mat vectorToMat(std::vector< std::vector<pre> > &);
       static std::vector< std::vector<pre> >  matToVector(cv::Mat &);
       static IplImage MatToIplImage(cv::Mat &);
       static cv::Mat IplImageToMat(IplImage *);
       static cv::Mat CvMatToMat(CvMat *);
       static CvMat MatToCvMat(cv::Mat &);
       static const CvArr * MatToCvArr(cv::Mat &);
//////////////////////////////////////////////////////////////////////////////  
          
public:

//////////////////////////////////////////////////////////////////////////
       image  operator-=(const pre &js){
             for(std::vector< std::vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
                         std::vector<pre> temp = *it;
                         for(std::vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                             double temp = *itt;
                             temp -= js;
                             if(temp > TIFF_UP) temp = TIFF_UP;
                             if(temp < TIFF_DOWN) temp = TIFF_DOWN;
                             *itt = temp;
                         }    
             }  
             return *this;                  
       }
//////////////////////////////////////////////////////////////////////////

       image  operator-=(const std::vector< std::vector<pre> > &jj){
             for(int i = 0; i < im.size(); i++){
                     for(int j = 0; j< im[i].size(); j++){
                             double temp = im[i][j];
                             temp -= jj[i][j];
                             if(temp > TIFF_UP) temp = TIFF_UP;
                             if(temp < TIFF_DOWN) temp = TIFF_DOWN;
                             im[i][j] = temp;
                     }
             }
             return *this;                       
       }

//////////////////////////////////////////////////////////////////////////
       image  operator+=(const pre &js){
              for(std::vector< std::vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
                         std::vector<pre> temp = *it;
                         for(std::vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                             double temp = *itt;
                             temp += js;
                             if(temp > TIFF_UP) temp = TIFF_UP;
                             if(temp < TIFF_DOWN) temp = TIFF_DOWN;
                             *itt = temp;
                         }    
             }                     
             return *this;
       }
       image  operator+=(const std::vector< std::vector<pre> > &jj){
             for(int i = 0; i < im.size(); i++){
                     for(int j = 0; j< im[i].size(); j++){
                             double temp = im[i][j];
                             temp += jj[i][j];
                             if(temp > TIFF_UP) temp = TIFF_UP;
                             if(temp < TIFF_DOWN) temp = TIFF_DOWN;
                             im[i][j] = temp;        
                     }
             }
             return *this;                     
       }
       image  operator+=(image& tim){
             std::vector< std::vector<pre> >  v = tim.getImage();
             for(int i = 0; i < im.size(); i++){
                     for(int j = 0; j< im[i].size(); j++){
                             double temp = im[i][j];
                             temp += v[i][j];
                             if(temp > TIFF_UP) temp = TIFF_UP;
                             if(temp < TIFF_DOWN) temp = TIFF_DOWN;
                             im[i][j] = temp;  
                     }
             }   
             return *this;                              
       }
       
       image  operator=(image &tim){
              im = tim.getImage();
              noise = tim.getNoise();
	          if(!im.empty()){
  	    	                  this->width = im[0].size();
            	              this->height = im.size();
               }
	           op_im = (tim.getOp_im()).clone();
	           op_noise = (tim.getOp_noise()).clone();
	           op_width = op_im.cols;
	           op_height = op_im.rows;            
               return *this;                     
       }
       
       image  operator+(image &tim){
              image out(*this);
              out += tim;         
              return out;                     
       }
       
       std::vector< std::vector<double> >  operator*(const double &jj){
             std::vector< std::vector<double> > v;
             for(int i = 0; i < im.size(); i++){
                     std::vector<double> temp;
                     for(int j = 0; j< im[0].size(); j++){
                             double value = im[i][j] * jj;
                             temp.push_back(value);
                     }
                     v.push_back(temp);
             }
             return v;                     
       }

       std::vector< std::vector<double> >  operator*(const std::vector< std::vector<pre> > &jj){
             std::vector< std::vector<double> > v;
             for(int i = 0; i < im.size(); i++){
                     std::vector<double> temp;
                     for(int j = 0; j< im[0].size(); j++){
                             double value = im[i][j] * jj[i][j];
                             temp.push_back(value);
                     }
                     v.push_back(temp);
             }
             return v;                      
       }

       std::vector< std::vector<double> >  operator/(const double &jj){
             std::vector< std::vector<double> > v;
             for(int i = 0; i < im.size(); i++){
                     std::vector<double> temp;
                     for(int j = 0; j< im[0].size(); j++){
                             double value = im[i][j] / jj;
                             temp.push_back(value);
                     }
                     v.push_back(temp);
             }
             return v;                     
       }
       
       std::vector< std::vector<double> >  operator/(const std::vector< std::vector<pre> > &jj){
             std::vector< std::vector<double> > v;
             for(int i = 0; i < im.size(); i++){
                     std::vector<double> temp;
                     for(int j = 0; j< im[0].size(); j++){
                             double value = im[i][j] / jj[i][j];
                             temp.push_back(value);
                     }
                     v.push_back(temp);
             }
             return v;                      
       }
       
///////////////////////////////////////////////////////////////////////////
       
private:
      std::vector< std::vector<pre> > im;
      pre width;
      pre height;
      std::vector< std::vector<pre> > noise;

///////////////////////////////////////////
public:
	cv::Mat getOp_im();
	void setOp_im(cv::Mat &);
	pre getOp_width();
    pre getOp_height();
	cv::Mat getOp_noise();
	void setOp_noise(cv::Mat &);
    long double opLaplacianGradient();	
	void op_print();
private:
	cv::Mat op_im;
	pre op_width;
    pre op_height;
	cv::Mat op_noise;
///////////////////////////////////////////

private:
        std::string filename;
        unsigned short slide;
        unsigned short lane;
        unsigned short field;
        unsigned int tile;//block
        long id;
};

}

#include "slide.hpp"
using namespace IMAGE;

#endif
