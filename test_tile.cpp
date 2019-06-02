
// 效率与鲁棒性 
#include "myTime.h"
#include "memory.h"
#include "multithreading.h"
#include "errorStream.h"

#include "readWriteTXT.h"
#include "findFile.h"

#include "slide.hpp"

// 图像分析 
#include "affineTransformation.h"
#include "imageCrop.h"
#include "FFT.h"
#include "image.h"
#include "gaussWeighting.h"
#include "readWriteTIFF.h"
#include "registration.h"
#include "erodeDilate.h"
#include "peakPosition.h"
#include "Intensity.h"
#include "CDReconstruct.h"
#include "charity.h"
#include "wiener.h"
#include "block.h"
#include "check.h"

// 强度分析
#include "phasingPrephasing.h"
#include "Intensity.h"
#include "crosstalk.h"
#include "normalization.h"

// 图像与强度画图
#include "imageAnalysis.h"
#include "intensityAnalysis.h" 

// call模型 
#include "calling.h"

// 结果分析 
#include "htmlReport.h"

// GUI
#include "GUI.h"

//mexican_hat 保留负数， 强度提取亚像素 , 边缘使用grid fit 
 

using namespace std;
using namespace cv;


int main(void){
  
/////////////////////////////////  
string pi = "/home/xuweibin/basecall/mine/basecall_module_900/temp/zebra900";  
string of = "zebra900_tile";
int cycle = 32;
/////////////////////////////////

/////////////////////////////////
string path = "./test/" + of + "/";
string cm = "mkdir " + path;
system(cm.c_str());
string list = path + of + ".list";
/////////////////////////////////

  
//image analysis=======================dnb======================================
   cout<<"Find File..."<<endl;
   findFile ff;
   ff.find(pi, list);
   readWriteTXT rwtxt;
   rwtxt.readTXT(list);
   vector<string> tf = rwtxt.getContent();
   

for(int cl = cycle * 4; cl <= tf.size(); cl += cycle * 4){//////////////////////

stringstream ss;
ss<<(cl / cycle / 4);
string ts = ss.str();       
string iar = path + of + "_image" + ts + ".txt";
string arear = path + of + "_area" + ts +".txt";
string offsetr = path + of + "_offset" + ts + ".txt";
string matchr = path + of + "_match" + ts +".txt";
string bbr = path + of + "_bb" + ts +".txt";
string beforer = path + of + "_before" + ts + ".txt";
string normalizer = path + of + "_normalize" + ts + ".txt";
string noiser = path + of + "_noise" + ts + ".txt";
string charityr  = path + of + "_charity" + ts + ".txt";
string intensityr = path + of + "_intensity" + ts + ".txt";
string crosstalkr = path + of + "_crosstalk" + ts + ".txt";
string afterr = path + of + "_after" + ts + ".txt";
string ppr = path + of + "_pp" + ts + ".txt";
string pprr = path + of + "_app" + ts + ".txt";
string fqr = path + of + "_fq" + ts + ".gz";
  
memory mem;
myTime mtm;
mtm.b_print();
mtm.start();
mem.memStat();  
  
vector<image> ig;  
  
 
for(int i = cl - cycle * 4; i < cl; i ++){
   cout<<"Get Image..."<<endl;    
   readWriteTIFF rwt;
   rwt.load(tf[i]);
   image im(rwt);
   ig.push_back(im);
}

   cout<<"Image Draw..."<<endl;
   imageAnalysis ima;
   //ima.draw(ig, iar);  
    
    //image analysis=======================cluster=====================
   
   vector< vector<db> > its;
   vector< vector<db> > inoise; 
   
   vector< vector<double> > offset;
   vector< vector<double> > ala;
   
   vector< pair<float, float> > peak;

   readWriteCH rwc;
   
for(int i = 0; i < ig.size(); i ++){
   cout<<"\nImage:"<<(i + 1)<<"\tCycle:"<<(i/4 + 1)<<endl;
   
   image im = ig[i]; 
   
   cout<<"Weight Filter..."<<endl;
   gaussWeighting gw;   
   gw.filter(im);////////////////////////////////////////////////mr/////////////    
   
   cout<<"Top Hat..."<<endl;
   erodeDilate ed;
   ed.erode(im);    
 
   cout<<"Wiener..."<<endl;
   wiener wn;
   //wn.filtering(im);    

   ig[i] = im;
}

  
   cout<<"\nImage Crop..."<<endl;
   imageCrop icp(460, 460);/////////////////////////////////////////////////////
   vector< vector<image> > cig = icp.subimage(ig);
  
for(int ic = 0; ic < cig[0].size(); ic++){  
     for(int ib = 0; ib < cig.size(); ib++){
                ig[ib] = cig[ib][ic];
     }   

for(int i = 0; i < ig.size(); i ++){  
   cout<<"Image "<<i<<"..."<<endl;
           
   image im = ig[i];        
   vector< vector<long long> > bim;
   cout<<"Registration..."<<endl;
   registration rg;
   vector< pair<float, float> > peak = rg.getIRPosition(im, 0.4, ala, bim, true); 
   
   cout<<"Get Peak..."<<endl;
   peakPosition pk;
   vector< pair<float, float> > wp;  
   wp = pk.getPeak(im, peak, true);///////////////////////////////////////////////
   
   cout<<"Peak Reconstruct..."<<endl;
   CDReconstruct cdr;
   //cdr.fit2(wp, im);/////////////////////////////////////////////MLR fit///////
   
   cout<<"Fit and AffineTransformation..."<<endl;                
   block bl;
   bl.fit2(im, wp);  
   
   ig[i] = im; /////original intensity reconstruct, not intensity after filtering
}                


//if random, then make sample for rotation and scale before FFT registration, use the dot pair of ATCG image and corresponding the dot pair of reference map image to compute linear distortion
//4 map can be constructed, finally a reference coordinate system can be built 
cout<<"\nMake Reference Map..."<<endl;
FFT fft;
pair<int, int> xy;
xy = fft.minMax(ig[0], ig[1], true); 
image ref_second = ig[1];
affineTransformation atf;
atf.translation(ref_second, xy);
image ref_first = ig[0];////////////////////////////////////////////////////////
vector< vector<pre> > iv1 = ref_first.getImage();
vector< vector<pre> > iv2 = ref_second.getImage();
for(int i = 0; i < iv1.size(); i++)
        for(int j = 0; j < iv1[i].size(); j++){
                if(iv1[i][j] < iv2[i][j]){
                         iv1[i][j] = iv2[i][j];         
                }        
        }
ref_first.setImage(iv1);
 
cout<<"Registration..."<<endl;   
for(int i = 0; i < ig.size(); i ++){ 
   cout<<"\nImage:"<<(i + 1)<<"\tCycle:"<<(i/4 + 1)<<endl; 
   image im = ig[i];        
   FFT fft;
   pair<int, int> xy;
   xy = fft.minMax(ref_first, im, true);     
   cout<<"Offset:("<<xy.first<<","<<xy.second<<")"<<endl;   
   vector<double> tos;
   tos.push_back(xy.first);
   tos.push_back(xy.second);
   offset.push_back(tos);
   
   affineTransformation atf;
   atf.translation(im, xy);
   
   ig[i] = im;
}

   int number = 5;///////////////////////////////////////////////////////////////// 
   image ref = ig[number * 4];    
   vector< vector<pre> > ref2 = ig[number * 4 + 1].getImage();
   vector< vector<pre> > ref3 = ig[number * 4 + 2].getImage();
   vector< vector<pre> > ref4 = ig[number * 4 + 3].getImage();
   vector< vector<pre> > refd1 = ref.getImage();
   for(int t1 = 0; t1 < refd1.size(); t1++){
        for(int t2 = 0; t2 < refd1[t1].size(); t2++){
                if(refd1[t1][t2] < ref2[t1][t2])
                           refd1[t1][t2] = ref2[t1][t2];
                if(refd1[t1][t2] < ref3[t1][t2])
                           refd1[t1][t2] = ref3[t1][t2];
                if(refd1[t1][t2] < ref4[t1][t2])
                           refd1[t1][t2] = ref4[t1][t2];                                                                     
        }        
   }//////////////////////////////////////////////////////////////////////////// 
   
   ref.setImage(refd1);    
   cout<<"\nGet Peaks..."<<endl;
   registration rg;
   vector< vector<long long> > bim;
   peak = rg.getIRPosition(ref, 0.2, ala, bim, false);/////////////////////////////////   
   
/////////////////////////////////////////////////   
   cout<<"Get Intensity..."<<endl;
   vector< vector<db> > itst;
   vector< vector<db> > inoiset; 
for(int i = 0; i < ig.size(); i++){
        image im = ig[i];
        vector< vector<pre> > v = im.getImage();  
        vector< vector<unsigned short> > vnoise = im.getNoise();
   if(i == 0){
        for(vector< pair<float, float> >::iterator itt = peak.begin(); itt != peak.end(); itt++){
                               vector<double> temp;
                               temp.push_back(0);///////////////////////////////
                               temp.push_back(ic);//////////////////////////////
                               temp.push_back((*itt).first);
                               temp.push_back((*itt).second); 
                               itst.push_back(temp);
                               inoiset.push_back(temp);                                
        }
   }
        long long counter = 0;
        for(vector< pair<float, float> >::iterator itt = peak.begin(); itt != peak.end(); itt++){
            int x = round((*itt).first);
            int y = round((*itt).second);
            //采用插值，查找到对应亚像素的强度 
            itst[counter].push_back(v[x][y]);
            inoiset[counter].push_back(v[x][y] * 1.0 / (vnoise[x][y] + 1e-10));   
            counter ++;              
        }
}

   its.insert(its.end(), itst.begin(), itst.end());
   inoise.insert(inoise.end(), inoiset.begin(), inoiset.end());

}
///////////////////////////////////////////////////

   rwc.setContent(ala);
   rwc.writeCH(arear); 
   rwc.setContent(offset);
   rwc.writeCH(offsetr); 


   offset.clear(); 
   vector<image>(ig).swap(ig); 
   ala.clear();
   peak.clear();

   Intensity itp;
   
   itp.setIntensity(its);  
   itp.setNoise(inoise);
   itp.writeIntensity(beforer);
   itp.writeNoise(noiser); 

   its.clear();  
   inoise.clear();
      
      
   cout<<"\nIntensity Analysis..."<<endl;   
   cout<<"Intensity Draw..."<<endl;
   intensityAnalysis ita;
   //ita.draw(itp, intensityr);  
//image analysis=======================cluster======================= 


   calling ci;
   vector<Intensity> ait = itp.crop(2000000);//////////////////////////////////////
for(int i = 0; i < ait.size(); i++){

    Intensity it(ait[i]); 
   
    crosstalk ct;
    normalization nl;
    phasingPrephasing pp; 
    if(0 == i){    
         cout<<"Crosstalk..."<<endl;
         ct.linearFit(it);//ct.linearFit(it),ct.polar(it)
    
         double** ctm =  ct.getMatrix();
         vector< vector<double> > ctmv(4, vector<double>(4, 0));
         for(int c1 = 0; c1 < 4; c1 ++){
            for(int c2 = 0; c2 < 4; c2++){
                ctmv[c1][c2] = ctm[c1][c2];            
            }        
         }
    
         rwc.setContent(ctmv);
         rwc.writeCH(crosstalkr); 
    
         it.writeIntensity(afterr);
         cout<<"Normalization..."<<endl;
         nl.normalize(it);
         it.writeIntensity(normalizer);
         cout<<"Phasing/Prephasing..."<<endl;
    
         vector<double> pptt;
         pp.correct(it, pptt);
    
         vector< vector<double> > ppt;
         ppt.push_back(pptt); 
         rwc.setContent(ppt);
         rwc.writeCH(ppr); 
       
         it.writeIntensity(pprr);
    }else{
          cout<<"Crosstalk..."<<endl;
          ct.linearFit(it);//ct.linearFit(it),ct.polar(it)
    
          double** ctm =  ct.getMatrix();
          vector< vector<double> > ctmv(4, vector<double>(4, 0));
          for(int c1 = 0; c1 < 4; c1 ++){
            for(int c2 = 0; c2 < 4; c2++){
                ctmv[c1][c2] = ctm[c1][c2];            
            }        
          }
    
          rwc.setContent(ctmv);
          rwc.writeCH2(crosstalkr); 
    
          it.writeIntensity2(afterr);
          cout<<"Normalization..."<<endl;
          nl.normalize(it);
          it.writeIntensity2(normalizer);
          cout<<"Phasing/Prephasing..."<<endl;
    
          vector<double> pptt;
          pp.correct(it, pptt);
    
          vector< vector<double> > ppt;
          ppt.push_back(pptt); 
          rwc.setContent(ppt);
          rwc.writeCH2(ppr); 
       
          it.writeIntensity2(pprr);             
    }
}
    ait.clear(); 

/////////////////////////////call test    
    //Intensity itp;
    //calling ci;
/////////////////////////////    
    
   itp.readIntensity(pprr);
   itp.readNoise(noiser);//////////////
    
   cout<<"Charity..."<<endl;
   charity ch;
   ch.compute(itp, charityr);   
    
   cout<<"Calling..."<<endl;
   ci.call(itp, fqr, path + of); 
   
   its.clear();
   inoise.clear();
    
    //intensity analysis============================================

mtm.end();
mtm.getTime();
mtm.b_print();
mem.memStat();

system(("mp " + fqr + " /home/xuweibin/workgroup/analysis/genome_reference/Ecoli.fa " + path + " N" ).c_str());
system(("sh " + path + of + "_fq" + ts + "_res/map.sh" ).c_str());

}

   tf.clear();

}
