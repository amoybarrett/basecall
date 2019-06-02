/*
 * @kangkang
 */
 
#include "wiener.h"

using namespace cv;
using namespace std;

void wiener::filtering(image &im){
    double whole_segma = 0;
    double mu;
    double segma;
    vector< vector< pre > > vv = im.getImage();
    
    vector< vector< double > > v(vv.size(), vector<double>(vv[0].size(), 0));   
 

for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[i].size(); j++){
                        v[i][j] = vv[i][j] * 1.0 / TIFF_UP;
        }        
} 
   
    vector< vector<double> > all_mu(v.size(), vector<double>(v[0].size(), 0));
    vector< vector<double> > all_segma(v.size(), vector<double>(v[0].size(), 0));
    double size = 0;
    int tsize = gsize / 2;
    for(int i = 0; i < v.size(); i++){
            for(int j = 0 ; j < v[i].size(); j++){
                    mu = 0;
                    segma = 0;
                    double counter = 0;
                    for(int k1 = 0; k1 < gsize; k1++){
                            for(int k2 = 0; k2 < gsize; k2++){
                                    if(i+k1-tsize >= 0 && i+k1-tsize < v.size() && j + k2 - tsize >= 0 && j + k2 - tsize < v[i].size()){
                                                  mu += v[i + k1 - tsize][j + k2 - tsize]; 
                                                  counter ++;
                                    }       
                            }        
                    }     
                    mu /= counter;
                    for(int k1 = 0; k1 < gsize; k1++){
                            for(int k2 = 0; k2 < gsize; k2++){
                                    if(i+k1-tsize >= 0 && i+k1-tsize < v.size() && j + k2 - tsize >= 0 && j + k2 - tsize < v[i].size()){
                                                  segma += v[i + k1 - tsize][j + k2 - tsize] * v[i + k1 - tsize][j + k2 - tsize];
                                    }        
                            }        
                    } 
                    segma = segma / counter - mu * mu;
                    size ++;
                    all_mu[i][j] = mu;
                    all_segma[i][j] = segma;                    
            }       
    }   
    
    double sum = 0;
    for(vector< vector<double> >::iterator it = all_segma.begin(); it != all_segma.end(); it++){
                for(vector<double>::iterator itt = (*it).begin();itt != (*it).end(); itt++){
                     sum += *itt;                      
                }                                                
    }
    whole_segma = sum / size;
    
    vector< vector<double> > f(v.size(), vector<double>(v[0].size(), 0));
    vector< vector<double> > g(v.size(), vector<double>(v[0].size(), 0));
    
    
    
    for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                            f[i][j] = v[i][j] - all_mu[i][j];
                            g[i][j] = all_segma[i][j] - whole_segma;
                            if(g[i][j] < 0){
                                          g[i][j] = 0;              
                            }
                            if(all_segma[i][j] < whole_segma){
                                                  all_segma[i][j] = whole_segma;                      
                            }
            }
    }  

    for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                    f[i][j] /= all_segma[i][j]; 
            }
    }

    for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                    f[i][j] *= g[i][j]; 
            }
    }
 
    for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                    //cout<<f[i][j]<<"\t"<<all_mu[i][j]<<endl;
                    f[i][j] += all_mu[i][j]; 
            }
    }
  
    vector< vector< pre > > out = im.getImage();
    for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
            
		    long temp = round(f[i][j] * TIFF_UP);
		     if(temp > TIFF_UP){temp = TIFF_UP;}
             if(temp < TIFF_DOWN){temp = TIFF_DOWN;}
                    out[i][j] = temp; 
            }
    }    
    im.setImage(out);  
}

/*
int main(void){
        readWriteTIFF rwt;
        rwt.load("test_check_dnb9.tif");
        image im(rwt);
        wiener wn;
        wn.filtering(im);
        vector< vector<pre> > v = im.getImage();
        rwt.setIm(v);
        rwt.save("test_check_dnb9_res.tif");  
}
*/



