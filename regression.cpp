/*
 * @kangkang
 */
#include "regression.h"
using namespace std;

  void mregression::analysis() 
  { 
	  long i,j,k;
      double e,p,yy,pp;
      b[nn-1][nn-1] = n;
      for (j=0; j<=m-1; j++)
      { 
		  p=0.0;
          for (i=0; i<=n-1; i++) p=p+x[j][i];
          b[m][j]=p;
          b[j][m]=p;
      }
      for (i=0; i<=m-1; i++)
      for (j=i; j<=m-1; j++)
      { 
		  p=0.0;
          for (k=0; k<=n-1; k++)  p=p+x[i][k]*x[j][k];
          b[j][i]=p;
          b[i][j]=p;
      }
      a[m]=0.0;
      for (i=0; i<=n-1; i++) a[m]=a[m]+y[i];
      for (i=0; i<=m-1; i++)
      { 
		  a[i]=0.0;
          for (j=0; j<=n-1; j++)  a[i]=a[i]+x[i][j]*y[j];
      }
      chol();
      yy=0.0;
      for (i=0; i<=n-1; i++)  yy=yy+y[i]/n;
      q=0.0; e=0.0; u=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  p=a[m];
          for (j=0; j<=m-1; j++) p=p+a[j]*x[j][i];
          q=q+(y[i]-p)*(y[i]-p);
          e=e+(y[i]-yy)*(y[i]-yy);
          u=u+(yy-p)*(yy-p);
      }
      s=sqrt(q/n);
      r=sqrt(1.0-q/e);
      for (j=0; j<=m-1; j++)
      { 
		  p=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  pp=a[m];
              for (k=0; k<=m-1; k++)
                  if (k!=j) pp=pp+a[k]*x[k][i];
              p=p+(y[i]-pp)*(y[i]-pp);
          }
          v[j]=sqrt(1.0-q/p);
      }
  }

  void mregression::chol()       
  { 
	  long i,j,k;
      b[0][0]=sqrt(b[0][0]);
      for (j=1; j<=nn-1; j++)  b[0][j]=b[0][j]/b[0][0];
      for (i=1; i<=nn-1; i++)
      { 
          for (j=1; j<=i; j++)
          { 
              b[i][i]=b[i][i]-b[j-1][i]*b[j-1][i];
          }
          b[i][i]=sqrt(b[i][i]);
          if (i!=(nn-1))
          { 
			  for (j=i+1; j<=nn-1; j++)
              { 
                  for (k=1; k<=i; k++)
                      b[i][j]=b[i][j]-b[k-1][i]*b[k-1][j];
                  b[i][j]=b[i][j]/b[i][i];
              }
          }
      } 
      a[0]=a[0]/b[0][0];
      for (i=1; i<=nn-1; i++)
      { 
          for (k=1; k<=i; k++)
              a[i]=a[i]-b[k-1][i]*a[k-1];
          a[i]=a[i]/b[i][i];
      } 
      a[nn-1]=a[nn-1]/b[nn-1][nn-1];
      for (k=nn-1; k>=1; k--)
      { 
          for (i=k; i<=nn-1; i++)
              a[k-1]=a[k-1]-b[k-1][i]*a[i];
          a[k-1]=a[k-1]/b[k-1][k-1];
      }
  }

  double* mregression::output() 
  {
       this->analysis();
       
       
	  for (register int i=0; i<m; i++)
	  {
		  cout <<"a(" <<i <<") = " <<a[i] <<"   ";
	  }
	  cout<<endl;
	  return a;
	  /*
	  cout <<endl;
	  cout <<"偏差平方和 = " <<q <<endl; 
	  cout <<"平均标准偏差 = " <<s <<endl; 
	  cout <<"复相关系数 = " <<r <<endl;   
	  cout <<"回归平方和 = " <<u <<endl;   
	  cout <<"m个自变量的偏相关系数:" <<endl; 
	  for (register int i=0; i<m; i++)
	  {
		  cout <<"v(" <<i <<") = " <<v[i] <<"   ";
	  }
	  cout <<endl;
	  */
  }

