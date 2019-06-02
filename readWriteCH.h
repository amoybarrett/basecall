/*
 * @kangkang
 */
#ifndef _READ_WRITE_CH_H_
#define _READ_WRITE_CH_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//////////////////////////////////////////
#ifndef _CH_
#define _CH_
#define CH " " 
#endif

#ifndef _CH2_
#define _CH2_
#define CH2 "\t" 
#endif
//////////////////////////////////////////

#ifndef _DB_
#define _DB_

typedef double db;

#endif

//templat<class csv_type>
class readWriteCH{
public:
	readWriteCH(){
    }
    ~readWriteCH(){
    }
    
public:
	std::vector< std::vector<db> > getContent();
	void setContent(const std::vector< std::vector<db> > &);
	void print() const;
	
public:
	void readCH(const std::string &);
	void writeCH(const std::string &);
	void writeCH2(const std::string &);
	//////////////////
    void readByLine();
    void writeByLine();
    //////////////////

private: 
	std::vector< std::vector<db> > content;
	const static int BUF_SIZE = 1024 * 1024;
};

#endif
