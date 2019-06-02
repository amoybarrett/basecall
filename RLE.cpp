/*
 * @kangkang
 */
#include "RLE.h"

using namespace std;

void RLE::getRLE(vector< pair<ll,ll> > &out1){
     out1 = resultPosition;
}

void RLE::setRLE(vector< pair<ll,ll> > &in1){
     resultPosition.clear();
     resultPosition = in1;
}

void RLE::print(){
    cout<<"X"<<"\t"<<"Y"<<endl;
    for(vector< pair<ll,ll> >::iterator it = resultPosition.begin(); it != resultPosition.end(); ++it ){
            cout<<(*it).first<<"\t"<<(*it).second<<endl;
    }
}

void RLE::launch(vector< vector<ll> > &data, const vector<vector<pre> > &data2)
{
    
     //data for flag, data2 for matrix
    resultPosition.clear();

    vector<pair<ll,ll> >  temp;
    
    double sum;
    long area;
    
    bool xh = false;
    
   for(vector< vector<ll> >::iterator itv = data.begin(); itv != data.end(); itv++){
               vector<ll> itvt = *itv;
               for(vector<ll>::iterator itvtit = itvt.begin(); itvtit != itvt.end(); itvtit++){
                   if(!(*itvtit)){
                               xh = true; 
                               break;
                   }
               }
               if(xh){
                   break;    
               }
   }
   if(!xh){
           cout<<"All One Error!"<<endl;
           return ;
   }
 
int stop;   
do{
    stop = 0;
    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = 0; j < data[i].size(); ++j)
        {
            if (data[i][j] == 1)
            {               
               temp.push_back(make_pair(i,j));
               data[i][j] = 2;
               
               sum = data2[i][j];
               area = 1;  
                   
               recursion(i, j, data, temp, data2, sum, area);
                          
               if(area == 1){
                    resultPosition.push_back(make_pair(i,j)); 
                    data[i][j] = 0;    
               }else if(isAllMax(temp, data2, data)){
                     resultPosition.push_back(make_pair(i,j));                  
               }else{
                     double tave = sum / area;
                     for(vector< pair<ll,ll> >::iterator ip= temp.begin(); ip != temp.end(); ++ip){
                           if(data2[(*ip).first][(*ip).second] >= tave){
                               data[(*ip).first][(*ip).second] = 1;
                               stop++;
                           }else{
                               data[(*ip).first][(*ip).second] = 0;
                           }
                     }
               }
               temp.clear();                               
               
            }
        }
    }
   
   
}while(stop != 0);       
            
}

int RLE::recursion(ll i, ll j, vector<vector<ll> > &data, vector<pair<ll,ll> > &position, const vector<vector<pre> > &intensity, double &sum, long &area)
{
    if ( i - 1 >= 0 && j -1 >= 0 && data[i-1][j-1] == 1)
    {
        position.push_back(make_pair(i-1,j-1));
        data[i-1][j-1] = 2;
        sum += intensity[i-1][j-1];
        area ++;
        recursion(i-1,j-1,data,position, intensity, sum, area);
    }
    if (i - 1 >= 0 && data[i-1][j] == 1)
    {
        position.push_back(make_pair(i-1,j));
        data[i-1][j] = 2;
        sum += intensity[i-1][j];
        area ++;
        recursion(i-1,j,data,position, intensity, sum, area);
    }
    if ( j - 1 >= 0 && data[i][j-1] == 1)
    {
        position.push_back(make_pair(i,j-1));
        data[i][j-1] = 2;
        sum += intensity[i][j-1];
        area ++;
        recursion(i,j-1,data,position, intensity, sum, area);
    }
    if ( j - 1 >= 0 && i + 1 < data.size() && data[i+1][j-1] == 1)
    {
        position.push_back(make_pair(i+1,j-1));
        data[i+1][j-1] = 2;
        sum += intensity[i+1][j-1];
        area ++;
        recursion(i+1,j-1,data,position, intensity, sum, area);
    }
    if ( i - 1 >= 0 && j + 1 < data[0].size() && data[i-1][j+1] == 1)
    {
        position.push_back(make_pair(i-1,j+1));
        data[i-1][j+1] = 2;
        sum += intensity[i-1][j+1];
        area ++;
        recursion(i-1,j+1,data,position, intensity, sum, area);
    }
    if ( i + 1 < data.size() && data[i+1][j] == 1)
    {
        position.push_back(make_pair(i+1,j));
        data[i+1][j] = 2;
        sum += intensity[i+1][j];
        area ++;
        recursion(i+1,j,data,position, intensity, sum, area);
    }
    if ( j + 1 < data[0].size() && data[i][j+1] == 1)
    {
        position.push_back(make_pair(i,j+1));
        data[i][j+1] = 2;
        sum += intensity[i][j+1];
        area ++;
        recursion(i,j+1,data,position, intensity, sum, area);
    }
    if ( i + 1 < data.size() && j + 1 < data[0].size() && data[i+1][j+1] == 1)
    {
        position.push_back(make_pair(i+1,j+1));
        data[i+1][j+1] = 2;
        sum += intensity[i+1][j+1];
        area ++;
        recursion(i+1,j+1,data,position, intensity, sum, area);
    }

    return 0;

}


bool RLE::isAllMax(vector<pair<ll,ll> >  &temp, const vector< vector<pre> > &data2, vector<vector<ll> > &data){
                     vector< pair<ll,ll> >::iterator ip= temp.begin();
                     pre td = data2[(*ip).first][(*ip).second];
                     for(ip++ ; ip != temp.end(); ++ip){
                              if(data2[(*ip).first][(*ip).second] != td){
                                  return false;
                              }
                     }   
                     for(vector< pair<ll,ll> >::iterator ip= temp.begin(); ip != temp.end(); ++ip){
                              data[(*ip).first][(*ip).second] = 0;
                     } 
                     return true;
}
