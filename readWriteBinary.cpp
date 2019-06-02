/*
 * @kangkang
 */
#include "readWriteBinary.h"

using namespace std;

void readWriteBinary::openBinary(const string& fileName, bool flag){
if(flag){
     is.open(fileName.c_str(), std::ios::binary);
     if(is.fail()){
         cout<<"file not exist!"<<endl;
         abort();
     }
     if(!is.is_open()){
         cout<<"file can't open!"<<endl;
         abort();
     }
}else{
     os.open(fileName.c_str(), std::ios::binary);
     if(os.fail()){
         cout<<"file can't create!"<<endl;
         abort();
     }
     if(!os.is_open()){
         cout<<"file can't open!"<<endl;
         abort();
     } 
}
} 
    
void readWriteBinary::closeBinary(bool flag){
if(flag){     
       is.close();
       is.clear();
}else{
       os.close();
       os.clear();      
}
}

vector<db> readWriteBinary::readByLine(){
     line.clear();  
     db temp;
     while(is.read((char*)&temp, sizeof(db))){   
         line.push_back(temp);
     }
     return line;
}

void readWriteBinary::writeByLine(vector<db> &iline){
     line = iline;
     for(vector<db>::iterator it = iline.begin(), end = iline.end(); it != end; it++){
         db temp = *it;
         os.write((char*)&(temp), sizeof(db));   
     }
}

void readWriteBinary::print(){
     for(vector<db>::iterator it = line.begin(), end = line.end(); it != end; it++){
         cout << *it <<endl;
     }     
}
void readWriteBinary::setLine(std::vector<db> &iline){
    line = iline;
}
vector<db> readWriteBinary::getLine(){
    return this->line;
}

