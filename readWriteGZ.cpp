/*
 * @kangkang
 */
#include "readWriteGZ.h"

#include <cstdlib>


using namespace std;



bool readWriteGZ::openInGZ(const string &ifile){
	gi = gzopen(ifile.c_str(), "rb");
	if(!gi){
		cerr<<"error:can't open file:"<<ifile<<endl;
		exit(0);
	}
	return true;
}

bool readWriteGZ::readGZLine(string &out){
	int have;
	out = "";
	have = gzread(gi, buf, BUF_SIZE);	
	if(have > 0){
		out.append(buf, have);
		return true;
	}else{
		return false;
	}
}

void readWriteGZ::closeInGZ(){
	gzclose(gi);
}

bool readWriteGZ::openOutGZ(const string &ofile){
	go = gzopen(ofile.c_str(), "wb");
	if(!go){
		cerr<<"error:can't open file:"<<ofile<<endl;
		exit(0);
	}
	return true;
}

void readWriteGZ::writeGZLine(const string &in){
	gzwrite(go, in.c_str(), in.length());
}

void readWriteGZ::closeOutGZ(){
	gzclose(go);
}

vector<str> readWriteGZ::readGZ(const string &ifile){
     str temp;
     str tail="";
     content.clear();
     if(openInGZ(ifile)){
         while(readGZLine(temp)){
             temp = tail + temp;
             int i=-1;
             int j=0;
             while((i = temp.find_first_of('\n',j)) != string::npos){
                  str ct =  temp.substr(j,i+1-j);//×¢Òâlength=i+1-j 
                  if(ct.length()!=0){
                      content.push_back(ct);  
                  }
                  j=i+1;
             }
             tail = temp.erase(0,j);//·µ»ØÉ¾³ýºóµÄ×Ö·û´® 
         }
         closeInGZ();
     }
     return content;
}

void readWriteGZ::writeGZ(const string &ofile){
     if(openOutGZ(ofile)){
         vector< str >::iterator itt;
         for(itt = content.begin(); itt != content.end(); ++itt){
             str temp=*itt + "\n";
             writeGZLine(temp);
         }  
         closeOutGZ();                             
     }
}

void readWriteGZ::print() const{
         vector< str >::const_iterator itt;
         for(itt = content.begin(); itt != content.end(); ++itt){
             cout<<*itt;
         }     
}

void readWriteGZ::setContent(const vector<str> &content){
     this->content = content;
}

vector<str> readWriteGZ::getContent(){
     return this->content; 
}
