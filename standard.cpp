/*
 * @kangkang
 */
#include "standard.h"

using namespace std;

void standard::positive(Intensity &its){
     vector< vector<db> > v = its.getIntensity();
     for(long long i = 0; i < v.size(); ++i){
             for(int j = prefix; j < v[i].size(); j++){
                     if(v[i][j] < 0){
                                  v[i][j] = 0;
                     }
             }
     }
     its.setIntensity(v);
}
