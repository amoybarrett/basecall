#include "constrast.h"

std::vector<double> constrast::run(cv::Mat& image, int di, int ui, int dj, int uj){
     double jfcv = 0;
     double jfcjv = 0;
     double tdv = 0;
     double zxgv = 0;
     double zzcv = 0;
     double xxsv = 0;
     double hmse = 0;
     double hsnr = 0;
     double mse = 0;
     double snr = 0;
     double psnr = 0;
     
     int si = ui - di;
     int sj = uj - dj;
     
////////////////////////////////////////////////////////////////////////////////
     double meanv = 0;
     for(int i = di; i < ui; i++){
             for(int j = dj; j < uj; j++){
                     meanv += image.at<dt>(i,j);      
             }        
     }
     meanv /= (si * sj);
     for(int i = di; i < ui; i++){
             for(int j = dj; j < uj; j++){
                     jfcv += (image.at<dt>(i,j) - meanv) * (image.at<dt>(i,j) - meanv);      
             }        
     }     
     jfcv /= (si * sj);
     jfcjv = jfcv * meanv;
////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////   
     cv::Mat dst;                                                                         
     Laplacian(image,dst,image.depth());      
     for(int i = di; i < ui; i++){
             for(int j = dj; j < uj; j++){
                     tdv += std::abs(dst.at<dt>(i,j));      
             }        
     }     
     tdv /= (si * sj);
     
////////////////////////////////////////////////////////////////////////////////  

////////////////////////////////////////////////////////////////////////////////   
     double v1 = 0;
     double v2 = 0;                                                                                       
     for(int i = di; i < ui - 1; i++){
             for(int j = dj; j < uj; j++){
                     v1 += image.at<dt>(i,j) * image.at<dt>(i + 1,j);      
             }        
     }     
     for(int i = di; i < ui - 2; i++){
             for(int j = dj; j < uj; j++){
                     v2 += image.at<dt>(i,j) * image.at<dt>(i + 2,j);      
             }        
     }
     zxgv = (v1 - v2) / (si * sj);
////////////////////////////////////////////////////////////////////////////////  
  
////////////////////////////////////////////////////////////////////////////////   
     double maxv = -1;
     double minv = 1e100;                                                                                       
     for(int i = di; i < ui; i++){
             for(int j = dj; j < uj; j++){
                     if(image.at<dt>(i,j) > maxv){
                         maxv = image.at<dt>(i,j);                      
                     }     
                      if(image.at<dt>(i,j) < minv){
                         minv = image.at<dt>(i,j);                      
                     }                    
             }        
     }     
     zzcv = (maxv - minv) / maxv;
//////////////////////////////////////////////////////////////////////////////// 


////////////////////////////////////////////////////////////////////////////////   
     std::vector<double> hist(number, 0);                                                                                                                                                                  
     for(int i = di; i < ui; i++){
             for(int j = dj; j < uj; j++){ 
                     for(int k = 0; k < number; k++){
                             if(image.at<dt>(i,j) >= (maxv - minv) / number * k && image.at<dt>(i,j) < (maxv - minv) / number * (k + 1)) 
                                   hist[k]++;       
                     }            
             }        
     }     
     for(int i = 0; i < number; i++){
             hist[i] /= (si * sj); 
             if(hist[i] != 0)
                        xxsv = xxsv - hist[i] * std::log(hist[i]);      
     }
////////////////////////////////////////////////////////////////////////////////    
 
////////////////////////////////////////////////////////////////////////////////   
     double fr = 0;
     double fc = 0;                                                                                                                                                                 
     for(int i = di; i < ui; i++){
             for(int j = dj + 1; j < uj; j++){ 
                     fr = fr + (image.at<dt>(i,j) - image.at<dt>(i,j - 1)) * (image.at<dt>(i,j) - image.at<dt>(i,j - 1));        
             }        
     }    
     for(int i = di + 1; i < ui; i++){
             for(int j = dj; j < uj; j++){ 
                     fc = fc + (image.at<dt>(i, j) - image.at<dt>(i - 1, j)) * (image.at<dt>(i, j) - image.at<dt>(i - 1,j));        
             }        
     }  
     fr = std::sqrt(fr / (si * sj));
     fc = std::sqrt(fc / (si * sj));
     double c = std::sqrt(fr * fr + fc * fc);
     c = 2.6 * (0.0192 + 0.114 * c) * std::pow(E, 0 - (0.114 * c) * 1.1);
     hmse = c * jfcv;
     hsnr = 10 * std::log10( N * N / hmse);
////////////////////////////////////////////////////////////////////////////////  

////////////////////////////////////////////////////////////////////////////////       
     for(int i = di; i < ui; i++){
             for(int j = dj; j < uj; j++){      
                     mse += image.at<dt>(i, j) * image.at<dt>(i, j);
             }
     }
     mse /= (si * sj);
     snr = jfcv / mse;
     psnr = 10 * log10(N * N / mse);  
     
     
     std::vector<double> out;
     out.push_back(jfcv);
     out.push_back(jfcjv);
     out.push_back(tdv);
     out.push_back(zxgv);
     out.push_back(zzcv); 
     out.push_back(xxsv); 
     out.push_back(mse);
     out.push_back(psnr);
     out.push_back(snr);   
     out.push_back(hmse);
     out.push_back(hsnr);
     
     return out;
   
}

