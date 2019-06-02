/*
 * @kangkang
 */
#include "intensityAnalysis.h"

using namespace std;

void intensityAnalysis::draw(Intensity &its, const string &outfile){
      vector<double> maxcol = its.maxcol();
      vector<double> avebase = its.avebase();
      vector<double> colquantile = its.colquantile(0.95);
      vector<double> aveatcg = its.aveatcg();
      vector< vector<double> > out;
      for(int i = 0; i < avebase.size(); i ++){
              vector<double> temp;
              ////////////////////////////////////////////
              temp.push_back(i + 1);
              
              temp.push_back(maxcol[round(i * 4 + 0)]);
              temp.push_back(maxcol[round(i * 4 + 1)]);
              temp.push_back(maxcol[round(i * 4 + 2)]);
              temp.push_back(maxcol[round(i * 4 + 3)]);
              
              temp.push_back(colquantile[round(i * 4 + 0)]);
              temp.push_back(colquantile[round(i * 4 + 1)]);
              temp.push_back(colquantile[round(i * 4 + 2)]);
              temp.push_back(colquantile[round(i * 4 + 3)]);
              
              temp.push_back(aveatcg[round(i * 4 + 0)]);
              temp.push_back(aveatcg[round(i * 4 + 1)]);
              temp.push_back(aveatcg[round(i * 4 + 2)]);
              temp.push_back(aveatcg[round(i * 4 + 3)]); 
              
              temp.push_back(avebase[i]);
              //////////////////////////////////////////////             
              out.push_back(temp);        
      }
      readWriteCH rwc;
      rwc.setContent(out);
      rwc.writeCH(outfile);
} 

/*
int main(){
    Intensity it;
    it.readIntensity("testIntensity_before.txt");
    intensityAnalysis ia;
    ia.draw(it, "testIntensity_res.txt");
}
*/

