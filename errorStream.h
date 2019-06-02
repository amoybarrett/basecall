/*
 * @kangkang,ËùÓĞ´íÎóÁ÷
 */
#ifndef _ERROR_STREAM_H_
#define _ERROR_STREAM_H_

#include <exception>
#include <iostream>

//struct errorStream : public virtual std::exception
class errorStream : public virtual std::exception
{
private:
        int err_no;
public:
       errorStream(const char* msg, int err){}
       int getErr_no(){
           return err_no;   
       }
};

#endif
