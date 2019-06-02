/*
 * @kangkang,9个参数 ,6个参数 
 */
#include "affineTransformation.h"

using namespace std;
using namespace cv;

void affineTransformation::affine(image &im){
	    Mat img = im.getOp_im();
	    int img_height = img.rows;
	    int img_width = img.cols;
	    vector<Point2f> corners(4);
    	corners[0] = Point2f(0,0);  
    	corners[1] = Point2f(img_width-1,0);  
    	corners[2] = Point2f(0,img_height-1);  
    	corners[3] = Point2f(img_width-1,img_height-1);  
    	vector<Point2f> corners_trans(4);  
    	corners_trans[0] = Point2f(0,0);  
    	corners_trans[1] = Point2f(img_width-1,0);  
    	corners_trans[2] = Point2f(0,img_height-1);  
    	corners_trans[3] = Point2f(img_width-1,img_height-1);	
    	transform = getPerspectiveTransform(corners,corners_trans);  
 	    Mat imageturn;
	    warpPerspective(img,imageturn, transform, cv::Size(img.rows,img.cols)/*img.size()*/, INTER_LINEAR);
	    im.setOp_im(imageturn);
} 

void affineTransformation::affine2(image &im, Mat &warp_mat){
     vector< vector<pre> > v = im.getImage();
     Mat tim = image::vectorToMat(v);
     
     Mat warp_dst = Mat::zeros( tim.rows, tim.cols, tim.type() ); 
     warpAffine( tim, warp_dst, warp_mat, warp_dst.size(), INTER_LINEAR);///////////////////////////////////  
     
     v = image::matToVector(warp_dst);
     im.setImage(v);  
}

image affineTransformation::rotate(image &im, double angle, double scale){
     vector< vector<pre> > v = im.getImage();
     Mat tim = image::vectorToMat(v);
     
     Point2f center = Point2f(tim.cols / 2, tim.rows / 2); 
     Mat warp_mat( 2, 3, CV_32FC1 ); 
     warp_mat = getRotationMatrix2D(center, angle, scale); 
     
     Mat warp_dst = Mat::zeros( tim.rows, tim.cols, tim.type() ); 
     warpAffine( tim, warp_dst, warp_mat, warp_dst.size(), INTER_LINEAR);  
     
     v = image::matToVector(warp_dst);
     im.setImage(v);
     return im; 
}

///////////////////////////////////////////////////////////
void affineTransformation::translation(image &im, pair<int, int> r){
    int x = r.first;
    int y = r.second;
    vector< vector<pre> > v = im.getImage();
    vector< vector<pre> > noise = im.getNoise();
    vector< vector<pre> > rnoise = noise;
    vector< vector<pre> > res = v;
    for(long i = 0; i < v.size(); i++){
             for(long j = 0; j < v[i].size(); j++){
                  if(i - y >= 0 && i - y < v.size() && j - x >= 0 && j - x < v[i].size()){
                       res[i][j] = v[i - y][j - x];
                       if(rnoise.size() != 0)
                              rnoise[i][j] = noise[i - y][j - x];     
                  }else{
                        res[i][j] = 0;  
                        if(rnoise.size() != 0)    
                              rnoise[i][j] = 0;
                  }         
             }         
    } 
    im.setImage(res);
    if(rnoise.size() != 0)
                     im.setNoise(rnoise);
}
////////////////////////////////////////////////////////////////

/*
#include "affineTransformation.h"
#include "readWriteTIFF.h"
#include "image.h"


using namespace std;
using namespace cv;

int main(void){
    readWriteTIFF rwt;
    rwt.op_load("test_check_dnb1.tif");
    image im(rwt);
    affineTransformation atf;
    atf.affine(im);
    Mat op_im = im.getOp_im();
    rwt.setOp_im(op_im);
    rwt.op_save("test_check_dnb1_res.tif");
}
*/
