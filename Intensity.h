/*
 * @kangkang,强度类，子强度类 
 */
#ifndef _INTENSITY_H_
#define _INTENSITY_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "readWriteCH.h"

#ifndef _CH_
#define _CH_
#define CH " "
#endif

#ifndef _DB_
#define _DB_

typedef double db;

#endif

namespace INTENSITY{
          
class Intensity{
public:
       Intensity(std::string filename,
        unsigned short slide,
        unsigned short lane,
        unsigned short field,
        unsigned int tile,
        long id = -1):filename(filename),slide(slide),lane(lane),field(field),tile(tile),id(id){}
	Intensity(const Intensity &iti){
                intensity = iti.intensity;
                noise = iti.noise;
    }
    Intensity(){
    }
    ~Intensity(){
                 intensity.clear();
    }
    
public:
	std::vector< std::vector<db> > getIntensity();
	void setIntensity(const std::vector< std::vector<db> > &);
	std::vector< std::vector<db> > getNoise();
	void setNoise(const std::vector< std::vector<db> > &);
	void print() const;

public:
	void readIntensity(const std::string &);
	void writeIntensity(const std::string &);
	void writeIntensity2(const std::string &);
	void readNoise(const std::string &);
	void writeNoise(const std::string &);
    long long getRow(){
            return intensity.size(); 
    }
    int getCol(){
        return intensity[0].size();    
    }
    std::vector<Intensity> crop(long); 

public:    
    std::vector<db> maxcol();
    std::vector<db> mincol();
    std::vector<db> avecol(); 
    std::vector<db> avebase();
    std::vector<db> aveatcg();
    std::vector<db> ratio();
    std::vector<db> colquantile(float);
    std::vector<db> colmedian();
    db** getArray();
    
    
public:
       
////////////////////////////////test////////////////////////////////////////////
       Intensity  operator-=(const db &js){
             for(std::vector< std::vector<db> >::iterator it = intensity.begin(); it != intensity.end(); ++it){
                         std::vector<db> temp = *it;
                         for(std::vector<db>::iterator itt = temp.begin() + prefix; itt != temp.end(); ++itt){
                             *itt -= js;
                         }    
             }  
             return *this;                  
       }
       Intensity  operator-=(const std::vector< std::vector<db> > &jj){
             for(long long i = 0; i < intensity.size(); i++){
                     for(int j = prefix; j< intensity[0].size(); j++){
                             intensity[i][j] -= jj[i][j];
                     }
             }
             return *this;                       
       }
       Intensity operator+=(const db &js){
             for(std::vector< std::vector<db> >::iterator it = intensity.begin() + prefix; it != intensity.end(); ++it){
                         std::vector<db> temp = *it;
                         for(std::vector<db>::iterator itt = temp.begin() + prefix; itt != temp.end(); ++itt){
                             *itt += js;
                         }    
             }  
             return *this;                  
       }
       Intensity  operator+=(const std::vector< std::vector<db> > &jj){
             for(long long i = 0; i < intensity.size(); i++){
                     for(int j = prefix; j< intensity[0].size(); j++){
                             intensity[i][j] += jj[i][j];
                     }
             }
             return *this;                       
       }
 
 
        Intensity  operator*=(const double &js){
             for(std::vector< std::vector<db> >::iterator it = intensity.begin(); it != intensity.end(); ++it){
                         std::vector<db> temp = *it;
                         for(std::vector<db>::iterator itt = temp.begin() + prefix; itt != temp.end(); ++itt){
                             *itt *= js;
                         }    
             }  
             return *this;                  
       }   
       Intensity  operator/=(const double &js){
             for(std::vector< std::vector<db> >::iterator it = intensity.begin(); it != intensity.end(); ++it){
                         std::vector<db> temp = *it;
                         for(std::vector<db>::iterator itt = temp.begin() + prefix; itt != temp.end(); ++itt){
                             *itt /= js;
                         }    
             }  
             return *this;                  
       }
////////////////////////////////test////////////////////////////////////////////
private: 
	std::vector< std::vector<db> > intensity;
	std::vector< std::vector<db> > noise;
	const static int BUF_SIZE = 1024 * 4;
	const static unsigned short int prefix = 4;
	const static unsigned short int bsize = 4;
	
private:
        std::string filename;
        unsigned short slide;
        unsigned short lane;
        unsigned short field;
        unsigned int tile;//block
        long id;
};

}

using namespace INTENSITY;
#endif
