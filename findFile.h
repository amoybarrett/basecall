/*
 * @kangkang,����filelist������boost���� 
 */
 

#ifndef _FIND_FILE_H_
#define _FIND_FILE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>


class findFile{
public:
       findFile(){}
       ~findFile(){}
public:
        void find(const std::string &, const std::string &);    
};

#endif
