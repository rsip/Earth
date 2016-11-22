/*
NAME:		golden.c 
DESCRIPTION: 	1-D minimisation
AUTHOR:	 	Will Grey
VERSION:	2016-11-15	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#include "earth.h"

double goldenFit (double a, double b, float *dist, float *sv, int num, int flag){
 
 double goldenRatio = (sqrt(5)-1)/2;
 int i=0;
 double x1, x2;
 
 x1 = b - goldenRatio * (b - a);
 x2 = a + goldenRatio * (b - a);

 while((fabs(b - a) > ERR_TOL) && (i < MAX_ITERS)){
  
  if (merit_function_golden(&x2,dist,sv,num,flag) > merit_function_golden(&x1,dist,sv,num,flag)){
    b=x2;     
    x2=x1;
    x1 = b - goldenRatio * (b - a);
  }
  else{
    a=x1;
    x1=x2;
    x2 = a + goldenRatio * (b - a); 
  }
   i++;

  }
 
 x2=fabs(b+a)/2;

 fprintf(stdout,"Golden: %f %f %d\n", merit_function_golden(&x2,dist,sv,num,flag), fabs(b+a)/2, i); 
 return fabs(b+a)/2;

}

float merit_function_golden(double *x, float *d, float *sv, int n, int flag){

 float e=0.0;
 int i;

 if (flag==1)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-(*x * d[i]),2);   /* linear model */

 if (flag==2)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-(1.0 - exp((3*d[i]) / *x)),2); /* exponential model */
 
 if (flag==3)
  for (i=0;i<n;i++)
   if (d[i] <=* x)
    e+=pow(sv[i]-(1.5*(d[i]/ *x)-0.5*pow(d[i]/ *x,3)),2); /* spherical model */
 
 if (flag==4)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-(1.0 - exp((3*d[i]*d[i])/(*x* *x))),2); /* gaussian model */
   


 return e;

}


double * fit_variogram_model_golden(float *dist, float *sv, int nbins, int flag){

 double *y;
 int dim=2;
 y = allocateDoubleVector(dim);
 y[1]=goldenFit (-100.0, 100.0,dist,sv,nbins,flag);
 y[0]=0.0; 
 
 return y;
}

