/*
 * @kangkang
 */
#include "calling.h"

/*
 * 1.ǿ�Ƚ�����Ȩ�ؼ����������ƣ������С�滮�������С��Ȼ����С���ˣ�������飬������ģ���˻��ţ����ɽ���Ŵ��㷨����Ⱥ�㷨�� 
 * 2.��������svm��bayes��ANN��
 * ���ؼ���charity��ͼƬ�Աȶȣ�ͼƬƽ��ǿ�ȣ�ͼƬ�ܺͣ�ͼƬ�ݶ� ,ͼƬ����������(image::noise)��offset(cycle�ڣ�cycle��)��ͼ��block��tile��������� ,bb,ct,pp
 * ������������������������ɣ�
 * Ŀ�꺯��(mismatch,ATCG(4ֵ),ǿ�ȣ����,�����ֵ�����ľأ�����)������ѵ��
 */

using namespace std;

void calling::call(Intensity &its, const string &outfile, const string &infile){
       vector< vector<db> > v = its.getIntensity();
       vector< vector<db> > inoise = its.getNoise();
       vector<db> min = its.colquantile(0.01);/////////////////////////////////
       vector<db> max = its.colquantile(0.99);/////////////////////////////////
       readWriteGZ rwg;
       rwg.openOutGZ(outfile);
       string line1,line2,line3,line4;
       line3 = "+^_^";  
       stringstream ss;
       string res;
       
       vector< vector< vector<double> > > vv;//score,��Ԫ������� 
       
       
       /*      
       readWriteCH rwc;
       rwc.readCH(infile + "_charity.txt");//�� 
       vector< vector<double> > chy = rwc.getContent();
       rwc.readCH(infile + "_image.txt"); //�� 
       vector< vector<double> > iq = rwc.getContent();
       rwc.readCH(infile + "_offset.txt"); //С 
       vector< vector<double> > offset = rwc.getContent();       
       rwc.readCH(infile + "_match.txt"); //�� 
       vector< vector<double> > match = rwc.getContent();  
       
       

       for(long long i = 0; i < chy.size(); i++){
                vector< vector<double> > vvt;
                for(int j = 0; j < chy[i].size(); j++){
                      vector<double> vvtt;   
                      
                      double noise = -1;
                      for(register short k = 0; k < bsize; k++){
                                   if(noise < inoise[i][j * bsize + prefix + k]){
                                            noise =  inoise[i][j * bsize + prefix + k];        
                                   }                                  
                      }
                      
                      
                      float tos = 0;
                      float ta = 0;
                      for(register short k = 0; k < bsize; k++){
                                   tos = sqrt((offset[j * bsize + k][0] - offset[j * bsize][0]) * (offset[j * bsize + k][0] - offset[j * bsize][0]) + (offset[j * bsize + k][2] - offset[j * bsize][2]) * (offset[j * bsize + k][2] - offset[j * bsize][2]));
                                   ta += (offset[j * bsize + k][1] - offset[j * bsize + k][0]) * (offset[j * bsize + k][3] - offset[j * bsize + k][2]);
                      }
                      
                      double var = 0;
                      double ave = 0;
                      for(register short k = 1; k < 2 * 4 + 1; k++){
                                   if(k <= 4){
                                         var += iq[j][k];
                                   }else{
                                         ave += iq[j][k];      
                                   }
                      }
                      
                      double am = 0;
                      for(register short k = 0; k < 4; k++){
                                   for(short l = 0; l < match[j * bsize + k].size(); l++)
                                        am += match[j * bsize + k][l];             
                      }
                      am /= (4 * match[0].size());
                      
                      vvtt.push_back(noise);
                      vvtt.push_back(chy[i][j]);
                      vvtt.push_back(am);
                      vvtt.push_back(tos);
                      vvtt.push_back(ta);   
                      vvtt.push_back(var);
                      vvtt.push_back(ave);                   
                      
                      vvt.push_back(vvtt);       
                }         
                vv.push_back(vvt);
                
       }
       
       chy.clear();
       iq.clear();
       offset.clear();
       match.clear();
       */
       
       vector< vector< short > > allbase;
       
       //... = svm::train(v, inoise, allbase);
       //... = ANN::train(v, inoise, allbase);
       
       //bayescall byc;
       //byc.train(v, inoise, allbase);///////////////////////////////////////////
        
       for(long long i = 0; i < v.size(); i++){
                ss.clear();
                int block, x, y;
                block = v[i][1];
                x = v[i][2];
                y = v[i][3];
                ss<<"-"<<block<<":"<<x<<":"<<y;// lane,slide,read1,read2,up,down 
                ss>>res;
                line1 = "@^*^" + res;
                line2 = "";
                line4 = "";
                
                for(int j = prefix; j < v[i].size(); j += bsize){

                                int base = getBase(v, i, j);                                  
                                //double error = getRoughProbability(v, i, j, base);
                                double error = 0; //getProbability(v, i, j, base, min, max); ////////////////////////////                                
                                
                                //double error = byc.getProbability(v, inoise, allbase, i, j);  
                                //int base = allbase[i][(j - prefix) / bsize];                                                                                                                                                                                                               
                                                                                            
                                
                                int score = getScore(error);                                
                                
                                if(base == 0){
                                      line2 += "G";/////////////////////////////////ע���Ӧ��ϵ       
                                }else if(base == 1){
                                      line2 += "C"; ////////////////////////////////     
                                }else if(base == 2){
                                      line2 += "A"; /////////////////////////////////     
                                }else if(base == 3){
                                      line2 += "T"; /////////////////////////////////     
                                }else{
                                      line2 += "N";//////////////////////////////////      
                                }
                                
                                char s = (char)(QualitySystem + score);
                                line4 += s;
                }    
                
                rwg.writeGZLine(line1+"\n");
                rwg.writeGZLine(line2+"\n");
                rwg.writeGZLine(line3+"\n");
                rwg.writeGZLine(line4+"\n");    
       }    
       rwg.closeOutGZ();         
}


