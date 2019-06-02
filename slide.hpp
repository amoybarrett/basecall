/*
 * @kangkang,slide信息结构体 
 */

#ifndef _SLIDE_HPP_
#define _SLIDE_HPP_  

#include <string>

struct slide{
        std::string filename;
        unsigned short slide;
        unsigned short lane;
        unsigned short field;
        unsigned int tile;//block
        long id; 
        std::string inpath;  
        std::string outpath;           
};

#endif
