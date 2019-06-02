/*
 * @kangkang
 */
#include "erodeDilate.h"

////////////////////////////////////////
using namespace cv;
using namespace std;
////////////////////////////////////////


pre erodeDilate::winMin(const vector< vector<pre> > &v, long t1, long t2, long t3, long t4){
     pre mini = TIFF_UP;
     for(long i = t1; i <= t2; i++){
              for(long j = t3; j <= t4; ++j){
                       if(v[i][j] < mini){
                                   mini = v[i][j];
                       }
              }
     }            
     return mini;
}

void erodeDilate::erode(image &im){
	vector< vector<pre> > v = im.getImage();
	vector< vector<pre> > noise;
	pre mini = TIFF_DOWN;
	short middle = floor(winsize / 2);
	long m = v.size() - 1;
	long n = v[0].size() - 1;
	for(long i = 0; i < v.size(); i++){
             vector<pre> temp;
             for(long j = 0; j < v[i].size(); j++){
                      int imin = i - middle>0?i-middle:0;
                      int imax = i + middle<m?i+middle:m;
                      int jmin = j - middle>0?j-middle:0;
                      int jmax = j + middle<n?j+middle:n;
                      mini=winMin(v, imin, imax, jmin, jmax);  
                      temp.push_back(mini);               
             }
             noise.push_back(temp);
    }
    im -= noise;
    im.setNoise(noise);
}



void erodeDilate::op_erode(image &im){
     Mat bg;
     Mat src = im.getOp_im();
     Mat element = getStructuringElement(MORPH_RECT, Size(winsize, winsize));
     cv::erode(src, bg, element);
     src=src - bg;
     im.setOp_im(src);
     im.setOp_noise(bg);
}

