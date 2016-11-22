/*
NAME:		tsspec.c 
DESCRIPTION: 	Perform time series analysis on single col data
AUTHOR:	 	Will Grey
VERSION:	2016-04-19	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

#define INTERVAL_TOLERANCE 0.1

int tsspec(int argc, char **argv){
 
 int samples=0, i, flag;
 float alpha=0.05;
 float *x, *y, interval, *pwr, *p, f;
 regressionCoefficients coeffs; 
 FILE *ftext;
 
 if (argc < 4) usageTsa(argv[1]);
 samples=getLength(argv[2]); 
 ftext  = openFile("",argv[3],  "w"); 
 if (argc == 5) alpha=atof(argv[4]);

 if((x  = (float *) calloc(samples, sizeof(float)))== NULL) memoryCheck();
 if((y   = (float *) calloc(samples, sizeof(float)))== NULL) memoryCheck();
 if((pwr   = (float *) calloc((samples/2)+2, sizeof(float)))== NULL) memoryCheck();

 readData(x,y,argv[1]); 
 flag=checkInterval(x,samples,&interval);

 if (flag==1){
  fprintf(stderr,"Data are irregularly spaced\n");
  exit(EXIT_FAILURE);
 }
 
 coeffs=regression(x,y,samples);
 detrend(x,y,samples,coeffs);

 fprintf(stdout,"Number_of_samples: %d \n",samples); 
 fprintf(stdout,"Detrend_slope:     %f \n",coeffs.m); 
 fprintf(stdout,"Detrend_intercept: %f \n",coeffs.c);
 fprintf(stdout,"Interval:          %f \n",interval);
 fprintf(stdout,"Alpha:             %f \n",alpha);

 cosEndTaper(x, y,samples,alpha);
 dftPower(y,pwr,samples);

 p=smoothSpec(pwr,samples);

 fprintf(ftext,"Frequency\tPeriod\tPower\n");

 for (i=1;i<(samples/2)+1;i++){
  f=(1/(samples*interval))*i;
  fprintf(ftext," %10.5f %9.4f %10.6f\n",f,1.0/f,p[i]);
 } 
 
 fclose(ftext);
 free(pwr);
 free(y);
 free(x);

 return (EXIT_SUCCESS);

}

int dftPower(float *data, float *pwr, int n){

 int i, k;
 float re, im;

 pwr[0]=0.0;

 for (i=1;i<=(n/2)+1;i++){
  re=0.0;
  im=0.0;

  for (k=0;k<n;k++){
   re+=data[k]*cos(2*PI*k*i/n);
   im+=data[k]*sin(2*PI*k*i/n);
  }

  pwr[i] = re * re + im * im;

 }
 
 return (EXIT_SUCCESS);

}

float *smoothSpec(float *p, int n)
{

 int k, i;
 float *psmth;
 float ep[]={0.5,0.5};
 float pts[]={0.25,0.5,0.25};
 double tot=0.0;

 if((psmth  = (float *) calloc((n/2)+2, sizeof(float)))== NULL) memoryCheck();

 psmth[0]=0.0;

 for (k=0;k<=2;k++){
  psmth[0]=p[0];
  psmth[1]=ep[0]*p[1]+ep[1]*p[2];
  psmth[(n/2)]=ep[0]*p[(n/2)-1]+ep[1]*p[(n/2)];

 for (i=2;i<n/2;i++)
  psmth[i] = pts[0] * p[i-1] + pts[1] * p[i] + pts[2] * p[i+1];

 for (i=0;i<=(n/2);i++)
  p[i]=psmth[i];
  
 } 
 
 for (i=1;i<=(n/2);i++)
  tot=tot+psmth[i];
 for (i=1;i<=(n/2);i++)
  psmth[i] = psmth[i]/tot;
 
 return psmth;

}


void usageTsa(char *tool){

 fprintf(stderr,"\nUsage: earth %s infile outfile alpha\n\n", tool);
 fprintf(stderr, "   infile        Input file\n"); 	   
 fprintf(stderr, "   outfile       Output file\n");
 fprintf(stderr, "   alpha         Parameter required for cosine taper (default=0.05)\n\n");
 exit(EXIT_FAILURE);

}

int cosEndTaper(float *x, float *y, int n, float alpha){

 int i;
 double xp; 

 for(i=0; i<n; i++){
  xp=(fabs(x[n-1]-x[i]) + (fabs(x[n-1]-x[0])/(10.0*n)))/fabs(x[n-1]-x[0]);
  if(xp<=alpha)y[i]=y[i]*(0.5-0.5*cos(PI*xp/alpha));
  if(xp>=1.0-alpha)y[i]=y[i]*(0.5-0.5*cos(PI*(1.0-xp)/alpha));
 }

 return(EXIT_SUCCESS);

}





int checkInterval(float *x, int samples, float *diff)
{

 /* check whether data are irregularly 
    or regularly spaced */

 float diff2,tol;
 int i, flag=0;
 float sumDiff=0.0;

 *diff=x[1]-x[0];
 tol=INTERVAL_TOLERANCE * *diff;

 for (i=1;i<samples;i++){
  diff2=x[i]-x[i-1];
  sumDiff=sumDiff+diff2;
  
   if ((diff2 < *diff-tol) && (diff2 > *diff+tol)){ 
    flag=1;
    break;
   }
  
  }

  *diff=sumDiff/((float)samples-1);

  return flag;
}




