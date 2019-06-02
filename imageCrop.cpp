/*
 * @kangkang,×îºÃÕû±¶²Ã¼ô
 */
 
#include "imageCrop.h"

using namespace std;

vector< vector<image> > imageCrop::subimage(vector<image> &ima){
       vector< vector<image> > out(ima.size());
       for(int i = 0; i < ima.size(); i++){
               vector< vector<pre> > fim = ima[i].getImage();
               vector< vector<pre> > noise = ima[i].getNoise();
               for(int t1 = 0; t1 + cheight <= fim.size(); t1 += cheight){
                       for(int t2 = 0; t2 + cwidth <= fim[t1].size(); t2 += cwidth){
                              vector< vector<pre> > oi;
                              vector< vector<pre> > on;
                              for(int k1 = t1; k1 < t1 + cheight; k1++){
                                      vector<pre> oit; 
                                      vector<pre> ont;
                                      for(int k2 = t2; k2 < t2 + cwidth; k2++){
                                           oit.push_back(fim[k1][k2]);
                                           if(noise.size() != 0) ont.push_back(noise[k1][k2]);          
                                      }        
                                      oi.push_back(oit);
                                      if(noise.size() != 0) on.push_back(ont);
                              }  
                              image im;
                              im.setImage(oi);
                              if(noise.size() != 0)
                                              im.setNoise(on);
                              out[i].push_back(im);                                  
                       }                      
               } 
               if(fim.size() % cheight != 0){
                   for(int t2 = 0; t2 + cwidth <= fim[0].size(); t2 += cwidth){
                             vector< vector<pre> > oi;
                             vector< vector<pre> > on;
                             for(int k1 = (fim.size() / cheight) * cheight; k1 < fim.size(); k1++){
                                  vector<pre> oit; 
                                  vector<pre> ont;
                                  for(int k2 = t2; k2 < t2 + cwidth; k2++){
                                      oit.push_back(fim[k1][k2]);
                                      if(noise.size() != 0) ont.push_back(noise[k1][k2]);            
                                  }  
                                  oi.push_back(oit);
                                  if(noise.size() != 0) on.push_back(ont);                                         
                             }
                             image im;
                             im.setImage(oi);
                             if(noise.size() != 0) 
                                             im.setNoise(on); 
                             out[i].push_back(im);  
                   }           
               }    
               if(fim[0].size() % cwidth != 0){
                   for(int t1 = 0; t1 + cheight <= fim.size(); t1 += cheight){
                             vector< vector<pre> > oi;
                             vector< vector<pre> > on;
                             for(int k1 = t1; k1 < t1 + cheight; k1++){
                                  vector<pre> oit; 
                                  vector<pre> ont;
                                  for(int k2 = (fim[k1].size() / cwidth) * cwidth; k2 < fim[k1].size(); k2++){
                                      oit.push_back(fim[k1][k2]);
                                      if(noise.size() != 0) ont.push_back(noise[k1][k2]);            
                                  }  
                                  oi.push_back(oit);
                                  if(noise.size() != 0) on.push_back(ont);                                         
                             }
                             image im;
                             im.setImage(oi);
                             if(noise.size() != 0) 
                                             im.setNoise(on); 
                             out[i].push_back(im); 
                   }            
               }
               if(fim.size() % cheight != 0 && fim[0].size() % cwidth != 0){
                             vector< vector<pre> > oi;
                             vector< vector<pre> > on;
                             for(int k1 = (fim.size() / cheight) * cheight; k1 < fim.size(); k1++){
                                  vector<pre> oit; 
                                  vector<pre> ont;
                                  for(int k2 = (fim[k1].size() / cwidth) * cwidth; k2 < fim[k1].size(); k2++){
                                      oit.push_back(fim[k1][k2]);
                                      if(noise.size() != 0) ont.push_back(noise[k1][k2]);            
                                  }  
                                  oi.push_back(oit);
                                  if(noise.size() != 0) on.push_back(ont);                                         
                             }
                             image im;
                             im.setImage(oi);
                             if(noise.size() != 0) 
                                             im.setNoise(on); 
                             out[i].push_back(im);                              
               }            
       } 
       
       return out;
}

