/*
 * @kangkang,bayes∑÷¿‡∆˜
 */
#ifndef _BAYESCALL_H_
#define _BAYESCALL_H_

#include <map>
#include <vector>
#include <utility>
#include <iostream>

class bayescall{
public:
       bayescall(){}
       ~bayescall(){}  
       
public:
       void sample(); 
       void train(std::vector< std::vector<double> > &, std::vector< std::vector<double> >&, std::vector< std::vector<short> > &);     
       short getBase(std::vector< std::vector<double> > &, long long , int );
       double getProbability(std::vector< std::vector<double> > &, std::vector< std::vector<double> >&, std::vector< std::vector<short> > &, long long, int);
       
private:
        const static unsigned short int prefix = 4;//////
        const static unsigned short int bsize = 4;////
        std::vector< std::map< std::pair< std::pair<double, double>, short>, double> > tt;
        std::vector<short> tbp;
        const static unsigned short int group = 10;/////////////////////////
        double prob[bsize];
        double maxa, maxc, maxt, maxg;
        double mina, minc, mint, ming;
        double maxna, maxnc, maxnt, maxng;
        double minna, minnc, minnt, minng;
};

//#include "bayescall.cpp"

#endif

