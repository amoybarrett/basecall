/*
 * @kangkang
 */
#include "gaussWeighting.h"

using namespace std;
using namespace cv;

void gaussWeighting::one(){
         double sum = 0;
         for(register short i = 0; i < gsize; i++){

              for(register short j = 0; j < gsize; j++){

                 sum += gaussKernel[i][j];    

              }             

         }
         
         for(register short i = 0; i < gsize; i++){

              for(register short j = 0; j < gsize; j++){

                 gaussKernel[i][j] /= sum;    

              }             

         }	
}
 
void gaussWeighting::gaussFun(float a0){
         float x0 = round(gsize / 2.0) - 1;
         float y0 = round(gsize / 2.0) - 1; 
         for(register short i = 0; i < gsize; i++){
              for(register short j = 0; j < gsize; j++){
                 gaussKernel[i][j] = 1.0/(sqrt(2 * PI) * a0) * exp(-((i - y0) * (i - y0) + (j - x0) * (j - x0)) / 2.0 / (a0 * a0));    
              }             
         }
         one();
}

void gaussWeighting::mr(float a0){
         float x0 = round(gsize / 2.0) - 1;
         float y0 = round(gsize / 2.0) - 1; 
         for(register short i = 0; i < gsize; i++){
              for(register short j = 0; j < gsize; j++){
                 //gaussKernel[i][j] = 1 / (sqrt(2 * PI) * pow(a0, 3)) * (1 - ((i - y0) * (i - y0) + (j - x0) * (j - x0)) / (a0 * a0)) * exp(-((i - y0) * (i - y0) + (j - x0) * (j - x0)) / 2.0 / (a0 * a0));
                 gaussKernel[i][j] = 1.0/(PI * pow(a0, 4)) * (1 - ((i - y0) * (i - y0) + (j - x0) * (j - x0)) / (2 * a0 * a0)) * exp(-((i - y0) * (i - y0) + (j - x0) * (j - x0)) / 2.0 / (a0 * a0));    
              }             
         }
}

void gaussWeighting::filter(image& im){//±ßÔµ²åÖµÔÙÂË²¨ 

     vector< vector<pre> > v = im.getImage();
     vector< vector<pre> > out(v);

     mr(segma);/////////////////////////////////////////////////////////////////
     //gaussFun(segma);/////////////////////////////////////////////////////////////
     print();
     for(int i = 0; i < v.size(); i++){
             for(int j = 0; j < v[i].size(); j++){
                     double temp = 0;
                     for(int k1 = 0; k1 < gsize; k1++){
                             for(int k2 = 0; k2 < gsize; k2++){
                                     if(i + k1 - gsize/2 >= 0 && i + k1 - gsize/2 < v.size() && j + k2 - gsize/2 >= 0 && j + k2 - gsize/2 < v[i].size())
                                          temp += gaussKernel[k1][k2] * v[i + k1 - gsize/2][j + k2 - gsize/2];        
                             }        
                     }  
		     long tu = round(temp);
		     if(tu > TIFF_UP){tu = TIFF_UP;}else if(tu < TIFF_DOWN){tu = TIFF_DOWN;}
                     out[i][j] = tu;     
             }        
     }
     im.setImage(out);

}

void gaussWeighting::op_filter(image &im){
    Mat ig = im.getOp_im();
    GaussianBlur(ig, ig, Size(gsize,gsize), 1, segma);////////////////////
    im.setOp_im(ig);
}


/*
#include "image.h"
#include "readWriteTIFF.h"
using namespace std;
int main(){
    readWriteTIFF rwt;
    rwt.load("test_check_dnb9.tif");
    image im(rwt);
    gaussWeighting gw;
    gw.print();
    gw.filter(im);
    vector< vector< pre > > temp = im.getImage();
    rwt.setIm(temp);
    rwt.save("test_res.tif");
}
*/
