/*
 * @kangkang
 */
#include "readWriteTXT.h"

using namespace std;

void readWriteTXT::openTXT(const string& fileName, bool flag){
if(flag){
     is.open(fileName.c_str(), ofstream::in);
     if(is.fail()){
         cout<<"file not exist!"<<endl;
         exit(0);
     }
     if(!is.is_open()){
         cout<<"file can't open!"<<endl;
         exit(0);
     }
}else{
      os.open(fileName.c_str(), ofstream::out);
     if(os.fail()){
         cout<<"file can't create!"<<endl;
         exit(0);
     }
     if(!os.is_open()){
         cout<<"file can't open!"<<endl;
         exit(0);
     } 
}
} 
    
void readWriteTXT::closeTXT(bool flag){
if(flag){     
     is.close();
     is.clear();
}else{
      os.close();
      os.clear();      
}
}

bool readWriteTXT::readByLine(string& strline){
if(is >> strline){
              return true;
}
              return false;
}

void readWriteTXT::writeByLine(const string& strline){
     os << strline << endl;
}

vector<string> readWriteTXT::readTXT(const string& fileName){
     ifstream tis;
     tis.open(fileName.c_str(), ofstream::in);
     if(tis.fail()){
         cout<<"file not exist!"<<endl;
         return content;
     }
     if(!tis.is_open()){
         cout<<"file can't open!"<<endl;
         return content;
     }
     content.clear();
     char buffer[BUF_SIZE];
     while(!tis.eof()){
                       tis.getline(buffer, sizeof(buffer));
                       if(strlen(buffer) > 0){
                                         content.push_back(buffer);
                       }
     }
     tis.close();
     tis.clear(); 
     return content;     
}

void readWriteTXT::writeTXT(const string& fileName){
     ofstream tos;
     tos.open(fileName.c_str(), ofstream::out);
     if(tos.fail()){
         cout<<"file can't create!"<<endl;
         return ;
     }
     if(!tos.is_open()){
         cout<<"file can't open!"<<endl;
         return ;
     } 
     for(vector<string>::iterator it = content.begin(), end = content.end(); it != end; it++){
         tos << *it <<endl;
     }
     tos.close();
     tos.clear();
}


void readWriteTXT::setContent(const vector<string>& content){
     this->content = content;
}

vector<string> readWriteTXT::getContent(){
     return this->content;
}

void readWriteTXT::print() const{
     for(vector<string>::const_iterator it = content.begin(), end = content.end(); it != end; it++){
         cout << *it <<endl;
     }
}
