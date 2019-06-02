
// 效率与鲁棒性 
#include "myTime.h"
#include "memory.h"
#include "multithreading.h"
#include "errorStream.h"

#include "findFile.h"
#include "readWriteTXT.h"

#include "slide.hpp"

// 图像分析 
#include "grid.h"
#include "check.h"
#include "block.h"
#include "field.h"
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
#include "BB.h"

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


vector< vector< vector< vector< pair<float, float> > > > > allpeaks;
vector< vector< vector< vector< bool > > > > allflag;
vector<image> ig;
vector< vector< vector< pair<int, int> > > > afp;
vector< vector< pair<float, float> > > awp;
map< pair< int, pair<int, int> >, bool > ag;
vector< vector<double> > amr;
vector< vector< vector< vector< bool > > > > templateArray;


int ii1;
int ii2;
int ii3;
int ii4;
int ii5;
int ii6;
int ii7;
int ii8;

pthread_mutex_t mutex;
static void* runGrid1(void*){
   
   vector< vector< pair<int, int> > > fp = afp[ii1];
   image im = ig[ii1];
   vector< pair<float, float> > wp = awp[ii1];//读，安全 
   
   vector< vector< vector< bool > > > outflag;
   
   vector<double> mr;
   
   cout<<"Get Grid..."<<endl;
   grid gd;
   
   bool istpf = true;
   if(ii1 >= 4){
            istpf = false;     
   }
   
   vector< vector< vector< pair<float, float> > > > gp = gd.fit(im, fp, wp, outflag, mr, templateArray[ii1 % 4], istpf);

   pthread_mutex_lock (&mutex);    
   amr[ii1] = mr;
   allflag[ii1] = outflag;//写，不安全 ,加锁 
   allpeaks[ii1] = gp; 
   pthread_mutex_unlock(&mutex);
}

