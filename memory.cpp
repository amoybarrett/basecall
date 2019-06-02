/*
 * @kangkang，获得当前进程内存信息和进程号 
 */
#include "memory.h"

//////////////////////////linux
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <sys/sysinfo.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
//////////////////////////

/*
///////////////////////////window
#include <iostream>
#include <windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
using namespace std;
void showMemoryInfo(void){
    HANDLE handle=GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
    cout<<"内存使用:"<<pmc.WorkingSetSize/1000 <<"K/"<<pmc.PeakWorkingSetSize/1000<<"K + "<<pmc.PagefileUsage/1000 <<"K/"<<pmc.PeakPagefileUsage/1000 <<"K"<<endl;
}
///////////////////////////
*/

#include <boost/thread.hpp>

using namespace std;

void memory::memStat(){
      
       cout<<"Boost ID:"<<boost::this_thread::get_id()<<endl;
       cout<<"========================================System====================================="<<endl;
       struct sysinfo info;
       int error;
       error = sysinfo(&info);
       
       cout<<"System run time:"<<info.uptime<<"\n"<<"1 minute load average:"<<info.loads[0]<<"\n"<<"Total memory:"<<info.totalram<<"\n"<<"Unused memory:"<<info.freeram<<"\n"
       <<"Total swap:"<<info.totalswap<<"\n"<<"Free swap:"<<info.freeswap<<"\n"<<"Process number:"<<info.procs<<endl;
       cout<<"========================================System====================================="<<endl;
       cout<<"======================================PID("<<getpid()<<")==================================="<<endl;
       struct rusage usage;
       error = getrusage(RUSAGE_SELF, &usage);
       long sec = usage.ru_utime.tv_sec + usage.ru_stime.tv_sec;
       long usec = usage.ru_utime.tv_usec + usage.ru_stime.tv_usec;
       sec += usec/1000000;
       usec %= 1000000;
       
       cout<<"User time used:"<<sec<<"\n"<<"System time used:"<<usec<<"\n"<<"Maximum resident set size:"
       <<usage.ru_maxrss<<"\n"<<"Integral shared memory size:"<<usage.ru_ixrss<<"\n"<<"integral unshared data size:"<<usage.ru_idrss<<"\n"
       <<"Integral unshared stack size:"<<usage.ru_isrss<<"\n"<<"Page reclaims:"<<usage.ru_minflt<<"\n"<<"Page faults:"<<usage.ru_majflt<<"\n"<<
       "Swaps:"<<usage.ru_nswap<<endl;
       cout<<"======================================PID("<<getpid()<<")==================================="<<endl;
}

/*
int main(int argc, char **argv){
    memory mm;
    mm.memStat();    
}
*/


