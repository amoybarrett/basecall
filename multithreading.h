/*
 * @kangkang,∂‡œﬂ≥Ã
 */
#ifndef _MULTI_THREADING_H_
#define _MULTI_THREADING_H_

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <vector>

/////////////////////////////////
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
/////////////////////////////////

/*
 * image/intensity by tile or field
 * crosstalk , pp
 */
class multithreading{
public:
       multithreading(){
       }
       ~multithreading(){
           threads.clear();
           b_threads.clear();
       }  
public:
        void run();
        void addThread(void* (*)(void*) );
        void setThreads(const std::vector<void* (*)(void*)> &);
        std::vector<void* (*)(void*)> getThreads();
        
public:
       static void* thread1(void*){
              sleep(10);
              std::cout<<"1"<<std::endl;
       }
       static void* thread2(void*){
              sleep(1);
              std::cout<<"2"<<std::endl;
       }
       
private:
        std::vector<void* (*)(void*)> threads; 
        
public:
       void b_run();
       void b_addThread(void* (*)());
       void b_setThreads( std::vector<void* (*)()> &);
       std::vector<void* (*)()> b_getThreads();
       
private:
        std::vector<void* (*)()> b_threads;                  
};

#endif