int readData(float *ts, float *x, char *infile)
{
 
 FILE *ftext;
 ftext  = openFile("",infile,  "r"); 
 char *buffer, *p;
 int rows=0, cols;
 
 if((buffer  = (char *) calloc(MAX_LINE_LEN, sizeof(char)))== NULL) memoryCheck();

 while(fgets(buffer, MAX_LINE_LEN, ftext) !=NULL){
  
  if (buffer[0] != '\n'){ 
   cols=0;
   p = strtok(buffer," \t");
   
   while (p!=NULL || cols<=1){
    if (cols==0) ts[rows]=atof(p);
    if (cols==1) x[rows]= atof(p);
    p = strtok (NULL, "  \t");
    cols++; 
   } 
   rows++;
  }    
 
 } 
 
 free(buffer);
 fclose(ftext);
 
 return (EXIT_SUCCESS);
 	 
}		

int detrend(float *xData, float *yData, int n, regressionCoefficients coeffs)
{
	
 int i;

 for(i=0; i<n; i++){
   yData[i] = yData[i] - (coeffs.m * xData[i]) - coeffs.c;
 }

 return (EXIT_SUCCESS);

}

int getLength(char *infile){

 int row=0;
 char *buffer, *p;
 FILE *ftext;

 ftext  = openFile("",infile,  "r"); 
 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext)!=NULL){
  
  p=buffer;
  while(*p==' ' || *p=='\t' || *p=='\r') p++;
  if(*p!='\n') row++;

 } 
   
 free(buffer);
 fclose(ftext);
 return row;

}

#ifdef TEST

regressionCoefficients regression1(float *xData, float *yData, int n){
	
 regressionCoefficients coeffs;
 int i;
 double SumX=0,SumY=0,SumX2=0,SumXY=0;

 for(i=0; i<n; i++){
															
  SumX += (double)xData[i];
  SumY += (double)yData[i];
  SumX2 += ((double)xData[i] * (double)xData[i]);
  SumXY += ((double)xData[i] * (double)yData[i]); 
 
 }
 
 coeffs.m = ((n*SumXY)-(SumY*SumX)) / ((n*SumX2)-(SumX*SumX));
 coeffs.c = (SumY - (coeffs.m * SumX)) / n;

 return coeffs;

}

int hanningTaper(float *data, int n)
{

 int i;

 for(i=0; i<n; i++)
  data[i] *= 0.5 * ( 1.0 - cos((2 * PI * i) /(n -1)));
 
 return(EXIT_SUCCESS);

}

int cosTaper(float *data, int n, float a){

 int i;
 
 for(i=0; i<n; i++){

  if (i<=((a*(n-1))/2))  
    data[i] *= 0.5 * (1.0 + cos( PI *  (((2.0*i)/(a*(n-1))-1.0))));

  if (i>=(n-1)*(1-(a/2))) 
   data[i] *= 0.5 * (1.0 + cos( PI * ( ((2*i)/(a*(n-1))-(2/a)-1.0)))); 
 
 }
return(EXIT_SUCCESS);

}
#endif

