/*
 * @kangkang
 */
#include "normalization.h"

using namespace std;

void normalization::normalize(Intensity &its){
     
    standard sd;
    sd.positive(its);    
    
	vector< vector<db> > v = its.getIntensity();
	int len = ceil((v[0].size() - prefix) * 1.0/ bsize);
 
//1 和 2 顺序可调整 

//##########################################################
vector<double> colMax = its.colquantile(qlevel);

for(long long i = 0; i < v.size(); i++){
	for(int j = prefix; j < v[i].size(); ++j){
        if(v[i][j] >= colMax[j-prefix]){
              v[i][j] = 1;
        }else{
		      v[i][j] = v[i][j] / (colMax[j-prefix] + 1e-10);
        }
	}
}
//##########################################################

its.setIntensity(v);

//#############################################################	
    vector<double> ave = its.avebase();
    for(int j = prefix; j < v[0].size(); ++j){
        double rt = ave[(int)((j - prefix) * 1.0 / bsize)] / (ave[0] + 1e-10);                   
        for(long long i = 0; i < v.size(); i ++){
            if(i == 0){
                cout<<"Normalization:\n"<<rt<<endl;
            }
			     v[i][j] = v[i][j] * rt;
		}
	}
	
//##########################################################	



//##########################################################
for(long long i = 0; i < v.size(); i++){
	for(int j = prefix; j < v[i].size(); j += bsize){
		db baseMax = -1e10;
		for(int k = 0; k < bsize; k++){
			if(v[i][j + k] > baseMax)
				baseMax = v[i][j + k];
		}
		for(int k = 0; k < bsize; k++){
			v[i][j + k] = v[i][j + k] / (baseMax + 1e-10);
		}
	}
}
//##########################################################

its.setIntensity(v);
}
