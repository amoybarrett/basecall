#ifndef _GLOBAL_HPP_
#define _GLOBAL_HPP_

#include <vector>
#include <algorithm>
#include <utility>

namespace GT{
struct data{
    double distance;
    std::pair<float, float> p1;
    std::pair<float, float> p2;        
};
inline bool sortBD(const data &d1, const data &d2){
     return d1.distance < d2.distance;    
}
inline void pushBK(std::vector<data> &vecd, const double distance, const std::pair<float, float> &p1, std::pair<float, float> &p2){
     data d;
     d.distance = distance;
     d.p1 = p1;
     d.p2 = p2;
     vecd.push_back(d); 
}
}

#endif
