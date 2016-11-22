/*
NAME:		simplex.c 
DESCRIPTION: 	Using Nelder Mead for N-dimensional
                ftion mininisation.
AUTHOR:	 	Will Grey
xeRSION:	2015-05-05	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "numerical.h"

#ifdef TEST

double simplex(double (*f)(double[]), double **x, int n)
{
  
  double alpha=1.0, beta=2.0, gamma=0.5, fmin, tol=1.0; 
  int vs, vh, vg, i, j,row, k=0, iters=0;		 
  double *fx, fr, fe, fc, *xr, *xe, *xc, *xm;
  
  fx = allocateDoubleVector(n+1);
  xr = allocateDoubleVector(n);
  xe = allocateDoubleVector(n);  
  xc = allocateDoubleVector(n);
  xm = allocateDoubleVector(n); 
  
  for (j=0;j<=n;j++){ 
   fx[j] = f(x[j]); 
   k++;
  }
  
  fprintf(stdout,"Initial Values\n");
  for (j=0;j<n+1;j++){ 
   for (i=0;i<n;i++) 
    fprintf(stdout,"%f ",x[j][i]);
   fprintf(stdout,"%f\n",fx[j]); 
  }

  while (iters < MAX_ITERS && tol > ERR_TOL) {     
    /* find the index of the largest value */
    vg=0;
    for (j=0;j<=n;j++) 
      if (fx[j] > fx[vg]) 
	vg = j;
      
    /* find the index of the smallest value */
    vs=0;
    for (j=0;j<=n;j++) 
      if (fx[j] < fx[vs]) 
	vs = j;
     
    /* find the index of the second largest value */
    vh=vs;
    for (j=0;j<=n;j++) 
      if (fx[j] > fx[vh] && fx[j] < fx[vg]) 
	vh = j;
     
    /* calculate the centroid */
    for (j=0;j<=n-1;j++) {
      xm[j]=0.0;
      for (i=0;i<=n;i++) {
	if (i!=vg) {
	  xm[j] += x[i][j];
	}
      }
      xm[j] = xm[j]/n;
    }
    
    /* reflection */
    for (i=0;i<n;i++) 
     xr[i] = xm[i] + alpha * (xm[i] - x[vg][i]);
    fr = f(xr);
    k++;
    
    if (fr <= fx[vh] && fr > fx[vs]) {
      for (j=0;j<=n-1;j++) 
	x[vg][j] = xr[j];
      
      fx[vg] = fr;
    }
    
    /* expansion */
    
    if ( fr <=  fx[vs]) {
      for (i=0;i<n;i++)
       xe[i] = xm[i] + beta * (xr[i] - xm[i]);
      fe = f(xe);
      k++;
      

      if (fe < fr) {
	for (j=0;j<=n-1;j++) 
	  x[vg][j] = xe[j];
	
	fx[vg] = fe;
      }
      else {
	for (j=0;j<=n-1;j++) 
	  x[vg][j] = xr[j];
	
	fx[vg] = fr;
      }
    }
    
    /* contraction  */
    if (fr > fx[vh]) {
      for (i=0;i<=n-1;i++) 
       xc[i] = xm[i] + gamma * (x[vg][i] - xm[i]);
      fc = f(xc);
      k++;
      if (fc < fx[vg]) {
	for (j=0;j<=n-1;j++) 
	  x[vg][j] = xc[j];
	
	fx[vg] = fc;
      }
      
      else {
       for (row=0;row<=n;row++) 
        if (row != vs)
         for (j=0;j<=n-1;j++) 
          x[row][j] = x[vs][j]+(x[row][j]-x[vs][j])/2.0;
	   
	fx[vg] = f(x[vg]);
	k++;
	fx[vh] = f(x[vh]);
	k++;
	
      }
    }
    
    fprintf(stdout,"Iteration %d\n",iters);
    for (j=0;j<n+1;j++){ 
     for (i=0;i<n;i++) 
      fprintf(stdout,"%f ",x[j][i]);
     fprintf(stdout,"%f\n",fx[j]); 
    }     

    iters++;
    tol=fabs(fx[vg]-fx[vs]);
  }
  
  vs=0;
  for (i=0;i<=n;i++) 
   if (fx[i] < fx[vs]) 
    vs = i;
  
  fmin=f(x[vs]);   
  fprintf(stdout,"Min\n"); 
  for (i=0;i<n;i++) 
   fprintf(stdout,"%f ",x[vs][i]);
  fprintf(stdout,"%f\n",fmin); 
  
  k++;

  fprintf(stdout,"Function_evaluations: %d\n",k);
  fprintf(stdout,"Iterations: %d\n",iters);
   
  freeDoubleVector(fx); 
  freeDoubleVector(xr); 
  freeDoubleVector(xe);
  freeDoubleVector(xc);
  freeDoubleVector(xm);
 
  return fmin;
}

#endif



