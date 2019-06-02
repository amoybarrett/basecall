/*
 * @kangkang,æÿ’Û«ÛƒÊ 
 */
#ifndef _INVERSION_H_
#define _INVERSION_H_

class inversion{
public:
       inversion(){}
       ~inversion(){}
public:
 static double** inv(double **A,int n){
 int i,j,k,m=2*n;
 double mik,temp;
 double **a=new double*[n];
 double **B=new double*[n];

 for(i=0;i<n;i++)
 {
  a[i]=new double[2*n];
  B[i]=new double[n];
 }

 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
  {
   if(i==j)
    B[i][j]=1.0;
   else
    B[i][j]=0.0;
  }
 }        

 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
   a[i][j]=A[i][j];  
 for(i=0;i<n;i++)
  for(j=n;j<m;j++)
   a[i][j]=B[i][j-n]; 

 for(k=1;k<=n-1;k++)
 {
  for(i=k+1;i<=n;i++)
  {
   mik=a[i-1][k-1]/a[k-1][k-1];
   for(j=k+1;j<=m;j++)
   {
    a[i-1][j-1]-=mik*a[k-1][j-1];
   }
  }
 }        

 for(i=1;i<=n;i++)
 {
  temp=a[i-1][i-1];
  for(j=1;j<=m;j++)
  {
   a[i-1][j-1]/=temp;
  }
 }      

 for(k=n-1;k>=1;k--)
 {
  for(i=k;i>=1;i--)
  {
   mik=a[i-1][k];
   for(j=k+1;j<=m;j++)
   {
    a[i-1][j-1]-=mik*a[k][j-1];
   }
  }
 }       

 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
   B[i][j]=a[i][j+n]; 

 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
   if(fabs(B[i][j])<0.0001)
    B[i][j]=0.0;

 delete []a;
 return B;               
       }   
};

#endif
