/*
 * @kangkang
 */
#include "readWriteCH.h"
#include <cstdlib>

using namespace std;


void readWriteCH::readCH(const string &infile){
     ifstream is;
     is.open(infile.c_str(), ofstream::in);
     if(is.fail()){
         cout<<"file not exist!"<<endl;
         return ;
     }
     if(!is.is_open()){
         cout<<"file can't open!"<<endl;
         return ;
     }
     char buffer[BUF_SIZE];
     content.clear();
     
     while(!is.eof()){
        is.getline(buffer, sizeof(buffer));
        string o_str(buffer);
        vector<db> str_list;
        str_list.clear();
        if(o_str.length()==0){
             continue;       
        }
        int comma_n = 0;
        int comma_n2 = 0;
	    do
	    {
		    string tmp_s = "";
		    comma_n = o_str.find( CH );	
            comma_n2 = o_str.find( CH2 );
            if(comma_n2 >= 0&& comma_n2 < comma_n || -1 == comma_n ){
                        comma_n = comma_n2;            
            }		    
	        if( -1 == comma_n )
		    {
			    tmp_s = o_str.substr( 0, o_str.length() );
                if(tmp_s.length()==0)
                    break;
			    stringstream tst;
			    tst<<tmp_s;
			    double td;
			    tst>>td;
			    str_list.push_back( td );
			    break;
		    }
		    tmp_s = o_str.substr( 0, comma_n );
		    o_str.erase( 0, comma_n+1 );
		    str_list.push_back( atof(tmp_s.c_str()) );
      }while(true);
      content.push_back(str_list);
     }
     is.close();
}

void readWriteCH::writeCH(const string &outfile){
     ofstream os;
     string temp=outfile;
     os.open(temp.c_str(), ofstream::out); 
     if(os.fail()){
         cout<<"file can't create!"<<endl;
         return ;
     }
     if(!os.is_open()){
         cout<<"file can't open!"<<endl;
         return ;
     }     
     for(vector< vector< db > >::iterator it = content.begin(); it != content.end(); ++it){
         vector< db > tv = *it;
         vector< db >::iterator itt;
         for(itt = tv.begin(); itt != tv.end(); ++itt){
             os << *itt << CH;
         }
         os << "\n";
         
     }
     os.close();
}

void readWriteCH::writeCH2(const string &outfile){
     ofstream os;
     string temp=outfile;
     os.open(temp.c_str(), ofstream::app); 
     if(os.fail()){
         cout<<"file can't create!"<<endl;
         return ;
     }
     if(!os.is_open()){
         cout<<"file can't open!"<<endl;
         return ;
     }     
     for(vector< vector< db > >::iterator it = content.begin(); it != content.end(); ++it){
         vector< db > tv = *it;
         vector< db >::iterator itt;
         for(itt = tv.begin(); itt != tv.end(); ++itt){
             os << *itt << CH;
         }
         os << "\n";
         
     }
     os.close();
}


vector< vector<db> > readWriteCH::getContent(){
	return this->content;
}

void readWriteCH::setContent(const vector< vector<db> > &content){
	this->content = content;
}

void readWriteCH::print() const{
     for(vector< vector < db > >::const_iterator it = content.begin(); it != content.end(); ++it){
         vector< db > tv = *it;
         vector< db >::const_iterator itt;
         for(itt = tv.begin(); itt != tv.end(); ++itt){
             cout<<*itt<<CH;
         }
         cout<<"\n";
     }
}
