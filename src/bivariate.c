/*
NAME:		bivariate_stats.c 
DESCRIPTION: 	Calculate bivariate stats
AUTHOR:	 	Will Grey
VERSION:	2016-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int bivariate_stats(int argc, char *argv[]){
     
 FILE *fin;
 int pts;
 float *x, *y;
 regressionCoefficients coeffs;

 if(argc != 3) stats_usage("bivariate");
 pts=getNumPts(argv[2]);
 
 if((x = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((y = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 
 fin=openFile("",argv[2],"r");
 
 read_bivariate_data(fin,x,y,pts);
 coeffs=regression(x,y,pts);
 
 fprintf(stdout,"Num_points: %d\n",pts);
 fprintf(stdout,"Gradient: %f\n",coeffs.m);
 fprintf(stdout,"Intercept: %f\n",coeffs.c);
 fprintf(stdout,"Correlation %f\n",correlation(x,y,pts));
 fprintf(stdout,"Covariance %f\n",covariance(x,y,pts));
 fprintf(stdout,"RMSE %f\n",rmse(x,y,pts));
 fprintf(stdout,"bias: %f\n",bias(x,y,pts)); 

 fclose(fin); 
 return (EXIT_SUCCESS);

}


int read_bivariate_data(FILE *ftext, float *x, float *y, int pts){
 
 char buffer[TEXT_LINE_LEN], *p;
 int j;

 for(j=0;j<pts;j++){
  fgets(buffer, TEXT_LINE_LEN, ftext);
  
  p=buffer;
  while(*p==' ' || *p=='\t' || *p=='\r') p++;
  if(*p=='\n') filePtsError(ftext);
    
  sscanf(buffer,"%f %f",&x[j],&y[j]);
 }    	

 return (EXIT_SUCCESS);
}

