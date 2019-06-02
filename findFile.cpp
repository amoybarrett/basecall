/*
 * @kangkang,生成filelist，采用boost遍历 
 */

#include "findFile.h"

using namespace std;
namespace fs = boost::filesystem;

void findFile::find(const string &path, const string &ifile){
     string s1 = "C0";
     string s2 = "R0";
     
     string t = "rm " + ifile;
     system(t.c_str());
     
     int id_i = 30;
     int id_j = 30;
     
     for(int i = 1; i <= id_i; i++){
             for(int j = 1; j <= id_j; j++){
                  string s3 = s1;
                  if(i < 10)
                       s3 += "0";
                  stringstream ss1;               
                  ss1<<i;
                  s3 = s3 + ss1.str();
                                   
                  s3 = s3 + s2;
                  if(j < 10)
                       s3 += "0";
                  stringstream ss2; 
                  ss2<<j;
                  s3 = s3 + ss2.str();
                  
                  s3 = "find " + path + " -name \\*" + s3 + "\\*tif -print | sort >>" + ifile;
                  
                  system(s3.c_str());  
             }        
     }
                  
} 


bool getDirFiles( std::string sDirName,std::vector<std::string> &vFiles)
{
fs::path fullpath (sDirName);

if(!fs::exists(fullpath)){return false;}
fs::recursive_directory_iterator end_iter;
for(fs::recursive_directory_iterator iter(fullpath);iter!=end_iter;iter++){
try{
if (fs::is_directory( *iter ) ){
//std::cout<<*iter << "is dir" << std::endl;
//ret.push_back(iter->path().string());
}
else
{
//ret.push_back(iter->path().string());
//std::cout << *iter << " is a file" << std::endl;
std::string sFileName = iter->path().string();
vFiles.push_back(sFileName);
}
} catch ( const std::exception & ex ){
std::cerr << ex.what() << std::endl;
continue;
}
}
return true;
}

/*
int main(int argc, char **argv){
    vector<string> file;
    if(!getDirFiles(argv[1], file))
           cout<<"error"<<endl;
    
    for(int i = 0; i < file.size(); i++)
            cout<<file[i]<<endl;   
    return 0;   
}
*/
