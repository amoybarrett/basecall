/*
 * @kangkang,ǿ�����ݹ�һ�� 
 */
#ifndef _NORMALIZATION_H_
#define _NORMALIZATION_H_

#include <cmath>
#include "Intensity.h"
#include "standard.h"

class normalization{
public:
	normalization(){
                    qlevel = 0.99;//////////////////////////////////////////
	}
	~normalization(){
	}
public:
	void normalize(Intensity &);

private:
	const static unsigned short int prefix = 4;
	const static unsigned short int bsize = 4;
	float qlevel;
};

#endif
