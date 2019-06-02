/*
 * @kangkang
 */
#ifndef __READ_WRITE_BINARY_H_
#define __READ_WRITE_BINARY_H_


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>

#ifndef _DB_
#define _DB_

typedef double db;

#endif

class readWriteBinary{
public:
       readWriteBinary(){
       }
       ~readWriteBinary(){
       }
 
public:      
       void openBinary(const std::string&, bool);     
       void closeBinary(bool);
       std::vector<db> readByLine();
       void writeByLine(std::vector<db>&);

public: 
       void print();
       void setLine(std::vector<db> &);
       std::vector<db> getLine();
       
private:
        const static int BUF_SIZE = 1024;///////////////////////////////////////
        std::vector<db> line;
        std::ifstream is;
        std::ofstream os;      
};


#endif

