/*
NAME:		crossspec.c 
DESCRIPTION: 	Perform cross spectral analysis calculating 
                the phase and coherency of a time series dataset.
AUTHOR:	 	Will Grey
VERSION:	2016-03-06	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

#define INTERVAL_TOLERANCE 0.1
#define COH_95 0.779538

int crosspec(int argc, char **argv){
 
 int n=0, l, i;
 float alpha=0.05;
 float *x[2], *y[2], *re[2], *im[2], *p[2];
 float *coperiod, *quadperiod, *cs, *qs;
 float interval, f;
 float coherency, phaseAng, bang, phaseAngErr, bangerr;
 
 FILE *ftext;
 
 if (argc < 4) usageCross(argv[1]);
 n=getLength(argv[1]);
 
 if (getLength(argv[2]) != n){
  fprintf(stderr,"Time series are different lengths\n");
  exit(EXIT_FAILURE); }

 l=n/2+1;

 fprintf(stdout,"Number_of_n: %d \n",n); 
 fprintf(stdout,"Alpha:       %f \n",alpha);

 ftext  = openFile("",argv[3],  "w"); 
 if (argc == 5) alpha=atof(argv[4]);

 for (i=0;i<2;i++){
   if((x[i]  = (float *) calloc(n, sizeof(float)))== NULL) memoryCheck();
   if((y[i]   = (float *) calloc(n, sizeof(float)))== NULL) memoryCheck();
   if((re[i]  = (float *) calloc(l, sizeof(float)))== NULL) memoryCheck();
   if((im[i]  = (float *) calloc(l, sizeof(float)))== NULL) memoryCheck();
 }

 if((coperiod  = (float *) calloc(l, sizeof(float)))== NULL) memoryCheck();
 if((quadperiod   = (float *) calloc(l, sizeof(float)))== NULL) memoryCheck();

 p[0]=calcspec(x[1],y[1],re[1],im[1],n,argv[1],alpha,&interval);
 p[1]=calcspec(x[2],y[2],re[2],im[2],n,argv[2],alpha,&interval);

 for (i=0;i<n;i++){
  if (x[1][i] != x[0][i]){
   fprintf(stderr,"Time series are for different periods\n");
   exit(EXIT_FAILURE);
  }
 }


 for (i=1;i<=l;i++){
  coperiod[i] = re[0][i] * re[1][i] + im[0][i] * im[1][i];
  quadperiod[i] = im[0][i] * re[1][i] - im[1][i] * im[0][i];
 }

 cs=smoothSpec(coperiod,l);
 qs=smoothSpec(quadperiod,l);

 for (i=1;i<=l;i++){
  f=(1/(n*interval))*i;
  coherency=sqrt(cs[i]*cs[i]+qs[i]*qs[i])/sqrt(p[0][i]*p[1][i]);
  phaseAng=atan2(qs[i],cs[i])*180.0/PI;
  phaseAngErr=(1.96*sqrt(0.238)*sqrt(0.5*((1.0/pow(coherency,2))-1.0))) *180.0/PI;
  bang=(1.0/f)*(phaseAng/360.0);
  bangerr=(1.0/f)*(phaseAngErr/360.0);
 
  fprintf(ftext," %10.5f %9.4f %10.6f %10.6f %10.6f %10.6f %10.6f",f,1.0/f,coherency,phaseAng,phaseAngErr,bang,bangerr);
  
  if (coherency > COH_95)
   fprintf(ftext," (>95%%)\n");
  else
   fprintf(ftext,"\n");
 }

 fclose(ftext);

  for (i=0;i<2;i++){
   free(x[i]);
   free(y[i]);
   free(re[i]);
   free(im[i]);
 }

 free(coperiod);
 free(quadperiod);

 return (EXIT_SUCCESS);

}

float *calcspec(float *x, float *y, float *re, float *im, int n, char *infile, int alpha, float *interval){

 float *p, *pwr;
 regressionCoefficients coeffs;
 int flag; 

 if((pwr   = (float *) calloc((n/2)+2, sizeof(float)))== NULL) memoryCheck();
 
 readData(x,y,infile); 
 flag=checkInterval(x,n,interval);

 if (flag==1){
  fprintf(stderr,"Data are irregularly spaced\n");
  exit(EXIT_FAILURE);
 }
 
 coeffs=regression(x,y,n);
 normalise(x,n);
 detrend(x,y,n,coeffs);
 cosEndTaper(x,y,n,alpha);
 dftPowerReIm(y,pwr,re,im,n);
 p=smoothSpec(pwr,n);
 normaliseSpec(p, (n/2)+1); 

 return p; 

}

int normaliseSpec(float *data, int n){

 int i;
 double sum=0.0;

 for (i=1;i<=n;i++)
  sum+=data[i];

 for (i=1;i<=n;i++)
  data[i]=data[i]/sum;

 return(EXIT_SUCCESS);

}


void usageCross(char *tool){

 fprintf(stderr,"\nUsage: earth %s infile1 infile2 outfile alpha\n\n", tool);
 fprintf(stderr, "   infile1        Input file 1\n"); 
 fprintf(stderr, "   infile2        Input file 2\n"); 	   
 fprintf(stderr, "   outfile        Output file\n");
 fprintf(stderr, "   alpha          Parameter required for cosine taper (default=0.05)\n\n");
 exit(EXIT_FAILURE);

}

int normalise(float *data, int n){

 int i;
 double sum=0.0, stdev=0.0, ave=0.0;

 for (i=0;i<n;i++)
  sum+=data[i];

 ave=(sum/n);

 sum=0.0;
 for (i=0;i<n;i++)
  sum+=pow(data[i]-ave,2);

 stdev=sqrt(sum/n);

 for (i=0;i<n;i++)
  data[i]=(data[i]-ave)/stdev;

 return(EXIT_SUCCESS);

}

int dftPowerReIm(float *data, float *pwr, float *re, float *im, int n){

 int i, k, l;
 
 pwr[0]=0.0;
 l=(n/2)+1;


 for (i=1;i<=l;i++){
  re[k]=0.0;
  im[k]=0.0;

  for (k=0;k<n;k++){
   re[k]+=data[k]*cos(2*PI*k*i/n);
   im[k]+=data[k]*sin(2*PI*k*i/n);
  }

  pwr[i] = re[i] * re[i] + im[i] * im[i];

 }
 
 return (EXIT_SUCCESS);

}



