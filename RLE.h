/*
 * @kangkang,”Œ≥Ã±‡¬Î 
 */
#ifndef _RLE_H_
#define _RLE_H_

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#ifndef _LL_
#define _LL_
typedef long long ll;
#endif

#ifndef _PRE_
#define _PRE_
typedef unsigned short pre;
#endif

class RLE{

public:
       RLE(){
       }
       ~RLE(){
              resultPosition.clear();
       }

public:
       void getRLE(std::vector< std::pair<ll,ll> > &);
       void setRLE(std::vector< std::pair<ll,ll> > &);
       void print();

public:
       void launch(std::vector< std::vector<ll> > &, const std::vector< std::vector<pre> > &);
       int recursion(ll, ll, std::vector< std::vector<ll> > &, std::vector< std::pair<ll,ll> > &, const std::vector< std::vector<pre> > &, double &, long &);
       bool isAllMax(std::vector< std::pair<ll,ll> > &, const std::vector< std::vector<pre> > &, std::vector< std::vector<ll> > &);
       
private:

        std::vector< std::pair<ll,ll> > resultPosition;

      
};

#endif
