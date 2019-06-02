/*
 * @kangkang,subtile(block)
 */
#include "phasingPrephasing.h"

using namespace std;

//random walk matrix,Plamen Markov
void phasingPrephasing::correct(Intensity &its, vector<double> &ppt){
     vector<double> v1;
     vector<double> v2 = phasing(its);
     for(int i = 0; i < v2.size(); i++){
             v1.push_back(i + 2);        
     } 
     LeastSquare ls1(v1,v2);
     double A = ls1.getCoefficient();
     v1.clear();
     v2.clear();
     v2 = prephasing(its);
     for(int i = 0; i < v2.size(); i++){
             v1.push_back(i + 1);        
     }
     LeastSquare ls2(v1,v2);
     double B = ls2.getCoefficient();
     cout<<"Phasing:"<<A<<endl;/////////////////phasing
     cout<<"Prephasing:"<<B<<endl;/////////////////prephasing
     
     ppt.push_back(A);
     ppt.push_back(B);
     
     double C = 1 - A - B;
     matrix = new double*[v1.size() + 1];
     for(int i = 0; i < v1.size() + 1; ++i){
	 matrix[i] = new double[v1.size() + 1];
     } 
     
     
     
for(int i = 0; i < v1.size() + 1; i++){
    for(register short j = 0; j < v1.size() + 1; j++){
	matrix[i][j] = 0;
    }
}

    matrix[0][0] = C;
    matrix[0][1] = B;

for(int i = 1; i < v1.size() + 1; i++){
    for(register short j = 0; j < v1.size() + 1; j++){
	if(j - 1 < 0){
		matrix[i][j] = matrix[i-1][j] * A;
	}else if(j - 2 < 0){
		matrix[i][j] = matrix[i-1][j-1] * C + matrix[i-1][j] * A;
	}else{
		matrix[i][j] = matrix[i-1][j -2]  * B + matrix[i-1][j-1] * C + matrix[i-1][j] * A;
	}
    }
}

/*
for(register short i = 0; i < v1.size() + 1; i++){
    for(register short j = 0; j < v1.size() + 1; j++){
                 cout<<matrix[i][j]<<"\t";
    }
    cout<<endl;
}
*/
	
    inversion iv;
    matrix = iv.inv(matrix, v1.size() + 1);

vector< vector<db> > v = its.getIntensity();
    
    for(long long j = 0; j < v.size(); ++j){
		long double temp[v[j].size() - prefix];
		for(register short int jt = 0; jt < v[j].size() - prefix; jt++){
			temp[jt] = 0;
		}
		
        for(int i = prefix; i < v[j].size(); i++){
            int l = ((i - prefix) / bsize);
		    int m = ((i - prefix) % bsize);
		    for(int k1 = 0; k1 < (v[j].size() - prefix) * 1.0 / bsize; k1++){
			        temp[i-prefix] += matrix[l][k1] * v[j][(int)(k1 * bsize + m) + prefix];		
		    }
	    }
	    
	    for(register int i = 0; i < v[j].size() - prefix; i++){
		             v[j][i + prefix] = temp[i];
	    }	
    }
    
    its.setIntensity(v);

    for(int i = 0; i < v1.size() + 1; ++i){
	      delete []  matrix[i];
    } 
    delete [] matrix; 
}

vector<double> phasingPrephasing::phasing(Intensity &its){
               vector< vector<db> > v = its.getIntensity(); 
               vector<double> p;
               for(int i = 2; i <= (v[0].size() - prefix) * 1.0 / bsize; i++){
                     double *b1 = oneNotMax(v, i ,true);
                     double *b2 = twoNotMax(v, i, true);
                     double temp = 0;
                     for(register int k = 0; k < bsize; k ++){
                                  temp += (b1[k] - b2[k]);
                                  
                     }                     
                     delete [] b1;
                     delete [] b2;
                     p.push_back(temp/bsize); 
               } 
               return p;
}

vector<double> phasingPrephasing::prephasing(Intensity &its){
               vector< vector<db> > v = its.getIntensity(); 
               vector<double> p;
               for(int i = 1; i <= (v[0].size() - prefix) * 1.0 / bsize - 1; i++){
                     double *b1 = oneNotMax(v, i ,false);
                     double *b2 = twoNotMax(v, i, false);
                     double temp = 0;
                     for(register int k = 0; k < bsize; k ++){
                                  temp += (b1[k] - b2[k]);
                     }
                     delete [] b1;
                     delete [] b2;
                     p.push_back(temp/bsize);  
               } 
               return p;
}

double* phasingPrephasing::oneNotMax(vector< vector<db> > &v, int c, bool flag){
        double *B = new double[bsize];
        for(register short i = 0; i < bsize; i++){
                     B[i] = 0;             
        }
        double b[bsize] = {0, 0, 0, 0};
        if(flag){
             for(long long i = 0; i < v.size(); i++){
                    short base = max(v, i, c - 1);
                    short _base = max(v, i, c);
                    if(_base != base){
                                B[base] += v[i][round((c - 1) * bsize + prefix) + base];
                                b[base] ++;
                    }         
             }    
        }else{
             for(long long i = 0; i < v.size(); i++){
                    short base = max(v, i, c + 1);
                    short _base = max(v, i, c);
                    if(_base != base){
                                B[base] += v[i][round((c - 1) * bsize + prefix) + base];
                                b[base] ++;
                    }         
             }    
        }
        for(register short i = 0; i < bsize; i++){
                     B[i] /= (b[i] + 1e-10);             
        }
        return B;
}

double* phasingPrephasing::twoNotMax(vector< vector<db> > &v, int c, bool flag){
        double *B = new double[bsize];
        for(register short i = 0; i < bsize; i++){
                     B[i] = 0;             
        }
        double b[bsize] = {0, 0, 0, 0};
        if(flag){
             for(long long i = 0; i < v.size(); i++){
                    short base = max(v, i, c - 1);
                    short _base = max(v, i, c);
                    for(register short j = 0; j < bsize; j ++){
                            if(j != base && j!= _base){
                                B[j] += v[i][round((c - 1) * bsize + prefix) + j];
                                b[j] ++;
                            }   
                    }      
             }    
        }else{
             for(long long i = 0; i < v.size(); i++){
                    short base = max(v, i, c + 1);
                    short _base = max(v, i, c);
                    for(register short j = 0; j < bsize; j ++){
                            if(j != base && j!= _base){
                                B[j] += v[i][round((c - 1) * bsize + prefix) + j];
                                b[j] ++;
                            }   
                    }       
             }    
        }
        for(register short i = 0; i < bsize; i++){
                     B[i] /= b[i] + 1e-10;             
        }
        return B;       
}

int phasingPrephasing::max(vector< vector<db> > &its, long long m, int n){
    db temp = -1e10;
    bool flag = true;
    int out = -1;
    for(register int i = round((n - 1) * bsize + prefix); i < round(n * bsize + prefix); i++){
            if(its[m][i] > temp || flag){				
                         temp = its[m][i];
                         out = i - round((n - 1) * bsize + prefix);
			 flag = false;
            }     
    } 
    return out;   
}


