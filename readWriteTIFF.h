/*
 * @kangkang
 */
#ifndef _READ_WRITE_TIFF_H_
#define _READ_WRITE_TIFF_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>


#include "tiffio.h"


//////////////////////////////////////////////////////
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
////////////////////////////////////////////////////////


#ifndef _CH_
#define _CH_
#define CH " "
#endif

#ifndef _PRE_
#define _PRE_
typedef unsigned short int pre;
#endif

class readWriteTIFF{
  
   
public:
       readWriteTIFF(){
		               width = 0;
		               height = 0;
       }
       ~readWriteTIFF(){
            im.clear();
       }

       
public:      
      void print() const;
      void setIm(const std::vector< std::vector<pre> > &);
      std::vector< std::vector<pre> > getIm();

public:      
      std::vector< std::vector<pre> > load(const std::string &);
      std::vector< std::vector<pre> > load_txt(const std::string &);
      void save(const std::string &) const;
      void save_txt(const std::string &);
          

private:
      std::vector< std::vector<pre> > im;
      unsigned int width;
      unsigned int height;
      const static int BUF_SIZE = 1024 * 4;


///////////////////////////////////////////////////////
public:
	cv::Mat op_load(const std::string &);
	void op_save(const std::string &);
	void setOp_im(const cv::Mat &);
	cv::Mat getOp_im();
	void op_print();
private:
	cv::Mat  op_im;
    unsigned int op_width;
	unsigned int op_height;
///////////////////////////////////////////////////////

};

#endif
