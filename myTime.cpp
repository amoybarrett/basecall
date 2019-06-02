/*
 * @kangkang,采用boost跨平台 
 */
#include "myTime.h"

using namespace std;

void myTime::print(){
      cout<<"Current Time:"<<this->current()<<endl;;
}

time_t myTime::start(){
      time(&st);
      return st;
}

time_t myTime::end(){
      time(&et);
      return et;
}

time_t myTime::current(){
      localtime(&cr);
      return cr;    
}

double myTime::getTime(){
       double cost=0;
       cost=difftime(et,st);
       cout<<"Cost:\t"<<cost<<"(s)"<<endl;
       return cost;
}

////////////////////////////////
void myTime::b_print(){
     string strTime = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());  
  
     int pos = strTime.find('T');  
     strTime.replace(pos,1,string("-"));  
     strTime.replace(pos + 3,0,string(":"));  
     strTime.replace(pos + 6,0,string(":"));  
  
     cout << "Current Time:"<< strTime.c_str() << endl;       
}
/////////////////////////////////
