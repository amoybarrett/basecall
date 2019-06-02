/*
 * @kangkang
 */
#include "imageAnalysis.h"


using namespace std;

void imageAnalysis::draw(vector<image> &im, const string &outfile){
    vector< vector<double> > out;
    long i = 0;
    for(vector<image>::iterator it = im.begin(); it != im.end(); it += 4){
        vector<double> temp;
        ////////////////////////////////////////////////
        temp.push_back(i + 1);
        temp.push_back((*(it + 0)).sum());
        temp.push_back((*(it + 1)).sum());
        temp.push_back((*(it + 2)).sum());
        temp.push_back((*(it + 3)).sum());
        
        temp.push_back((*(it + 0)).average());
        temp.push_back((*(it + 1)).average());
        temp.push_back((*(it + 2)).average());
        temp.push_back((*(it + 3)).average());
        
        temp.push_back((*(it + 0)).variance());  
        temp.push_back((*(it + 1)).variance());
        temp.push_back((*(it + 2)).variance());
        temp.push_back((*(it + 3)).variance());     
                
        temp.push_back((*(it + 0)).LaplacianGradient());
        temp.push_back((*(it + 1)).LaplacianGradient());
        temp.push_back((*(it + 2)).LaplacianGradient());
        temp.push_back((*(it + 3)).LaplacianGradient());    
        out.push_back(temp); 
        /////////////////////////////////////////////////////      
        i++;
    }
  
  readWriteCH rwc;
  rwc.setContent(out);
  rwc.writeCH(outfile);
}

/*
int main(){
     readWriteTIFF rwt;
	rwt.op_load("test_check_dnb9.tif");
	image im(rwt);
	imageAnalysis ia;
	ia.analysis(im);
        rwt.setOp_im(im.getOp_im());
        rwt.op_save("test_check_dnb9_new.tif");
}
*/