cv::Mat constrast::one(cv::Mat& image){
     cv::Mat image_new(image.rows, image.cols, CV_32F); 
     /*/////////////////////////////////////////////////////////////////////////
     double maxv = -1, minv = 1e100;
     for(int i = 0; i < image.rows; i++){
             for(int j = 0; j < image.cols; j++){
                     if(image.at<unsigned short int>(i, j) < minv)
                                        minv = image.at<unsigned short int>(i, j);
                     if(image.at<unsigned short int>(i, j) > maxv)
                                        maxv = image.at<unsigned short int>(i, j);      
             }        
     }
     
     for(int i = 0; i < image.rows; i++){
             for(int j = 0; j < image.cols; j++){
                     image_new.at<dt>(i, j) = (image.at<unsigned short int>(i, j) - minv) * 1.0 / (maxv - minv) * 100;  
             }        
     }    
     *//////////////////////////////////////////////////////////////////////////
     cv::Mat bg;
     cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(window, window));
     cv::erode(image, bg, element);
     for(int i = 0; i < image.rows; i++){
             for(int j = 0; j < image.cols; j++){
                     image_new.at<dt>(i, j) = (image.at<unsigned short>(i, j) - bg.at<unsigned short>(i, j)) * 1.0 / (bg.at<unsigned short>(i, j) + 1e-10);
             }        
     }       
     return image_new; 
}

std::vector<double> constrast::evaluate(cv::Mat& image){
     cv::Mat image_new = one(image);
     std::vector<double> temp = run(image_new, 0, image.rows, 0, image.cols);
     
     double jfcv = temp[0];
     double jfcjv = temp[1];
     double tdv = temp[2];
     double zxgv = temp[3];
     double zzcv = temp[4];
     double xxsv = temp[5];
     double mse = temp[6];
     double psnr = temp[7];
     double snr = temp[8];
     double hmse = temp[9];
     double hsnr = temp[10];
     
     
     return temp;     
}

