/*
 * @kangkang,subtile(block)(median)
 */
#include "crosstalk.h"

using namespace std;

double crosstalk::getArray(double* m, vector<double> v){
                      for(long long b = 0; b < v.size(); b++){
                               m[b] = v[b];         
                      }       
}

void crosstalk::linearFit(Intensity &its){

standard sd;
sd.positive(its);

vector< vector<db> > it = its.getIntensity();

vector<double> itdown = its.colquantile(0.5);

for(int j = prefix; j < it[0].size(); j += bsize){  

for(register short i = 0; i < bsize; i++){
             for(register short l = 0; l < bsize; l++){
                          matrix[i][l] = 1;
             }
}

    for(int k1 = j; k1 < j + bsize; ++k1){ 
        for(int k2 = k1 + 1; k2 < j + bsize; ++k2){  
                if(k1 != k2){
                      int len = ceil(RG * 1.0 / step);
                      long long counter[len];
                      for(int i = 0; i < len; i ++){
                              counter[i] = 0;
                      }
                      for(long long i = 0; i < it.size(); ++i){
                            bool flag = true;
                            for(float l = step; l < RG; l += step){
                                if(it[i][k1] > itdown[k1 - prefix] || it[i][k2] > itdown[k2 - prefix]){
                                         if ((it[i][k2]) / ((it[i][k1]) + 1e-10) < tan(l / 180.0 * PI)){
                                             int index = ceil((l - step) * 1.0/step);
                                             counter[index] += 1;
                                             flag = false;
                                             break;
                                         }
                                }
                            }
                             if(flag){                                   
                                     counter[len - 1]++;       
                            }                                                                    
                      } 
                      
                      
                      double tt = 0;
                      for(register int l = 0; l < len; l ++){
                                   tt += counter[l];
                      } 
                      
                      long long tl = tt / 2;
                      double xl = -1;
                      long long ts = 0;                     
 

  
                      for(int i = 0; i < len; ++i){
                          ts += counter[i];  
                          if(ts >= tl){
                                 xl =  tan(((i + 1) * step - step / 2.0) / 180.0 * PI);
                                 break;
                          }
                      }  
                      vector<db> v1, v2, v3, v4;
                      for(long long i = 0; i < it.size(); ++i){
                                         if((it[i][k2]) / ((it[i][k1]) + 1e-10) < xl){
                                               v1.push_back(it[i][k1]);
                                               v2.push_back(it[i][k2]);         
                                         }else{
                                                v3.push_back(it[i][k1]);
                                                v4.push_back(it[i][k2]);                                               
                                         }                                           
                      }  
                      LeastSquare ls1(v1,v2);
                      LeastSquare ls2(v4,v3);                                         
                      matrix[k2 - j][k1 - j] = ls1.getCoefficient();
                      matrix[k1 - j][k2 - j] = ls2.getCoefficient();                 
                }     
        }
    }
    
    //print();
    matrix = inversion::inv(matrix, bsize);
    this->correct(it, j);
}
	its.setIntensity(it);
	return ;    
}

void crosstalk::polar(Intensity &its){
standard sd;
sd.positive(its);

vector< vector<db> > it = its.getIntensity();

vector<double> itup = its.colquantile(0.99); 
vector<double> itdown = its.colquantile(0.5);

for(int j = prefix; j < it[0].size(); j += bsize){  
for(register short i = 0; i < bsize; i++){
             for(register short l = 0; l < bsize; l++){
                          matrix[i][l] = 1;
             }
}
    for(int k1 = j; k1 < j + bsize; ++k1){ 
        for(int k2 = k1 + 1; k2 < j + bsize; ++k2){  
                if(k1 != k2){
                      int len = ceil(RG * 1.0 / step);
                      long long counter[len];
                      double sum[len];
                      for(int i = 0; i < len; i ++){
                              counter[i] = 0;
                              sum[i] = 0;
                      }
                      for(long long i = 0; i < it.size(); ++i){ 
                            if(it[i][k1] > itdown[k1 - prefix] || it[i][k2] > itdown[k2 - prefix]){                           
                                         int index = round(atan(it[i][k2] / (it[i][k1] + 1e-10)) / (PI / 2.0) * RG / step);
                                         counter[index] ++;
                                         double s1 = it[i][k1] / itup[k1 - prefix];
                                         double s2 = it[i][k2] / itup[k2 - prefix];
                                         sum[index] += sqrt(s1 * s1 + s2 * s2); 
                            }                                        
                      }   
                      
                      double tt = 0;
                      for(register int l = 0; l < len; l ++){
                                   //cout<<l<<":"<<counter[l]<<"+"<<sum[l]<<"\t";
                                   tt += counter[l];
                      }
                      //cout<<endl;
                      
                      double ml1 = -1;
                      double ml2 = -1;
                      long long ts = 0;
                      long long tl = tt / 2;
                      double xl1 = -1, xl2 = -1;
                      int i1 = -1;
                      int i2 = -1;
                      for(int i = 0; i < len; ++i){
                              ts += counter[i];
                              if(ts < tl){
                                    if(sum[i] > ml1){
                                        ml1 = sum[i];
                                        i1 = i;
                                        xl1 = tan(((i + 1) * step - step / 2.0) / 180.0 * PI);
                                    }
                              }else{
                                    if(sum[i] > ml2){
                                        ml2 = sum[i];
                                        i2 = i;
                                        xl2 = 1 / tan(((i + 1) * step - step / 2.0) / 180.0 * PI);
                                    }
                              }     
                      } 
                      //cout<<"max:"<<i1<<":"<<counter[i1]<<"\t"<<i2<<":"<<counter[i2]<<endl;
                      if(i1 == 0) xl1 = 0;
                      if(i2 == len - 1) xl2 = 0;
                      matrix[k2 - j][k1 - j] = xl1;
                      matrix[k1 - j][k2 - j] = xl2;               
                }     
        }
    }
    //this->print();
    matrix = inversion::inv(matrix, bsize);
    this->correct(it, j);
}
	its.setIntensity(it);
	return ;   
}



void crosstalk::correct(vector< vector<double> > &its, int &n){
    for(long long i = 0; i < its.size(); ++i){
		double temp[bsize];
		for(register short int j = 0; j < bsize; j++){
			temp[j] = 0;
		}
		for(register short k1 = 0; k1  < bsize; k1++){
			for(register short k2 = 0; k2 < bsize; k2++){
				temp[k1] += matrix[k1][k2] * its[i][n + k2];
			}
			
		}
		for(register short int j = 0; j < bsize; j++){
			its[i][n+j] = temp[j];
		}
    }
}


void crosstalk::print(){
     for(int i = 0; i < bsize; ++i){
             for(int j = 0; j < bsize; ++j){
                     cout<<matrix[i][j]<<"\t";
             }
             cout<<endl;
     }
}

double** crosstalk::getMatrix(){
	return this->matrix;
}

void crosstalk::setMatrix(double **t){
    for(int i = 0; i < bsize; ++i){
	 		delete []  matrix[i];
    } 
	delete [] matrix;
    matrix = t;
}