short calling::getBase(vector< vector<db> > &its, long long c, int cc){
      db temp = 1e-10;
      short out = 0;
      for(int i = cc; i < cc + bsize; i++){
                    if(its[c][i] > temp){
                                 temp = its[c][i];
                                 out = i % bsize;            
                    }
      }
      short ct = 0;
      for(int i = cc; i < cc + bsize; i++){
              if(its[c][i] == temp) ct++;
      }
      if(ct > 1) out = bsize;
      return out;
}

double calling::getRoughProbability(vector< vector<db> > &its, long long i, int j, int base){
       double t1 = 0;
       double t2 = 0;
       for(int k = j; k < j + bsize; k++){
            if(k != j + base){
                 t1 += its[i][k];     
            }           
            t2 += its[i][k];
       }
       return (t1 / t2);
}

double calling::getProbability(vector< vector<db> > &its, long long i, int j, int base, vector<db> &min, vector<db> &max){
       vector<double> pb;
       for(int k = j; k < j + bsize; k++){
              mu = (max[k - prefix] - min[k - prefix]) / 2;   
              double pbt = erf(its[i][k], min[k - prefix]);
              pb.push_back(pbt);      
       }
       double t1 = 0;
       double t2 = 0;
       for(int k = j; k < j + bsize; k++){
            if(k != j + base){
                 t1 += pb[k - j];     
            }           
            t2 += pb[k - j];
       }
       return (t1 / t2);
}

double calling::erf(db p, db m){//���sigma�ϴ����������t=muʱ����Ϊ0.5����<t��>t���мӼ����� 
       double out = 0;
       for(double i = m; i <= p; i += precision){
            double t = i + 0.5 * precision;
            out += 1.0 / (sqrt(2 * PI) * sigma) * pow(E, -((t - mu) * (t - mu) / (2 * sigma * sigma))) * precision;                
       }
       return out;
}

short calling::getScore(double error){
      return score::phred(error);    
}
