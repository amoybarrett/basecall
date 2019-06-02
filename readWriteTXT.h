/*
 * @kangkang
 */
#ifndef __READ_WRITE_TXT_H_
#define __READ_WRITE_TXT_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>



class readWriteTXT{
public:
       readWriteTXT(){
                      buf = new char[BUF_SIZE];
       }
       virtual ~readWriteTXT(){
                      delete [] buf;
                      content.clear();
       }
       
public:
       void setContent(const std::vector<std::string>&);
       std::vector<std::string> getContent();
       void print() const;
 
public:      
       void openTXT(const std::string&, bool);     
       void closeTXT(bool);
       bool readByLine(std::string&);
       void writeByLine(const std::string&);
       std::vector<std::string> readTXT(const std::string&);
       void writeTXT(const std::string&);
       
       
public:
        template<typename T>
        inline std::string to_string(const T& x)
        {
               std::ostringstream oss;
               oss << x;
               return oss.str();
         }

       
private:
        const static int BUF_SIZE = 1024;
        char *buf;
        std::string line;
        std::vector<std::string> content;
        std::ifstream is;
        std::ofstream os;      
};

//#include "readWriteTXT.cpp"

#endif

