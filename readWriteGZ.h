/*
 * @kangkang
 */
#ifndef _READ_WRITE_GZ_H_
#define _READ_WRITE_GZ_H_

#include <iostream>
#include <zlib.h>
#include <vector>
#include <string>

#ifndef _STR_
#define _STR_
typedef std::string str;
#endif

class readWriteGZ{
      
public:
       readWriteGZ(){
           buf = new char[BUF_SIZE];
       }
       ~readWriteGZ(){
           delete [] buf;
           content.clear();
       }

public:
       void setContent(const std::vector<str> &);
       std::vector<str> getContent();
       void print() const;

public:    
       bool openInGZ(const std::string &);
       bool readGZLine(std::string &);
       void closeInGZ();
       bool openOutGZ(const std::string &);
       void writeGZLine(const std::string &);
       void closeOutGZ();
       void writeGZ(const std::string &);
       std::vector<str> readGZ(const std::string &);

private:
       const static int BUF_SIZE = 1024 * 4;
       char* buf;
       std::vector<str> content;  
       gzFile gi,go;
};

#endif