std::vector<double> constrast::subEvaluate(cv::Mat& image){
     cv::Mat image_new = one(image);  
     double jfcv = 0;
     double jfcjv = 0;
     double tdv = 0;
     double zxgv = 0;
     double zzcv = 0;
     double xxsv = 0;
     double hmse = 0;
     double hsnr = 0;
     double mse = 0;
     double snr = 0;
     double psnr = 0;
     double counter = 0;
     
     for(int i = 0; i < image_new.rows; i+=window){
             int ui = i + window > image_new.rows - 1 ?  image_new.rows - 1 : i + window;
             for(int j = 0; j < image_new.cols; j+=window){
                  int uj = j + window > image_new.cols - 1 ? image_new.cols - 1 : j + window;
                  std::vector<double> temp =  run(image_new, i, ui, j, uj);  
                  jfcv += temp[0];
                  jfcjv += temp[1];
                  tdv += temp[2];
                  zxgv += temp[3];
                  zzcv += temp[4]; 
                  xxsv += temp[5]; 
                  mse += temp[6];
                  psnr += temp[7];
                  snr += temp[8]; 
                  hmse += temp[9];
                  hsnr += temp[10]; 
                  counter++;                       
             }
     }
     
     jfcv /= counter;
     jfcjv  /= counter;
     tdv  /= counter;
     zxgv  /= counter;
     zzcv  /= counter; 
     xxsv  /= counter; 
     mse  /= counter;
     psnr  /= counter;
     snr  /= counter; 
     hmse  /= counter;
     hsnr  /= counter;
            
     
     std::vector<double> out;
     out.push_back(jfcv);
     out.push_back(jfcjv);
     out.push_back(tdv);
     out.push_back(zxgv);
     out.push_back(zzcv); 
     out.push_back(xxsv); 
     out.push_back(mse);
     out.push_back(psnr);
     out.push_back(snr);   
     out.push_back(hmse);
     out.push_back(hsnr);
     
     return out;                  
}

int main(void){
    std::vector<cv::Mat> aim;
    
    
    cv::Mat im1 = cv::imread("test_check_dnb1.tif");
    aim.push_back(im1);
    cv::Mat im2 = cv::imread("test_check_dnb9.tif");
    aim.push_back(im2);
    
    
    constrast cst;
    std::vector< std::vector<double> > res1, res2;
    
    for(int i = 0; i < aim.size(); i++){
            std::vector<double> t1;
            std::vector<double> t2;
            cv::Mat im = aim[i];
            t1 = cst.evaluate(im);
            t2 = cst.subEvaluate(im);
            res1.push_back(t1);
            res2.push_back(t2);
    }
    
    std::cout<<"T1"<<std::endl;
    std::cout<<"jfcv(U)\tjfcjv(U)\ttdv(U)\tzxgv(U)\tzzcv(U)\txxsv(U)\thmse(D)\thsnr(U)\tmse(U)\tsnr(U)\tpsnr(D)"<<std::endl;
    for(int i = 0; i < aim.size(); i++){
       std::vector<double> temp = res1[i];
       double jfcv = temp[0];
       double jfcjv = temp[1];
       double tdv = temp[2];
       double zxgv = temp[3];
       double zzcv = temp[4];
       double xxsv = temp[5];
       double mse = temp[6];
       double psnr = temp[7];
       double snr = temp[8];
       double hmse = temp[9];
       double hsnr = temp[10];
       std::cout<<jfcv<<"\t"<<jfcjv<<"\t"<<tdv<<"\t"<<zxgv<<"\t"<<zzcv<<"\t"<<xxsv<<"\t"<<hmse<<"\t"<<hsnr<<"\t"<<mse<<"\t"<<snr<<"\t"<<psnr<<std::endl;
    }
    
    
    std::cout<<"T2"<<std::endl;
    std::cout<<"jfcv(U)\tjfcjv(U)\ttdv(U)\tzxgv(U)\tzzcv(U)\txxsv(U)\thmse(D)\thsnr(U)\tmse(U)\tsnr(U)\tpsnr(D)"<<std::endl;
    for(int i = 0; i < aim.size(); i++){
       std::vector<double> temp = res2[i];
       double jfcv = temp[0];
       double jfcjv = temp[1];
       double tdv = temp[2];
       double zxgv = temp[3];
       double zzcv = temp[4];
       double xxsv = temp[5];
       double mse = temp[6];
       double psnr = temp[7];
       double snr = temp[8];
       double hmse = temp[9];
       double hsnr = temp[10];
       std::cout<<jfcv<<"\t"<<jfcjv<<"\t"<<tdv<<"\t"<<zxgv<<"\t"<<zzcv<<"\t"<<xxsv<<"\t"<<hmse<<"\t"<<hsnr<<"\t"<<mse<<"\t"<<snr<<"\t"<<psnr<<std::endl;
    }
    
    return 0;    
}
