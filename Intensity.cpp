/*
 * @kangkang
 */
#include "Intensity.h"
#include <cstdlib>

using namespace std;

vector<Intensity> Intensity::crop(long step){//或者按block或tile分 
         vector<Intensity> out;
         long long i;
         if(step < intensity.size()){
                 for(i = 0; i + step < intensity.size(); i += step){
                       Intensity ti;
                       vector< vector<db> > temp1;
                       vector< vector<db> > temp2;
                       for(long long j = i; j < i + step; j++){
                           temp1.push_back(intensity[j]);
                           temp2.push_back(noise[j]);         
                       }
                       ti.setIntensity(temp1);
                       ti.setNoise(temp2);
                       out.push_back(ti);
                 }
                 if(i < intensity.size() - 1){
                      Intensity ti;
                      vector< vector<db> > temp1;
                      vector< vector<db> > temp2;
                      for(long long j = i; j < intensity.size(); j++){
                           temp1.push_back(intensity[j]);
                           temp2.push_back(noise[j]);                        
                      }    
                      ti.setIntensity(temp1);
                      ti.setNoise(temp2);
                      out.push_back(ti);
                 }
         }else{
               out.push_back(*this);     
         }
         return out;
}

void Intensity::readIntensity(const string &infile){
     readWriteCH rwc;
     rwc.readCH(infile);
     this->intensity = rwc.getContent();
}

void Intensity::writeIntensity(const string &outfile){
     readWriteCH rwc;
     rwc.setContent(intensity);
     rwc.writeCH(outfile);
}

void Intensity::writeIntensity2(const string &outfile){
     readWriteCH rwc;
     rwc.setContent(intensity);
     rwc.writeCH2(outfile);
}

void Intensity::readNoise(const string &infile){
     readWriteCH rwc;
     rwc.readCH(infile);
     this->noise = rwc.getContent();
}

void Intensity::writeNoise(const string &outfile){
     readWriteCH rwc;
     rwc.setContent(noise);
     rwc.writeCH(outfile);
}

vector< vector<db> > Intensity::getIntensity(){
	return this->intensity;
}

void Intensity::setIntensity(const vector< vector<db> > &intensity){
	this->intensity = intensity;
}

vector< vector<db> > Intensity::getNoise(){
	return this->noise;
}

void Intensity::setNoise(const vector< vector<db> > &noise){
	this->noise = noise;
}

void Intensity::print() const{
     for(vector< vector < db > >::const_iterator it = intensity.begin(); it != intensity.end(); ++it){
         vector< db > tv = *it;
         for(vector< db >::const_iterator itt = tv.begin(); itt != tv.end(); ++itt){
             cout<<*itt<<CH;
         }
         cout<<"\n";
     }
}

////////////////////////////////test////////////////////////////////////////////
db** Intensity::getArray(){
    db **out;
    out = new db*[intensity.size()];    
    for (long long i = 0; i < intensity.size(); ++i)
    {
         out[i] = new db[intensity[0].size()];
    }

      for(long long i = 0; i < intensity.size(); i++){
               for(int j = 0; j < intensity[0].size(); j++){
                        out[i][j] = intensity[i][j];
               }
      }
      return out;
}
std::vector<db> Intensity::ratio(){
       vector<db> out;
       vector<db> temp = this->avebase();
       for(int i = 1; i < temp.size(); i ++){
               db t = temp[i] / (temp[i - 1] + 1e-10);
               out.push_back(t);
       }
       return out;
}
////////////////////////////////test////////////////////////////////////////////
vector<db> Intensity::colmedian(){
         return this->colquantile(0.5);   
}

vector<db> Intensity::maxcol(){
       vector<db> v((intensity[0].size() - prefix), -1e-10);
       for(long long i = 0; i < intensity.size(); i ++){
           for(int j = prefix; j < intensity[i].size(); j ++){
                   if(intensity[i][j] > v[j - prefix]){
                                v[j - prefix] =  intensity[i][j];     
                   }        
           }     
       }  
       return v;      
}

vector<db> Intensity::mincol(){
       vector<db> v((intensity[0].size() - prefix), 1e10);
       for(long long i = 0; i < intensity.size(); i ++){
           for(int j = prefix; j < intensity[i].size(); j ++){
                   if(intensity[i][j] < v[j - prefix]){
                                v[j - prefix] =  intensity[i][j];     
                   }        
           }     
       }  
       return v;      
}

vector<db> Intensity::avecol(){
       vector<db> v((intensity[0].size() - prefix), 0);
       for(long long i = 0; i < intensity.size(); i ++){
           for(int j = prefix; j < intensity[i].size(); j ++){
                      v[j - prefix] +=  intensity[i][j];           
           }     
       }  
       for(int i = 0; i < v.size(); i ++){
               v[i] /= intensity.size(); 
       }
       return v;       
}
vector<db> Intensity::avebase(){
       vector<db> v(ceil((intensity[0].size() - prefix) / bsize), 0);
       for(long long i = 0; i < intensity.size(); i ++){
           for(int j = prefix; j < intensity[i].size(); j += bsize){
                      for(int k = j; k < j + bsize; k ++){
                              v[floor((k - prefix) / bsize)] += intensity[i][k];
                      }           
           }     
       }  
       for(int i = 0; i < v.size(); i ++){
               v[i] /= intensity.size(); 
       }
       return v;
}

vector<db> Intensity::aveatcg(){
       vector<db> v(ceil((intensity[0].size() - prefix)), 0);
       vector<db> counter(ceil((intensity[0].size() - prefix)), 0);
       for(long long i = 0; i < intensity.size(); i ++){
           for(int j = prefix; j < intensity[i].size(); j += bsize){
                      db temp = -1e10;
                      int position = -1;
                      for(int k = j; k < j + bsize; k ++){
                              if(intensity[i][k] > temp){
                                                temp  = intensity[i][k];
                                                position = k - prefix;
                              }
                      }   
                      v[position] += temp;
                      counter[position] ++;        
           }     
       }  
       for(int i = 0; i < v.size(); i ++){
               v[i] /= (counter[i] + 1e-10); 
       }
       return v;                
}

vector<db> Intensity::colquantile(float level){
        vector<db> out;
        vector< vector<db> > v;
        long long position = round(level * intensity.size())-1;
        //cout<<position<<endl;
        for(int j = prefix; j < intensity[0].size(); j++){
                vector<db> temp;
                for(long long i = 0; i < intensity.size(); ++i){
                        temp.push_back(intensity[i][j]);        
                }
                sort(temp.begin(),temp.end());
                v.push_back(temp);
        }
        for(int i = 0; i < v.size(); i ++){
               //cout<<v[i][position]<<endl;
               out.push_back(v[i][position]);
        }
        return out;
}