int main(void){
    
/////////////////////////////////  
string pi = "/home/xuweibin/basecall/mine/basecall_module_900/temp/zebra900";  
string of = "zebra900_block";
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
 
 
vector< vector<db> > its;
vector< vector<db> > inoise;
   
vector<image> allbim;  
   
vector< vector<double> > ala;
vector< vector<double> > offset;
vector< vector<double> > mr;
vector< vector<double> > bb;
        
for(int i = cl - 4 * cycle; i < cl; i ++){
   cout<<"Get Image..."<<endl;    
   readWriteTIFF rwt;
   rwt.load(tf[i]);
   image im(rwt);
   ig.push_back(im);
}

   cout<<"Image Draw..."<<endl;
   imageAnalysis ima;
   //ima.draw(ig, iar);
   
   cout<<"\nImage Analysis..."<<endl;
for(int i = 0; i < ig.size(); i ++){ 
   cout<<"\nImage:"<<(i + 1)<<"\tCycle:"<<(i/4 + 1)<<endl;
   
   image im = ig[i]; 
   
   cout<<"Weight Filter..."<<endl;
   gaussWeighting gw;   
   gw.filter(im);    
  
   cout<<"Top Hat..."<<endl;
   erodeDilate ed;
   ed.erode(im);    
 
   cout<<"Wiener..."<<endl;
   wiener wn;
   //wn.filtering(im);  
         
   vector< vector<long long> > bim;
   cout<<"Registration..."<<endl;
   registration rg;
   vector< pair<float, float> > peak = rg.getIRPosition(im, 0.3, ala, bim, true); 
  
   cout<<"Get Peak..."<<endl;
   peakPosition pk;
   vector< pair<float, float> > wp;  
   wp = pk.getPeak(im, peak, false);
   
   cout<<"Peak Reconstruct..."<<endl;
   CDReconstruct cdr;
   //cdr.fit2(wp, im);//////////////////////////////////////////////////MLR fit//

////////////////////////////////////////////////////////////////////////////////
   vector< vector<pre> > content(im.getHeight(), vector<pre>(im.getWidth(), 0));
   
   //*////////////////////////////////////////////bit image//////////////////////
   for(long long k1 = 0; k1 < bim.size(); k1++){
            for(long long k2 = 0; k2 < bim[k1].size(); k2++){
                     content[k1][k2] = bim[k1][k2];
            }        
   }
   //*//////////////////////////////////////////////////////////////////////////
   
   /*//////////////////////////////////////peak image//////////////////////////  
   for(long long k = 0; k < peak.size(); k++){
            content[round(peak[k].first)][round(peak[k].second)] = 1;         
   }  
   //*//////////////////////////////////////////////////////////////////////////
   
   image imt;
   imt.setImage(content);   
////////////////////////////////////////////////////////////////////////////////

   awp.push_back(wp);
   allbim.push_back(imt);///////////////////////////////////////////////////////
   
   ig[i] = im;/////original intensity reconstruct, not intensity after filtering
} 
 
mtm.end();
mtm.getTime();
mtm.b_print();
mtm.start();
mem.memStat();  


for(int i = 0; i < ig.size(); i ++){ 
     vector< vector< vector< pair<float, float> > > > gp;
     vector< vector< vector< bool > > > outflag;
     vector<double> mr;
     amr.push_back(mr);
     allflag.push_back(outflag);
     allpeaks.push_back(gp);  
}
  
//*/////////////////////////////////////////////////////////////////////////////
int ref_size = 4;///////////////////////////////////////////////////////////////
vector< vector< vector< pair<int, int> > > > acp;
vector< vector< vector<int> > > axy;
for(int i = 0; i < ref_size; i ++){
   cout<<"\nGet Check..."<<endl;                
   check ck;
   vector< vector<int> > cxy;
   vector< vector< pair<int, int> > > cp = ck.getCheck2(allbim[i], cxy);
   acp.push_back(cp);
   axy.push_back(cxy);
}
 
for(int i = 0; i < ig.size(); i ++){ 
   cout<<"\nCycle:"<<(i/4 + 1)<<endl;
   cout<<"Image "<<i<<"..."<<endl;
   image imt = allbim[i]; 
   
   cout<<"Get Field..."<<endl;
   vector< vector< pair<int, int> > > cp = acp[i % 4];  
   vector< vector<int> > cxy = axy[i % 4];
   field fd;
   cp = fd.getField2(imt, cp, cxy);   
   
   //*///////////////////////////////////////////////////////////////////////////
   if(i < 8){
   vector< vector<pre> > I = imt.getImage();
   vector< pair<float, float> > wp = awp[i];
   readWriteTIFF rwt;
   rwt.setIm(I);
   stringstream ss;
   ss<<i;
   rwt.save( path + of + "_bitImage" + ss.str() + ".tif");
   I = ig[i].getImage();
   for(int k = 0; k < cxy.size(); k++){
         int x = cxy[k][0];
         int y = cxy[k][1];
         for(int m = x - 4; m <= x + 4; m++){
                 for(int n = y - 4; n <= y + 4; n++){
                         I[m][n] = 60000;        
                 }        
         }          
   }
   for(vector< pair<float, float> >::iterator it = wp.begin(); it != wp.end(); it++){
               I[round((*it).first)][round((*it).second)] = 60000;           
   }
   rwt.setIm(I);
   rwt.save( path + of + "_cross" + ss.str() + ".tif");  
   }    
   //*//////////////////////////////////////////////////////////////////////////

   afp.push_back(cp);  
}

allbim.clear();
 
templateArray.resize(4);////////////////////////////////////////////////////////
cout<<"\nFit Grid..."<<endl;
pthread_mutex_init (&mutex,NULL);
multithreading mt;
int thread_number = 1;//////////////////////////////////////////////////////////
for(int i = 0; i < ig.size(); i += thread_number){ 
   cout<<"\nCycle:"<<(i/4 + 1)<<endl;
   cout<<"Image "<<i<<"..."<<endl;
   ii1 = i;
   //ii2 = i + 1;////////////////////////////////////
   //ii3 = i + 2;////////////////////////////////////
   //ii4 = i + 3;////////////////////////////////////
   vector<void* (*)(void*)> threads;
   threads.push_back(runGrid1);
   //threads.push_back(runGrid2);////////////////////
   //threads.push_back(runGrid3);////////////////////
   //threads.push_back(runGrid4);////////////////////
   mt.setThreads(threads);
   mt.run();
}
//*/////////////////////////////////////////////////////////////////////////////

   bool fnee = false;
   cout<<"Check Field..."<<endl;
   int cfn = allflag[0].size();
   for(int j = 1; j < allflag.size(); j++){
           if(cfn != allflag[j].size()){
                  cout<<"\nField Not Equal Error!"<<endl;
                  cerr<<"\nField Not Equal Error!"<<endl;
                  fnee = true;
                  break;    
           }    
           if(cfn == 0){
                  cout<<"\nNo Field Error!"<<endl;
                  cerr<<"\nNo Field Error!"<<endl;
                  fnee = true;
                  break;    
           }     
   } 
   if(fnee){
     ala.clear();
     offset.clear();
     mr.clear();
     bb.clear();
     amr.clear();
     awp.clear();
     allflag.clear();
     allpeaks.clear();
     vector<image>(ig).swap(ig);
     afp.clear();
     its.clear();
     inoise.clear();
     ag.clear();
     vector<image>(allbim).swap(allbim);
     continue;         
   }

   cout<<"Write Image Information..."<<endl;
   readWriteCH rwc;
   rwc.setContent(ala);
   rwc.writeCH(arear); 
   rwc.setContent(offset);
   rwc.writeCH(offsetr);
   rwc.setContent(amr);
   rwc.writeCH(matchr); 
  
   
mtm.end();
mtm.getTime();
mtm.b_print();
mtm.start();
mem.memStat();  

cout<<"Merge Peak..."<<endl;

for(int k = 0; k < allflag.size(); k ++){      
	for(int j = 0; j < allflag[k].size(); j++){
		for(int a1 = 0; a1 < allflag[k][j].size(); a1++){
			for(int a2 = 0; a2 < allflag[k][j][a1].size(); a2++){
			    allflag[k][j][a1][a2] = true;           				
			}
		}
	}
}

    cout<<"BB..."<<endl;
    BB bt;
    bt.MLR(ig, allpeaks);////////////////////////////////////////
    
    rwc.setContent(bb);
    rwc.writeCH(bbr);

cout<<"Get Intensity..."<<endl;
for(int i = 0; i < ig.size(); i++){
        image im = ig[i];
        vector< vector< vector< pair<float, float> > > > gp = allpeaks[i];
   if(i == 0){
        double lane = 1;
        for(int j = 0; j < gp.size(); j++){
                for(long k1 = 0; k1 < gp[j].size(); k1++){
                   for(long k2 = 0; k2 < gp[j][k1].size(); k2++){
                           if(allflag[i][j][k1][k2]){
                               vector<double> temp;
                               temp.push_back(lane);////////////////////////////
                               temp.push_back((double)j);///////////////////////
                               temp.push_back((double)k1);
                               temp.push_back((double)k2); 
                               its.push_back(temp);
                               inoise.push_back(temp);
                           }
                           
                   }               
                }        
        }     
   }
        vector< vector<pre> > v = im.getImage();  
        vector< vector<pre> > vnoise = im.getNoise();
        long long counter = 0;
        for(int j = 0; j < gp.size(); j++){
                for(long k1 = 0; k1 < gp[j].size(); k1++){
                   for(long k2 = 0; k2 < gp[j][k1].size(); k2++){
                            if(allflag[i][j][k1][k2]){
                                 int x = round(gp[j][k1][k2].first);
                                 int y = round(gp[j][k1][k2].second);
                                 //采用插值，查找到对应亚像素的强度 
                                 double itv = 0;
                                 for(int xi = x - 1; xi <= x + 1; xi++){
                                         for(int yi = y - 1; yi <= y + 1; yi++){
                                                 itv += v[xi][yi];        
                                         }        
                                 }                                
                                 (its[counter]).push_back(itv);
                                 (inoise[counter++]).push_back(v[x][y] * 1.0 / vnoise[x][y]);
                            }
                   }               
                }        
        }        
}

mtm.end();
mtm.getTime();
mtm.b_print();
mtm.start();
mem.memStat();

   ala.clear();
   offset.clear();
   mr.clear();
   bb.clear();   
   amr.clear();
   awp.clear();
   allflag.clear();
   allpeaks.clear();
   vector<image>(ig).swap(ig); 
   afp.clear();
   ag.clear();
   vector<image>(allbim).swap(allbim); 
   Intensity itp;
   
   itp.setIntensity(its);  
   itp.setNoise(inoise);   
   its.clear();  
   inoise.clear();     
   itp.writeIntensity(beforer);
   itp.writeNoise(noiser);  

      
   cout<<"\nIntensity Analysis..."<<endl;   
   cout<<"Intensity Draw..."<<endl;
   intensityAnalysis ita;
   //ita.draw(itp, intensityr);  ///////////////////////////////////////////////
   
//image analysis=======================dnb====================================== 



//intensity analysis=============================================intensity分为block 
///////////////////////////////intensity test 
   //Intensity itp;  
   //readWriteCH rwc;
   //itp.readIntensity(beforer);
   //itp.readNoise(beforer);///////
////////////////////////////////     
   
   calling ci;
   vector<Intensity> ait = itp.crop(2000000);///////////////////////////////////
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
    itp.readNoise(noiser);
    
    cout<<"Charity..."<<endl;
    charity ch;
    ch.compute(itp, charityr);   
    
    cout<<"Calling..."<<endl;
    ci.call(itp, fqr, path + of); 
    
    its.clear();
    inoise.clear();
    
//intensity analysis============================================================

mtm.end();
mtm.getTime();
mtm.b_print();
mem.memStat();

system(("mp " + fqr + " /home/xuweibin/workgroup/analysis/genome_reference/Ecoli.fa " + path + " N" ).c_str());
system(("sh " + path + of + "_fq" + ts + "_res/map.sh" ).c_str());

}

   tf.clear();
 
}
