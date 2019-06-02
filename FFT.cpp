/*
 * @kangkang,结合旋转，缩放两个参数|仿射变换|，通过循环找出或者采样给出 
 */
#include "FFT.h"


using namespace std;
using namespace cv;

pair<int, int> FFT::minMax(image &im1, image &im2 , bool flag){
   
vector< vector<pre> > t1 = im1.getImage();
vector< vector<pre> > t2 = im2.getImage();   
 
if(t1.size() != t2.size() || t1[0].size() != t2[0].size()){
             printf("FFT SIZE MUST EQUAL!\n");
             exit(0);             
}               

int m_x_dim = t1.size();
int m_y_dim = t1[0].size();

double* m_image_in   = (double*) fftw_malloc(sizeof(double) * m_x_dim * m_y_dim);
double* m_image_other   = (double*) fftw_malloc(sizeof(double) * m_x_dim * m_y_dim);

fftw_complex *m_fft_out    = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * m_x_dim * (m_y_dim/2+1));
fftw_complex *m_fft_other    = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * m_x_dim * (m_y_dim/2+1));

fftw_plan m_plan_forward = fftw_plan_dft_r2c_2d(m_x_dim, m_y_dim, m_image_in, m_fft_out, FFTW_MEASURE); 
fftw_plan m_plan_forward_other = fftw_plan_dft_r2c_2d(m_x_dim, m_y_dim, m_image_other, m_fft_other, FFTW_MEASURE); 

fftw_complex *m_cross = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * m_x_dim * (m_y_dim/2+1));
double* m_correl_out = (double*) fftw_malloc(sizeof(double) * m_x_dim * m_y_dim);

fftw_plan m_plan_reverse = fftw_plan_dft_c2r_2d(m_x_dim, m_y_dim, m_cross, m_correl_out, FFTW_MEASURE); 


    for (int x=0; x<m_x_dim; x++) {

      for (int y=0; y<m_y_dim; y++) {
        m_image_in[x*m_y_dim+y] = t1[x][y];
      }

    }
 
    for (int x=0; x<m_x_dim; x++) {

      for (int y=0; y<m_y_dim; y++) {
        m_image_other[x*m_y_dim+y] = t2[x][y];
      }

    } 
    
fftw_execute (m_plan_forward);
fftw_execute (m_plan_forward_other);

   int y_out_dim = m_y_dim/2+1;  
    
   for (int ix=0; ix<m_x_dim*y_out_dim; ix++) {

      m_cross[ix][0] = m_fft_out[ix][0]*m_fft_other[ix][0]     
                     + m_fft_out[ix][1]*m_fft_other[ix][1];
      m_cross[ix][1] = m_fft_out[ix][1]*m_fft_other[ix][0]
                     - m_fft_out[ix][0]*m_fft_other[ix][1];

    }

    fftw_execute (m_plan_reverse);                       

    double max_value = -1e10;
    int max_x = -1;
    int max_y = -1;


    double min_value = 1e300;
    int min_x = -1;
    int min_y = -1;


    for (int y=0; y<m_y_dim; y++) {
      for (int x=0; x<m_x_dim; x++) {

        int index = x*m_y_dim+y;

        if (m_correl_out[index] > max_value) { 
          max_value = m_correl_out[index];
          max_x = x;
          max_y = y;
          
        }
        if (m_correl_out[index] < min_value) { 
          min_value = m_correl_out[index];
          min_x = x;
          min_y = y;
          
        }
      }
    }
  
    fftw_destroy_plan(m_plan_forward);
    fftw_destroy_plan(m_plan_reverse);
    fftw_destroy_plan(m_plan_forward_other);
    fftw_free(m_image_in);
    fftw_free(m_image_other);
    fftw_free(m_correl_out);
    fftw_free(m_fft_out);
    fftw_free(m_fft_other);
    fftw_free(m_cross);
  
    int out_x, out_y;
    if (max_x > m_x_dim/2) {              
      out_x = max_x - m_x_dim;
    } else {
      out_x = max_x;
    }
    if (max_y > m_y_dim/2) {
      out_y = max_y - m_y_dim;
    } else {
      out_y = max_y;
    }
    
    pair<int, int> out1;
    out1 = make_pair(out_y, out_x);

    if (min_x > m_x_dim/2) {              
      out_x = min_x - m_x_dim;
    } else {
      out_x = min_x;
    }
    if (min_y > m_y_dim/2) {
      out_y = min_y - m_y_dim;
    } else {
      out_y = min_y;
    }

    pair<int, int> out2;
    out2 = make_pair(out_y, out_x);
    
    if(flag) return out1;
    else return out2;	
       
}
//////////////////////////////////////////////////

//////////////////////////////////////////////////
fftw_complex* FFT::fFFT(image &im){
              fftw_plan p;
              vector< vector<pre> > v = im.getImage();              
              fftw_complex *out;
              out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * v.size() * v[0].size());
              double* temp = new double[v.size() * v[0].size()];
              float counter = 0;
              for (int i = 0; i < v.size(); ++i)
              {
                  for(int j = 0; j < v[0].size(); j++){
                      temp[(int)counter] = v[i][j];   
                  }
                  counter++;
              }
              p = fftw_plan_dft_r2c_2d(v.size(), v[0].size(), temp, out, FFTW_ESTIMATE);  
              fftw_execute(p);
              fftw_destroy_plan(p);
              return out;
}

double* FFT::rFFT(fftw_complex *f, int m, int n){
             fftw_plan p;
             double * out;
             p = fftw_plan_dft_c2r_2d(m, n, f, out, FFTW_ESTIMATE);
             return out;           
}

void FFT::op_fFFT(image &im){
    Mat temp = im.getOp_im();
    Mat padded;
    int m = getOptimalDFTSize(temp.rows);  // Return size of 2^x that suite for FFT
    int n = getOptimalDFTSize(temp.cols);

    copyMakeBorder(temp, padded, 0, m-temp.rows, 0, n-temp.cols, BORDER_CONSTANT, Scalar::all(0));

    // Create planes to storage REAL part and IMAGE part, IMAGE part init are 0
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);

    dft(complexI, complexI);
    // compute the magnitude and switch to logarithmic scale
    split(complexI, planes);
    
    magnitude(planes[0], planes[0], planes[1]);
    Mat magI = planes[0];

    // => log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
    magI += Scalar::all(1);
    log(magI, magI);    
}

void FFT::op_rFFT(Mat &complexI){
     Mat invDFT, invDFTcvt;    
     idft(complexI, invDFT, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT );
     invDFT.convertTo(invDFTcvt, CV_16U); 
}
/////////////////////////////////////////////////

/*
#include "readWriteTIFF.h"
#include "image.h"
#include "FFT.h"
#include "affineTransformation.h"

int main(void){
    readWriteTIFF rwt1;
    rwt1.load("test_cluster.tif");
    image im1(rwt1);
    image im2(rwt1);
    
    affineTransformation aff;
    pair<int, int> t = make_pair(-10, 5);
    aff.translation(im2, t);  
    
    FFT fft; 
    pair<int, int> xy = fft.minMax(im1, im2, true);
    cout<<"Offset:("<<xy.first<<","<<xy.second<<")"<<endl;
   
    affineTransformation atf;
    atf.translation(im2, xy);

    xy = fft.minMax(im1, im2, true);
    cout<<"Offset:("<<xy.first<<","<<xy.second<<")"<<endl;
   
    return 0;    
}
*/

