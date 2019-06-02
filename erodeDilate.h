/*
 * @kangkang,Í¼Ïñ¸¯Ê´ 
 */
#ifndef _ERODING_DILATE_H_
#define _ERODING_DILATE_H_

#include "image.h"
#include <cmath>

class erodeDilate{
public:
	erodeDilate(){
	}
	~erodeDilate(){
	}
public:
    pre winMin(const std::vector< std::vector<pre> > &, long , long , long , long );
	void erode(image &);
///////////////////////////////////
	void op_erode(image &);
///////////////////////////////////

private:
	const static unsigned short winsize = 11;////////////////////////////////////
};

#endif
