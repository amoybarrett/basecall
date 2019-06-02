/*
 * @kangkang,利用boost跨平台 
 */
#include "multithreading.h"

using namespace std;
using namespace boost;

void multithreading::run(){
     vector<pthread_t> temp;
     for(vector<void* (*)(void*)>::iterator it = threads.begin(); it != threads.end(); it++){
               pthread_t id;
               int i,ret;
               ret = pthread_create(&id , NULL, (*it), NULL);
               if(ret != 0){
                      cout<<"Create pthread error!"<<endl;
                      exit(1);
               }
               temp.push_back(id);
     }
     
     for(vector<pthread_t>::iterator it = temp.begin(); it != temp.end(); it++){
         pthread_join(*it, NULL);
     }
}

void multithreading::addThread(void* t(void*) ){
     threads.push_back(t);
}

void multithreading::setThreads(const vector<void* (*)(void*)> &threads){
     this->threads = threads;
}

vector<void* (*)(void*)> multithreading::getThreads(){
     return this->threads;
}

////////////////////////////////////////////////////////
void multithreading::b_run(){
     thread_group grp;
     for(vector<void* (*)()>::iterator it = b_threads.begin(); it != b_threads.end(); it++){
            grp.create_thread(*it);                          
     }
     grp.join_all();
}

void multithreading::b_addThread(void* t()){
     b_threads.push_back(t);
}

void multithreading::b_setThreads( vector<void* (*)()> &bt){
     this->b_threads = bt;
}

vector<void* (*)()> multithreading::b_getThreads(){
     return this->b_threads;                      
}

///////////////////////////////////////////////////////

/*
#include <windows.h>
#include <direct.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

boost::mutex mutexs[100];

void mul_run(int i){
		 mutexs[i].lock();
		 std::cout<<"begin thread "<<i<<std::endl;
		 Sleep(10000);
		 std::cout<<"end thread "<<i<<std::endl;
		 mutexs[i].unlock();
};

int main(int argc, char **args){
	std::cout<<"haha\n";
	int numberthreads = 4;
	std::vector< boost::thread * > threads(numberthreads, NULL);
	for(int i = 0; i < 20; i++){
		 if(threads[i % numberthreads] == NULL){
			 threads[i % numberthreads] = new boost::thread(&mul_run,i);
		 }else{
			threads[i % numberthreads]->join();
			delete threads[i % numberthreads];
			threads[i % numberthreads] = NULL;
			threads[i % numberthreads] = new boost::thread(&mul_run,i);
		 }
	}
	for(int i = 0; i < numberthreads; i++){
		if(threads[i] != NULL){
		    threads[i]->join();
		}
	}
	return 0;
}
*/