vector< vector<image> > imageCrop::subimage2(vector<image> &ima, vector< vector< vector< pair<int, int> > > > &cross){
    vector< vector<image> > out(ima.size());
    for(int i = 0; i < ima.size(); i++){
       vector< vector<pre> > fim = ima[i].getImage();
       vector< vector<pre> > noise = ima[i].getNoise();
       for(int j = 0; j < cross[i].size(); j++){
               pair<int, int> x1 = cross[i][j][0];
               pair<int, int> y1 = cross[i][j][1];
               pair<int, int> x2 = cross[i][j][2];
               pair<int, int> y2 = cross[i][j][3];    
               vector< vector<pre> > oi;
               vector< vector<pre> > on;
               for(int k1 = x1.first; k1 <= x2.first; k1++){
                                      vector<pre> oit; 
                                      vector<pre> ont;
                                      for(int k2 = x1.second; k2 <= y2.second; k2++){
                                           oit.push_back(fim[k1][k2]);
                                           if(noise.size() != 0) ont.push_back(noise[k1][k2]);          
                                      }        
                                      oi.push_back(oit);
                                      if(noise.size() != 0) on.push_back(ont);
                }  
                image im;
                im.setImage(oi);
                if(noise.size() != 0)
                                im.setNoise(on);
                out[i].push_back(im);                                                        
       } 
    }
    return out;
}

void imageCrop::crop(const string &infile, const string &outfile){
    

    TIFF *tif = TIFFOpen(infile.c_str(), "r");
    if (tif == NULL)
    {
        cout<<"Can't open "<<infile<<endl;
    }

//    TIFFGetField(Src, TIFFTAG_IMAGELENGTH, @Height);
//    TIFFGetField(Src, TIFFTAG_IMAGEWIDTH, @Width);
//    TIFFGetField(Src, TIFFTAG_SAMPLESPERPIXEL, @SAMPLESPERPIXEL);
//    TIFFGetField(Src, TIFFTAG_ROWSPERSTRIP, @ROWSPERSTRIP);
//    TIFFGetField(Src, TIFFTAG_StripByteCounts, @StripByteCounts);
//    TIFFGetField(Src, TIFFTAG_PHOTOMETRIC, @PHOTOMETRIC);
//    TIFFGetField(Src, TIFFTAG_COMPRESSION, @COMPRESSION);
//    TIFFGetField(Src, TIFFTAG_StripOffsets, @StripOffsets);
//    TIFFGetField(Src, TIFFTAG_PLANARCONFIG, @PLANARCONFIG);

    long twidth;
    long theight;
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &twidth);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &theight);
    

    uint32 imagelength;     
    pre *buf;            

    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imagelength);
    
    unsigned int scanlinesize = TIFFScanlineSize(tif);
    buf = static_cast<pre *>(_TIFFmalloc(TIFFScanlineSize(tif)));

    vector< vector< vector<pre> > > cim(scanlinesize / sizeof(pre) / cwidth, vector< vector<pre> >(cheight, vector<pre>(cwidth, 0)));
    
    long counter = 0;
    
    long result;
    
    for (uint32 row = 0; row < imagelength; ++row)
    {
        result = TIFFReadScanline(tif, buf, row);
        
        if (result == -1)
        {
            cout<<"Can't read image"<<endl;
        }

        pre *bp = buf;
        
        for (unsigned int n = 0; n <= (scanlinesize / sizeof(pre)); ++n)
        {
            pre val = *(static_cast<pre *>(bp));
            if((scanlinesize / sizeof(pre)) % cwidth == 0){
              cim[n / cwidth][row % cheight][n % cwidth]= val;
            }else if(n / cwidth < scanlinesize / sizeof(pre) / cwidth){
              cim[n / cwidth][row % cheight][n % cwidth]= val;    
            }
            bp++;
        }
        if(row % cheight == cheight - 1){
               for(int k = 0; k < (scanlinesize / sizeof(pre)) / cwidth; k ++){
                          counter ++;
                          stringstream temp;
                          temp << counter;
                          string of = outfile + temp.str() + ".tif";
                          save(of, cim[k]);     
               }       
        }
    }
    
    cim.clear();

    _TIFFfree(buf);

    TIFFClose(tif); 

}


void imageCrop::save(const string &oufile, std::vector< std::vector<pre> > &im) const{

  int width = im[0].size();
  int height = im.size();
    
  TIFF* tif = TIFFOpen(oufile.c_str(), "w");

  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 16);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
  TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, height);

  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
  TIFFSetField(tif, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
  TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

  TIFFSetField(tif, TIFFTAG_XRESOLUTION, 150.0);
  TIFFSetField(tif, TIFFTAG_YRESOLUTION, 150.0);
  TIFFSetField(tif, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
  
  pre *buf;
  buf = static_cast<pre *>(_TIFFmalloc(width*sizeof(pre)));
  
  for(unsigned int m=0;m<height;m++) {
	pre *bp = buf;
	for(unsigned int n=0;n<width;n++){
	    pre temp = im[m][n];
	    *bp=temp;
	    bp++;
	}
	
        TIFFWriteScanline(tif, buf, m);
  }

  _TIFFfree(buf);
  TIFFClose(tif);
}

/*
int main(void){
    imageCrop ic(350, 350);
    ic.crop("test_check_dnb1.tif", "test/test_imageCrop");
}
*/
