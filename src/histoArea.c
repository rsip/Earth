/*
NAME:		histoArea.c 
DESCRIPTION: 	Calculates histogram of multi-channel 
                input data file for each region
AUTHOR:	 	Will Grey
VERSION:	2015-11-27	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int histoArea(int argc, char **argv){
 
 metaData p;
 FILE *fin, *fcls;
 int Nbins=100;

 if (argc < 4) histoAreaUsage();	
 
 p.dataType = 1;
 p.channels = 1; 

 fin=openFile("",argv[2],"rb");
 fcls=openFile("",argv[3],"rb");
 if (argc >= 5) p.channels = atoi(argv[4]);
 if (argc >= 6) p.dataType = atoi(argv[5]);
 if (argc == 7) Nbins = atoi(argv[6]);

 p.bpp=dataType2bpp(p.dataType);
	
 getPixels(argv[2], &p);

 if (p.dataType == 1) histoAreaByte (fin,fcls,&p);		
 if (p.dataType == 2) histoAreaShort (fin,fcls,&p,Nbins);	
 if (p.dataType == 3) histoAreaLong (fin,fcls,&p,Nbins); 	
 if (p.dataType == 4) histoAreaFloat (fin,fcls,&p,Nbins);	
 if (p.dataType == 5) histoAreaDouble (fin,fcls,&p,Nbins);		
 
 fclose(fin);
 fclose(fcls);	

 return (EXIT_SUCCESS);
	
}

void histoAreaUsage(){
 fprintf(stderr,"Usage: earth -histoArea inImg inCls [channels] [bytesPerPixel]\n\n");
 fprintf(stderr, "   inImg           Input image                    \n");
 fprintf(stderr, "   inCls           Input classified image         \n");
 fprintf(stderr, "   channels        Number of channels             \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n");
 fprintf(stderr, "   Nbins           Number of bins in histogram \n\n");
 exit(EXIT_FAILURE);
}

int histoAreaByte (FILE *fin, FILE *fcls, metaData *p)
{

 unsigned char *imgcls;
 unsigned char *img;
 unsigned char *cls;
 int i, j, k, n;

 if((img  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();
 if((imgcls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();		
 
 fread(cls, 1, p->pixels, fcls);

 for (j=0;j<p->channels;j++){
  
  fread(img, p->bpp, p->pixels, fin);

  for (k=0;k<NUM_CLASSES;k++){
   n=0;
   for(i=0; i < p->pixels; i++){
    if (*(cls + i)==k){
     *(imgcls + n) = *(img + i);
     n++;
    }
   
    if(n!=0){
     fprintf(stdout,"Channel:   %d\n",j);
     fprintf(stdout,"Class:     %d\n",k);
     histogramByte(imgcls, n);
    }

   }
  }
 }
  
 free(img);
 free(cls);
 free(imgcls);

 return (EXIT_SUCCESS);
}

int histogramByte(unsigned char *img, int n){

 int i, j;
 int histogram[NUM_CLASSES];
 
 for (i=0;i<NUM_CLASSES;i++)
  histogram[i]=0;

 for (j=0;j<n;j++)  
  histogram[*(img +j)]++;

 for (i=0;i<NUM_CLASSES;i++)
  fprintf(stdout, "%d\t %f\n", i, (float)histogram[i]/(float)n);
  
 return (EXIT_SUCCESS);
}

int histoCls (int j, unsigned char *cls, float *img, float *imgcls, metaData *p, int Nbins){

 float min=1e20, max=-1e20; 
 float binSize;
 int i,k,n;
 long histogram[NUM_CLASSES]; 
 

 for (k=0;k<NUM_CLASSES;k++){
   n=0;
   for(i=0; i < p->pixels; i++){
    if (*(cls + i)==k){
     *(imgcls + n) = *(img + i);
     n++;
    }
   }

  if(n!=0){	 
   plotHisto((float *)img,n,&binSize,&min,&max,Nbins,histogram);
   fprintf(stdout,"Class:   %d\n",k);
   printHisto(j,binSize,min,max,Nbins,n,histogram);
  }
 }
 return (EXIT_SUCCESS);

}

int histoAreaFloat (FILE *fin, FILE *fcls, metaData *p, int Nbins){

 float *img, *imgcls;
 int j;
 unsigned char *cls;

 if((img  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();
 if((imgcls  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();  
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, sizeof(unsigned char), p->pixels, fcls);

 for (j=0;j<p->channels;j++){
  fread(img,p->bpp,p->pixels,fin);
  histoCls (j,cls,img,imgcls,p,Nbins);
 }

 free(imgcls);
 free(cls);
 free(img); 
 return (EXIT_SUCCESS);

}

int histoAreaLong (FILE *fin, FILE *fcls, metaData *p, int Nbins){

 long *img, *imgcls;
 int j;
 unsigned char *cls;

 if((img  = (long *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck();
 if((imgcls  = (long *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck();  
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, sizeof(unsigned char), p->pixels, fcls);

 for (j=0;j<p->channels;j++){
  fread(img,p->bpp,p->pixels,fin);
  histoCls (j,cls,(float *)img,(float *)imgcls,p,Nbins);
 }

 free(imgcls);
 free(cls);
 free(img); 
 return (EXIT_SUCCESS);

}

int histoAreaShort (FILE *fin, FILE *fcls, metaData *p, int Nbins){

 short *img, *imgcls;
 int j;
 unsigned char *cls;

 if((img  = (short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck();
 if((imgcls  = (short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck();  
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, sizeof(unsigned char), p->pixels, fcls);

 for (j=0;j<p->channels;j++){
  fread(img,p->bpp,p->pixels,fin);
  histoCls (j,cls,(float *)img,(float *)imgcls,p,Nbins);
 }

 free(imgcls);
 free(cls);
 free(img); 
 return (EXIT_SUCCESS);

}

int histoAreaDouble (FILE *fin, FILE *fcls, metaData *p, int Nbins){

 double *img, *imgcls;
 int j;
 unsigned char *cls;

 if((img  = (double *) calloc(p->pixels,sizeof(double)))== NULL) memoryCheck();
 if((imgcls  = (double *) calloc(p->pixels,sizeof(double)))== NULL) memoryCheck();  
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, sizeof(unsigned char), p->pixels, fcls);

 for (j=0;j<p->channels;j++){
  fread(img,p->bpp,p->pixels,fin);
  histoCls (j,cls,(float *)img,(float *)imgcls,p,Nbins);
 }

 free(imgcls);
 free(cls);
 free(img); 
 return (EXIT_SUCCESS);

}

