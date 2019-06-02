/*
 * @kangkang
 */
#include "image.h"

using namespace std;

void image::setImage(const vector< vector<pre> > &im){
     this->im = im;
     height = im.size();
     width = im[0].size();
}
vector< vector<pre> > image::getImage(){
        return this->im;
}
pre image::getWidth(){
     return this->width;
}
pre image::getHeight(){
    return this->height;
}
void image::setNoise(const vector< vector<pre> > &bgnoise){
     this->noise = bgnoise;
}
vector< vector<pre> > image::getNoise(){
        return this->noise;
}     

/////////////////////////////////////////////////////////////////////
pre** image::getArray(){
    pre **out;
    out = new pre*[im.size()];    
    for (long i = 0; i < im.size(); ++i)
    {
         out[i] = new pre[im[0].size()];
    }

      for(long int i = 0; i < im.size(); i++){
               for(long j = 0; j < im[0].size(); j++){
                        out[i][j] = im[i][j];
               }
      }
      return out;
}
double image::average(){
       double ave = (this->sum()) / (width * height);
       return ave;
}
long double image::sum(){
     long double res = 0;
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                      res += *itt;
             }    
     }
     return res;
}
pre image::max(){
     pre tmax = 0;
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                      if(tmax < *itt){
                                            tmax = *itt;
                                      }
             }    
     }
     return tmax;
}
pre image::min(){
     pre tmin;
     bool flag = true;
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                      if(flag){
                                               tmin = *itt;
                                               flag = false;
                                      }
                                      if(tmin > *itt){
                                            tmin = *itt;
                                      }
             }    
     }
     return tmin;
}

long double image::variance(){
     long double out = 0;
     vector<double> row = this->rowAve();
     vector<double> col = this->colAve();
     for(int i = 0; i < im.size(); i++){
             for(int j = 0; j < im[i].size(); j++){
                     out += abs(im[i][j] - col[j]);
                     out += abs(im[i][j] - row[i]);
             }
     }
     return out;
}
vector<pre> image::rowMax(){
     vector<pre> out(im.size(), 0);
     int counter = 0;
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                      if(out[counter] < *itt){
                                            out[counter] = *itt;
                                      }
             }    
             counter++;
     }
     return out;                 
}
vector<pre> image::rowMin(){
     vector<pre> out(im.size(), TIFF_UP);
     int counter = 0;
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                      if(out[counter] > *itt){
                                            out[counter] = *itt;
                                      }
             }    
             counter++;
     }
     return out;                 
}
vector<pre> image::colMax(){
     vector<pre> out(im[0].size(), 0);
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             int counter = 0;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt, counter++){                                       
                                      if(out[counter] < *itt){
                                            out[counter] = *itt;
                                      }
             }    
             
     }
     return out;                   
}
vector<pre> image::colMin(){
     vector<pre> out(im[0].size(), TIFF_UP);
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             int counter = 0;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt, counter++){                                       
                                      if(out[counter] > *itt){
                                            out[counter] = *itt;
                                      }
             }    
             
     }
     return out;                  
}
////////////////////////////////////////////////////////

vector<double> image::rowSum(){
     vector<double> out(im.size(), 0);
     int counter = 0;
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                            out[counter] += *itt;
             }    
             counter++;
     }
     return out;                    
}
vector<double> image::colSum(){
     vector<double> out(im[0].size(), 0);
     for(vector< vector<pre> >::iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             int counter = 0;
             for(vector<pre>::iterator itt = temp.begin(); itt != temp.end(); ++itt, counter++){                                       
                                            out[counter] += *itt;
             }    
             
     }
     return out;                   
}

long double image::LaplacianGradient(){
     op_im = vectorToMat(im);
     return opLaplacianGradient();
}

////////////////////////////////////////////////////////////
vector<double> image::rowAve(){
      vector<double> temp = this->rowSum();
      for(int i = 0; i < temp.size(); i++){
              temp[i] /= im[i].size();        
      }  
      return temp;
}
vector<double> image::colAve(){
      vector<double> temp = this->rowSum();
      for(int i = 0; i < temp.size(); i++){
              temp[i] /= im.size();        
      }  
      return temp;               
}
///////////////////////////////////////////////////////////////////////

void image::print() const{
     for(vector< vector<pre> >::const_iterator it = im.begin(); it != im.end(); ++it){
             vector<pre> temp = *it;
             for(vector<pre>::const_iterator itt = temp.begin(); itt != temp.end(); ++itt){
                                      cout<<*itt<<"\t";
             }    
             cout<<endl;
     }
}



using namespace cv;

Mat image::getOp_im(){
	return this->op_im;
}
void image::setOp_im(Mat &op_im){
	this->op_im = op_im;
	op_width = op_im.cols;
	op_height = op_im.rows;
}
pre image::getOp_width(){
	return this->op_width;
}
pre image::getOp_height(){
	return this->op_height;
}

Mat image::getOp_noise(){
	return this->op_noise;
}
void image::setOp_noise(Mat &op_noise){
	this->op_noise = op_noise;
}
void image::op_print(){
     for(int i=0; i < op_im.rows; ++i){
             for(int j=0; j < op_im.cols; ++j){
                     cout<<op_im.at<pre>(i,j)<<"\t";
             }
             cout<<endl;
     }
}

///////////////////////////////////////////
long double image::opLaplacianGradient(){
     Mat dst;
     double out = 0;
     int scale = 1;
     int delta = 0;
     int kernel_size = 3;
     int ddepth = CV_16U;
     Laplacian( op_im, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT ); 
     convertScaleAbs(dst, dst);
     for(int i=0; i < dst.rows; ++i){
             for(int j=0; j < dst.cols; ++j){
                     out += dst.at<pre>(i,j);
             }
     }    
     return out;  
}
///////////////////////////////////////////

Mat image::vectorToMat(vector< vector<pre> > &v){
    Mat out(v.size(), v[0].size(), CV_16U);
    for(long i = 0; i < v.size(); ++i){
         for(long j = 0; j < v[i].size(); j++){
                  out.at<pre>(i,j) = v[i][j];
         }    
    }
    return out;
}
vector< vector<pre> >  image::matToVector(Mat &m){
    vector< vector<pre> > out;
    for(long i = 0; i < m.rows; ++i){
             vector<pre> temp;
             for(long j = 0; j < m.cols; j++){
                      temp.push_back(m.at<pre>(i,j));         
             }         
             out.push_back(temp);
    }       
    return out;  
}
IplImage image::MatToIplImage(Mat &im){
	IplImage out = im;
	return out;
}

Mat image::IplImageToMat(IplImage *im){
	Mat out(im, false);
	return out;
}

Mat image::CvMatToMat(CvMat *im){
    Mat out(im, false);
	return out;
}

CvMat image::MatToCvMat(Mat &im){
    CvMat out = im;
	return out;
}
const CvArr* image::MatToCvArr(Mat &im){
	const  CvArr* s=(CvArr*)&im;
}