double simplex (double (*f)(double *), double **x, int n){
 
 double *xm, *xr, *xe, *xoc, *xic, *fx, tol=1e9, fr, fe, foc;
 double alpha=1, beta=2, gamma=0.5, delta=0.5;
 int i, j, iters=0;
 short int *xpos;

 xpos = allocateShortVector(n+1);
 fx = allocateDoubleVector(n+1);
 xm = allocateDoubleVector(n);
 xr = allocateDoubleVector(n);
 xe = allocateDoubleVector(n);
 xoc = allocateDoubleVector(n);
 xic = allocateDoubleVector(n);
 
 while (iters < MAX_ITERS && tol > ERR_TOL){

 for (i=0;i<n+1;i++){
  fx[i] = f(x[i]);
  xpos[i]=i; 
 }
 
 sortSimplex(fx,n+1,xpos);
 repositionSimplex(xpos, x, n);
 calcCentroid(x,n,xm);
 
 fprintf(stdout,"Iteration %d: \n",iters); 
 for (i=0;i<n+1;i++){
  for (j=0;j<n;j++){  
  fprintf(stdout,"%f ",x[i][j]); 
  }
  fprintf(stdout,"%f\n",fx[i]); 
 }
 

 /* reflection */ 

 for (i=0;i<n;i++)
  xr[i] = xm[i] + alpha * (xm[i] - x[n][i]);
 
 fr=f(xr);

#ifdef TEST
 if(fr<fx[n-1]){
  if (fx[0] < fr){
   for (i=0;i<n;i++) 
    x[n][i]=xr[i];    
  }
  else{
   /* expansion */
   for (i=0;i<n;i++)
    xe[i] = xm[i] + beta * (xr[i] - xm[i]);
   fe=f(xe);

   if(fe<fx[n-1]){
    for (i=0;i<n;i++) 
     x[n][i]=xe[i];
   }
   else{  
    for (i=0;i<n;i++) 
     x[n][i]=xr[i];
   } 
  }
 }

 else{
  /* contraction */
  if (fr < fx[n]){
   for (i=0;i<n;i++) 
    x[n][i]=xr[i];
  }
  for (i=0;i<n;i++)
   xoc[i] = xm[i] + gamma * (x[n][i] - xm[i]);
  foc =f(xoc); 
  
  if (foc < fx[n]){
   for (i=0;i<n;i++) 
    x[n][i]=xoc[i];
  }

  else{
   /* shrink */
   for (j=1;j<n+1;j++) 
    for (i=0;i<n;i++) 
     x[j][i] = x[0][i] + delta * (x[j][i]-x[0][i]);

  }


 }

#endif

  
 if (fx[0] <= fr && fr < fx[n-1]){
   for (i=0;i<n;i++) 
    x[n][i]=xr[i];  
 }

 else if (fr < fx[0]){
  
  /* expansion */
  
  for (i=0;i<n;i++)
   xe[i] = xm[i] + beta * (xr[i] - xm[i]);
  fe=f(xe); 
  
  if (fe < fx[n-1]){
    for (i=0;i<n;i++) 
     x[n][i]=xe[i];
   }

   else{
    for (i=0;i<n;i++) 
     x[n][i]=xr[i];
   } 

 }


 else{
  
  /* outside contraction */
  
  for (i=0;i<n;i++)
   xoc[i] = xm[i] + gamma * (x[n][i] - xm[i]);
  
  foc =f(xoc);

  if (foc <= fr){
   for (i=0;i<n;i++) 
     x[n][i]=xoc[i];
  }

  else{
   /* reduce */ 
   for (j=1;j<n+1;j++) 
    for (i=0;i<n;i++) 
     x[j][i] = x[0][i] + delta * (x[j][i]-x[0][i]);

  }
 
 }

  tol = fabs(fx[0]-fx[n]);
  iters++;

}

 freeShortVector(xpos);  
 freeDoubleVector(xe); 
 freeDoubleVector(xoc); 
 freeDoubleVector(xic);

 return fx[0];
}


int calcCentroid(double **x, int n, double *xm){

 int i,j;
 
 for (j=0;j<n;j++) {
  xm[j]=0.0;
  for (i=0;i<n;i++) 
   xm[j] += x[i][j];
  xm[j] = xm[j]/n;
 }

 return (EXIT_SUCCESS);

}


int repositionSimplex(short int *xpos, double **x, int n){

 int i,j;
 double **xorder;
 xorder = allocateDoubleMatrix(n+1,n);

 for (i=0;i<n+1;i++){
  for (j=0;j<n;j++){  
   xorder[i][j]=x[xpos[i]][j];
  }
 }
 
 for (i=0;i<n+1;i++)
  for (j=0;j<n;j++)
   x[i][j]=xorder[i][j];
 

 freeDoubleMatrix(xorder, n);


 return (EXIT_SUCCESS);
}



int sortSimplex(double *data, int n, short int *xpos)
{

 int i, sorted=0, check=1; 
 double holdValue;
 	
 while( sorted == 0 ){

  check=1;
		
  for (i=1; i < n; i++){
		
   if (data[i] < data[i - 1])	{
		
     holdValue = data[i];
     data[i] = data[i - 1];
     data[i - 1] = holdValue;	
     
     holdValue = xpos[i];
     xpos[i] = xpos[i - 1];
     xpos[i - 1] = holdValue;	
     
     check=0;
    }	
  }
		
   if(check == 1) sorted = 1;
 }
	
 return (EXIT_SUCCESS);

}

