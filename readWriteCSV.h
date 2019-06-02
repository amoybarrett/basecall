/*
 * @kangkang
 */
#ifndef _READ_WRITE_CSV_H_
#define _READ_WRITE_CSV_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifndef _CHC_
#define _CHC_
#define CHC ","
#endif


#ifndef _STR_
#define _STR_
typedef std::string str;
#endif

//templat<class csv_type>
class readWriteCSV{
public:
	readWriteCSV(){
    }
    ~readWriteCSV(){
    }
    
public:
	std::vector< std::vector<str> > getContent();
	void setContent(const std::vector< std::vector<str> > &);
	void print() const;
	
public:
	void readCSV(const std::string &);
	void writeCSV(const std::string &);
	////////////////////////
    void readByLine();
    void writeByLine();
    ////////////////////////

private: 
	std::vector< std::vector<str> > content;
	const static int BUF_SIZE = 1024 * 4;
};

#endif
