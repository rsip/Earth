/*
NAME:		histogram.c 
DESCRIPTION: 	Calculates histogram of multi-channel input data file.
AUTHOR:	 	Will Grey
VERSION:	2015-11-26	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int hist(int argc, char **argv){
 
 metaData p;
 FILE *fin;
 int Nbins=100;
 
 if (argc < 3) histogramUsage();	
 
 p.dataType = 1;
 p.channels = 1; 

 fin=openFile("",argv[2],"rb");
 if (argc >= 4) p.channels = atoi(argv[3]);
 if (argc >= 5) p.dataType = atoi(argv[4]);
 if (argc == 6) Nbins = atoi(argv[5]);
 p.bpp=dataType2bpp(p.dataType);
	
 getPixels(argv[2], &p);

 fprintf(stdout,"\nHistogram\n");
 fprintf(stdout,"n:\t%d\n",p.pixels); 

 if (p.dataType == 1) histoByte (fin,&p);		
 if (p.dataType == 2) histoShort (fin,&p,Nbins);	
 if (p.dataType == 3) histoLong (fin,&p,Nbins);	
 if (p.dataType == 4) histoFloat (fin,&p,Nbins);	
 if (p.dataType == 5) histoDouble (fin,&p,Nbins);		
 
 fclose(fin);
 	
 return (EXIT_SUCCESS);
	
}

void histogramUsage(){
 fprintf(stderr,"Usage: leaf -hist inImg [channels] [dataType] [Nbins]\n\n");
 fprintf(stderr, "   inImg           Input image                    \n");
 fprintf(stderr, "   channels        Number of channels             \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n");
 fprintf(stderr, "   Nbins           Number of bins in histogram \n\n");
 exit(EXIT_FAILURE);
}

int histoByte (FILE *fin, metaData *p){

 unsigned char *img; 
 int i, j;
 int histogram[NUM_CLASSES][MAX_NUM_CHANNELS];
 if((img  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck(); 

 for (i=0;i<NUM_CLASSES;i++)
  for (j=0;j<MAX_NUM_CHANNELS;j++)
   histogram[i][j]=0;

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(char),p->pixels,fin);
  for (j=0;j<p->pixels;i++)  
   histogram[*(img +j)][i]++;  
 }

 for (i=0;i<NUM_CLASSES;i++){
  fprintf(stdout, "%d\t", i);
  for (j=0;j<p->channels;j++)
   fprintf(stdout, "%f\t", (float)histogram[i][j]/(float)p->pixels);
  fprintf(stdout, "\n");
 }

 free(img); 
 return (EXIT_SUCCESS);
}

int printHisto(int i, float binSize, float min, float max, int Nbins, int n, long *histogram){

 int j;
 fprintf(stdout,"Channel:   %d\n",i);
 fprintf(stdout,"BinSize:   %f\n",binSize);
 fprintf(stdout,"Min:       %f\n",min);
 fprintf(stdout,"Max:       %f\n",max);
 fprintf(stdout,"Nbins:     %d\n",Nbins);
	
 for (j=0;j<Nbins;j++)
  fprintf(stdout, "%f\n", (float)histogram[j]/(float)n);
 fprintf(stdout, "\n\n");
 
 return (EXIT_SUCCESS);
}

int plotHisto(float *img, int n, float *binSize, float *min, float *max, int Nbins, long *histogram){

 int j;
 int bin;
 
 for (j=0;j<NUM_CLASSES;j++)
  histogram[j]=0;

 for (j=0;j<n;j++){  
  if (*(img + j) > *max) *max = *(img + j);
  if (*(img + j) < *min) *min = *(img + j);
 }
  
 *binSize = (*max - *min) / (float)Nbins;

 for (j=0;j<n;j++){
  bin=(*(img+j)-*min) / *binSize;
  histogram[bin]++;
 }

 return (EXIT_SUCCESS);
}

int histoFloat (FILE *fin, metaData *p, int Nbins){

 float *img;
 float min=1e20, max=-1e20; 
 float binSize;
 int i;
 long histogram[NUM_CLASSES]; 

 if((img  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(float),p->pixels,fin);	 
  plotHisto((float *)img,p->pixels,&binSize,&min,&max,Nbins,histogram);
  printHisto(i,binSize,min,max,Nbins,p->pixels,histogram); 
 }

 free(img); 
 return (EXIT_SUCCESS);

}

int histoDouble(FILE *fin, metaData *p, int Nbins){

 double *img;
 float min=1e20, max=-1e20; 
 float binSize;
 int i;
 long histogram[NUM_CLASSES]; 

 if((img  = (double *) calloc(p->pixels,sizeof(double)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(double),p->pixels,fin);	 
  plotHisto((float *)img,p->pixels,&binSize,&min,&max,Nbins,histogram);
  printHisto(i,binSize,(float)min,(float)max,Nbins,p->pixels,histogram); 
 }

 free(img); 
 return (EXIT_SUCCESS);

}

int histoShort(FILE *fin, metaData *p, int Nbins){

 short *img;
 float min=32768.0, max=-32768.0; 
 float binSize;
 int i;
 long histogram[NUM_CLASSES]; 

 if((img  = (short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(short),p->pixels,fin);	
  plotHisto((float *)img,p->pixels,&binSize,&min,&max,Nbins,histogram);
  printHisto(i,binSize,(float)min,(float)max,Nbins,p->pixels,histogram);
 }

 free(img); 
 return (EXIT_SUCCESS);

}

int histoLong(FILE *fin, metaData *p, int Nbins){

 long *img;
 float min=2e9, max=-2e9; 
 float binSize;
 int i;
 long histogram[NUM_CLASSES]; 

 if((img  = (long  *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck(); 

 for (i=0;i<p->channels;i++){ 
  fread(img,sizeof(long),p->pixels,fin);	 
  plotHisto((float *)img,p->pixels,&binSize,&min,&max,Nbins,histogram);
  printHisto(i,binSize,min,max,Nbins,p->pixels,histogram);
 }

 free(img); 
 return (EXIT_SUCCESS);

}

