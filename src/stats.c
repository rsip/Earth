/*
NAME:		stats.c 
DESCRIPTION: 	calculates univariate statistics.
AUTHOR:	 	Will Grey
VERSION:	2015-11-26	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int stats(int argc, char **argv){
 
 metaData p;
 FILE *fin;
 
 if (argc < 3)  statsUsage();	
 
 p.dataType = 1;
 p.channels = 1; 

 fin=openFile("",argv[2],"rb");
 if (argc >= 4) p.channels = atoi(argv[3]);
 if (argc == 5) p.dataType = atoi(argv[4]);
 p.bpp=dataType2bpp(p.dataType);
	
 getPixels(argv[2], &p);

 fprintf(stdout,"\nUnivariate Stats\n");
 fprintf(stdout,"n:\t%d\n",p.pixels); 

 if (p.dataType == 1) statsByte (fin,&p);		
 if (p.dataType == 2) statsShort (fin,&p);	
 if (p.dataType == 3) statsLong (fin,&p);	
 if (p.dataType == 4) statsFloat (fin,&p);	
 if (p.dataType == 5) statsDouble (fin,&p);		
 
 fclose(fin);
 	
 return (EXIT_SUCCESS);
	
}

int printStats(univariateStats stats){
 
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

 return (EXIT_SUCCESS);
}


void statsUsage(){
 fprintf(stderr,"Usage: earth -stats inImg [channels] [dataType]\n\n");
 fprintf(stderr, "   inImg           Input image                    \n");
 fprintf(stderr, "   channels        Number of channels             \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n\n");
 exit(EXIT_FAILURE);
}

int statsByte (FILE *fin, metaData *p){

 unsigned char *img; 
 univariateStats stats;
 int i;
 if((img  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(char),p->pixels,fin);
  univStatsByte(img, p->pixels, &stats);
  fprintf(stdout,"\nChannel %d\n",i);
  fprintf(stdout,"Mode:\t%d\n",stats.majority);
  printStats(stats); 
 }

 free(img); 
 return (EXIT_SUCCESS);
}

int statsShort (FILE *fin, metaData *p){

 short *img; 
 univariateStats stats;
 int i;
 if((img  = (short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(short),p->pixels,fin);
  univStats((float *)img, p->pixels, &stats);
  fprintf(stdout,"\nChannel %d\n",i);
  printStats(stats); 
 }

 free(img);
 return (EXIT_SUCCESS);
}

int statsLong (FILE *fin, metaData *p){

 long *img; 
 univariateStats stats;
 int i;
 if((img  = (long *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(long),p->pixels,fin);
  univStats((float *)img, p->pixels, &stats);
  fprintf(stdout,"\nChannel %d\n",i);
  printStats(stats); 
 }

 free(img);
 return (EXIT_SUCCESS);
}

int statsFloat (FILE *fin, metaData *p){

 float *img; 
 univariateStats stats;
 int i;
 if((img  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(float),p->pixels,fin);
  univStats((float *)img, p->pixels, &stats);
  fprintf(stdout,"\nChannel %d\n",i);
  printStats(stats); 
 }

 free(img);
 return (EXIT_SUCCESS);
}

int statsDouble (FILE *fin, metaData *p){

 double *img; 
 univariateStats stats;
 int i;
 if((img  = (double *) calloc(p->pixels,sizeof(double)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(double),p->pixels,fin);
  univStats((float *)img, p->pixels, &stats);
  fprintf(stdout,"\nChannel %d\n",i);
  printStats(stats); 
 }

 free(img);
 return (EXIT_SUCCESS);
}


