/*
NAME:		bivariate_stats.c 
DESCRIPTION: 	Calculate bivariate stats
AUTHOR:	 	Will Grey
VERSION:	2016-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int univariate(int argc, char *argv[]){
     
 FILE *fin;
 int n;
 float *a;
 univariateStats stats;

 if(argc != 3) stats_usage("univariate");
 n=getNumPts(argv[2]);

 if((a = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck(); 
 fin=openFile("",argv[2],"r");
 read_univariate_data(fin,a,n);
 
 univStats(a, n, &stats);
 
 fprintf(stdout,"\nUnivariate Stats\n");
 fprintf(stdout,"n:\t%d\n",n); 
 fprintf(stdout,"Mean:\t%f\n",stats.ave);
 fprintf(stdout,"Median:\t%f\n",stats.median);
 
 fprintf(stdout,"Max:\t%f\n",stats.max); 
 fprintf(stdout,"Min:\t%f\n",stats.min); 

 fprintf(stdout,"Stdev:\t%f\n",stats.stdDev);
 fprintf(stdout,"Variance:\t%f\n",stats.variance); 
 fprintf(stdout,"Skew:\t%f\n",stats.skewness); 
 fprintf(stdout,"Kurt:\t%f\n",stats.kurtosis);
 fprintf(stdout,"Range:\t%f\n",stats.range); 
 
 fprintf(stdout,"UpperQuartile:\t%f\n",stats.upperQuartile); 
 fprintf(stdout,"LowerQuartile:\t%f\n",stats.lowerQuartile);
 fprintf(stdout,"InterQuartieRange:\t%f\n",stats.interQuartileRange); 

 fprintf(stdout,"BestEstimateOfStDev:\t%f\n",stats.bestEstimateOfStDev);
 fprintf(stdout,"StandardErrorOfStDev:\t%f\n",stats.StandardErrorOfStDev);
 fprintf(stdout,"StandardErrorOfMean:\t%f\n",stats.StandardErrorOfMean);

 fclose(fin); 
 return (EXIT_SUCCESS);

}


int histText(int argc, char **argv){
 
 FILE *fin;
 int n;
 float *a;
 int nbins=100;
 float min=1e20, max=-1e20; 
 float binSize;
 long *histogram;
 
 if(argc < 3) hist_stats_usage("histText");
 n=getNumPts(argv[2]);
 if (argc == 4) nbins=atoi(argv[3]);

 if((histogram = (long *) calloc(nbins, sizeof(long))) == NULL) memoryCheck(); 
 if((a = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck(); 
 
 fin=openFile("",argv[2],"r");
 read_univariate_data(fin,a,n);
 
 plotHisto(a,n,&binSize,&min,&max,nbins,histogram);
 printHisto(-1,binSize,min,max,nbins,n,histogram); 
 
 fclose(fin);
 	
 return (EXIT_SUCCESS);
	
}

int read_univariate_data(FILE *ftext, float *x, int pts){
 
 char buffer[TEXT_LINE_LEN], *p;
 int j;

 for(j=0;j<pts;j++){
  fgets(buffer, TEXT_LINE_LEN, ftext);
  
  p=buffer;
  while(*p==' ' || *p=='\t' || *p=='\r') p++;
  if(*p=='\n') filePtsError(ftext);
    
  sscanf(buffer,"%f",&x[j]);
 }    	

 return (EXIT_SUCCESS);
}

void hist_stats_usage(char *s){

 fprintf(stderr,"Usage: earth -%s pointFile Nbins\n",s);	
 fprintf(stderr, "    pointFile:       x file\n");
 fprintf(stderr, "    NBins:           Number fo bins\n");
 exit(EXIT_FAILURE);

}

void stats_usage(char *s){

 fprintf(stderr,"Usage: earth -%s pointFile\n",s);	
 fprintf(stderr, "    pointFile:       x file\n");
 exit(EXIT_FAILURE);

}

