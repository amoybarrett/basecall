/*
 * @kangkang
 */
 
 #include "CDReconstruct.h"

using namespace std;
using namespace cv;

void CDReconstruct::fit(vector< pair<float, float> >  &allpeaks, image & im){//包括强度和位置重建 
             vector< vector< pre > > imt = im.getImage();
             vector< vector< pre > > out = imt;
             for(int j = 0; j < allpeaks.size(); j++){
                                  int x = round(allpeaks[j].first);
                                  int y = round(allpeaks[j].second);
                                  if(x > gsize/2 && x < imt.size() - gsize/2 && y > gsize/2 && y < imt[0].size() - gsize/2){
                                       vector< vector<double> > z;
                                       pair<float, float> pos;
                                       for(int t1 = x - gsize/2; t1 <= x + gsize/2; t1 ++){
                                               vector<double> temp;
                                               for(int t2 = y - gsize/2; t2 <= y + gsize/2; t2 ++){
                                                       temp.push_back(imt[x][y]);        
                                               }        
                                               z.push_back(temp);
                                       }    
                                       
                                       if(z.size() != 0){
                                                   squareFit sf(z, gsize);
                                                   long temp =  round(sf.interpolation(pos));
                                                   if(temp > TIFF_UP){
							                               temp = TIFF_UP;
			                                       }
						                           if(temp < TIFF_DOWN){
							                               temp = TIFF_DOWN;
                                                   }
						                           if(out[x][y] < temp)
						                                        out[x][y] = temp;	
                                                                allpeaks[j] = make_pair(x + pos.first, y + pos.second);					                
                                                   }
                                        }  
                                        
                                                     
             }   
             im.setImage(out);     
}

void CDReconstruct::fit2(vector< pair<float, float> >  &allpeaks, image & im){//包括强度和位置重建 


               vector< vector<double> > xx1;  
               vector<double> yy1; 
               vector< vector<pre> > I = im.getImage();
               vector< vector<pre> > out = im.getImage();
               
               for(vector< pair<float, float> >::iterator it = allpeaks.begin(); it != allpeaks.end(); it++){
                           int x = round((*it).first);
                           int y = round((*it).second); 
                           if(x > 0 && x < im.getHeight() - 1 && y > 0 && y < im.getWidth() - 1){
                                   vector<double> t;
                                   for(int i = x - 1; i <= x + 1; i++){
                                           for(int j = y - 1; j <= y + 1; j++){
                                                   if(i != x || j != y)
                                                        t.push_back(I[i][j]);        
                                           }        
                                   }  
                                   xx1.push_back(t);
                                   yy1.push_back(I[x][y]);
                           }         
               }
 
               vector< vector<double> > xt1;    
               if(xx1.size() != 0){
                   for(long long r1 = 0; r1 < xx1[0].size(); r1++){
                       vector<double> temp;
                       for(int r2 = 0; r2 < xx1.size(); r2++){
                               temp.push_back(xx1[r2][r1]);        
                       }     
                       xt1.push_back(temp);   
                   } 
               }
               
               mregression mr1(xt1,yy1);
               double *a1 = mr1.output(); 
               
               for(vector< pair<float, float> >::iterator it = allpeaks.begin(); it != allpeaks.end(); it++){
                           int counter = 0;
                           double temp = 0;
                           int x = round((*it).first);
                           int y = round((*it).second); 
                           if(x > 0 && x < im.getHeight() - 1 && y > 0 && y < im.getWidth() - 1){
 
                                   for(int i = x - 1; i <= x + 1; i++){
                                           for(int j = y - 1; j <= y + 1; j++){
                                                   if(i != x || j != y)
                                                        temp += I[i][j] * a1[counter++];       
                                           }        
                                   }                                  
		                           long tu = round(temp);
		                           if(tu > TIFF_UP){tu = TIFF_UP;}else if(tu < TIFF_DOWN){tu = TIFF_DOWN;}
                                   out[x][y] = tu;                                        
                                   
                           }         
               }
               im.setImage(out); 
                                  

}

