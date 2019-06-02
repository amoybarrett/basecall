/*
 * @kangkang
 */
#include "readWriteTIFF.h"

using namespace std;

void readWriteTIFF::print() const{
	vector< vector<pre> >::const_iterator it; 
	for(it = im.begin(); it != im.end(); ++it){
		vector<pre>::const_iterator itt;
		for(itt=(*it).begin(); itt!=(*it).end(); ++itt){
			cout<<*itt<<"\t";		
		}
		cout<<endl;
	}
}
void readWriteTIFF::setIm(const vector< vector<pre> > &im){
     this->im = im;
     this->width = (this->im)[0].size();
     this->height = (this->im).size();
}
vector< vector<pre> > readWriteTIFF::getIm(){
        return this->im;
}

vector< vector<pre> > readWriteTIFF::load(const string &infile){
    im.clear();


    TIFF *tif = TIFFOpen(infile.c_str(), "r");
    if (tif == NULL)
    {
        cout<<"Can't open "<<infile<<endl;
        return im;
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


    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);


    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

    uint32 imagelength;     
    pre *buf;            

    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imagelength);
    
    //cout<<imagelength<<endl;

    long result;
    
    unsigned int scanlinesize = TIFFScanlineSize(tif);

    buf = static_cast<pre *>(_TIFFmalloc(TIFFScanlineSize(tif)));

    for (uint32 row = 0; row < imagelength; ++row)
    {
        result = TIFFReadScanline(tif, buf, row);
        
        if (result == -1)
        {
            cout<<"Can't read image"<<endl;
            return im;
        }

        pre *bp = buf;

 	    vector<pre> image;

	    image.clear();

        for (unsigned int n = 0; n < (scanlinesize / sizeof(pre)); ++n)
        {
            pre val = *(static_cast<pre *>(bp));
            image.push_back(val);
            bp++;
        }
	    im.push_back(image);
    }


    _TIFFfree(buf);

    TIFFClose(tif); 

    this->width = (this->im)[0].size();
    this->height = (this->im).size();

    return im; 
}
vector< vector<pre> > readWriteTIFF::load_txt(const string &infile){
     im.clear();
     ifstream is;
     is.open(infile.c_str(), ofstream::in);
     if(is.fail()){
         cout<<"file not exist!"<<endl;
         return im;
     }
     if(!is.is_open()){
         cout<<"file can't open!"<<endl;
         return im;
     }
     char buffer[BUF_SIZE];
     
     while(!is.eof()){
        is.getline(buffer, sizeof(buffer));
        string o_str(buffer);
        vector<pre> str_list;
        str_list.clear();
        if(o_str.length()==0){
             break;       
        }
        int comma_n = 0;
	    do
	    {
		    string tmp_s = "";
		    comma_n = o_str.find( CH );
	        if( -1 == comma_n )
		    {
			    tmp_s = o_str.substr( 0, o_str.length() );
                if(tmp_s.length()==0)
                    break;
			    str_list.push_back( atof(tmp_s.c_str()) );
			    break;
		    }
		    tmp_s = o_str.substr( 0, comma_n );
		    o_str.erase( 0, comma_n+1 );
		    str_list.push_back( atof(tmp_s.c_str()) );
      }while(true);
       im.push_back(str_list);
     }
     is.close();
     this->width = (this->im)[0].size();
     this->height = (this->im).size();
     return im;
}
void readWriteTIFF::save(const string &oufile) const{

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
void readWriteTIFF::save_txt(const string &oufile){
     ofstream os;
     os.open(oufile.c_str(), ofstream::out); 
     if(os.fail()){
         cout<<"file can't create!"<<endl;
         return ;
     }
     if(!os.is_open()){
         cout<<"file can't open!"<<endl;
         return ;
     }  
     for(vector< vector< pre > >::iterator it = im.begin(); it != im.end(); ++it){
         vector< pre > tv = *it;
         vector< pre >::iterator itt;
         for(itt = tv.begin(); itt != tv.end(); ++itt){
             os << *itt << CH;
         }
         os << "\n";
         
     }
     os.close();
}


using namespace cv;

Mat readWriteTIFF::op_load(const string &infile){
	op_im = imread(infile.c_str());
	op_width = op_im.cols;
	op_height = op_im.rows;
	return op_im;
}

void readWriteTIFF::op_save(const string &outfile){
	imwrite(outfile.c_str(), op_im);
}

void readWriteTIFF::setOp_im(const Mat & im){
	this->op_im = im;
	op_width = op_im.cols;
	op_height = op_im.rows;
}

Mat readWriteTIFF::getOp_im(){
	return this->op_im;
}

void readWriteTIFF::op_print(){
     for(int i=0; i < op_im.rows; ++i){
             for(int j=0; j < op_im.cols; ++j){
                     cout<<op_im.at<unsigned short int>(i,j)<<"\t";
             }
             cout<<endl;
     }
}

