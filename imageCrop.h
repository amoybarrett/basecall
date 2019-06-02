/*
 * @kangkang,Í¼Ïñ²Ã¼ô 
 */

#ifndef _IMAGE_CROP_H_
#define _IMAGE_CROP_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

#include "image.h"
#include "tiffio.h"

#ifndef _PRE_
#define _PRE_
typedef unsigned short int pre;
#endif

class imageCrop{
public:
       imageCrop(int wd, int hg){cwidth = wd; cheight = hg;}
       imageCrop(int eg){edge = eg;}
       ~imageCrop(){}      

public:      
      void crop(const std::string &, const std::string &);          
      void save(const std::string &, std::vector< std::vector<pre> > &) const;  

public:
      std::vector< std::vector<image> > subimage(std::vector<image> &);
      std::vector< std::vector<image> > subimage2(std::vector<image> &, std::vector< std::vector< std::vector< std::pair<int, int> > > > &);
      
private:
      unsigned int cwidth;
      unsigned int cheight;
      unsigned int edge;
};

#endif
