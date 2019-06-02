/*
 * @kangkang
 */
#include "readWriteCSV.h"
#include <cstdlib>

using namespace std;


void readWriteCSV::readCSV(const string &infile){
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
        vector<str> str_list;
        str_list.clear();
        if(o_str.length()==0){
             continue;       
        }
        int comma_n = 0;
	    do
	    {
		    str tmp_s = "";
		    comma_n = o_str.find( CHC );
	        if( -1 == comma_n )
		    {
			    tmp_s = o_str.substr( 0, o_str.length() );
                if(tmp_s.length()==0)
                    break;
			    str_list.push_back( tmp_s );
			    break;
		    }
		    tmp_s = o_str.substr( 0, comma_n );
		    o_str.erase( 0, comma_n+1 );
		    str_list.push_back( tmp_s );
      }while(true);
       content.push_back(str_list);
     }
     is.close();
}

void readWriteCSV::writeCSV(const string &outfile){
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
     for(vector< vector< str > >::iterator it = content.begin(); it != content.end(); ++it){
         vector< str > tv = *it;
         vector< str >::iterator itt;
         for(itt = tv.begin(); itt != tv.end(); ++itt){
             os << *itt << CHC;
         }
         os << "\n";
         
     }
     os.close();
}


vector< vector<str> > readWriteCSV::getContent(){
	return this->content;
}

void readWriteCSV::setContent(const vector< vector<str> > &content){
	this->content = content;
}

void readWriteCSV::print() const{
     for(vector< vector < str > >::const_iterator it = content.begin(); it != content.end(); ++it){
         vector< str > tv = *it;
         vector< str >::const_iterator itt;
         for(itt = tv.begin(); itt != tv.end()-1; ++itt){
             cout<<*itt<<CHC;
         }
         cout<<*itt;
         cout<<"\n";
     }
}
