/*
 * @kangkang,¼ÆÊ±Æ÷ 
 */
#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>  
#include <time.h>
#include <string>


//////////////////////////////////////////////
#include <boost/date_time/posix_time/posix_time.hpp>  
#define BOOST_DATE_TIME_SOURCE
//////////////////////////////////////////////

class myTime{

public:

       myTime(){}
       ~myTime(){}      
public:
      void print(); 
      time_t start();
      time_t current();
      time_t end();
      double getTime();
      
//////////////////////////////      
public:
      void b_print();
/////////////////////////////
      
private:
      time_t st, et, cr;

};

#endif
