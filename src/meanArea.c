/*
NAME:		meanArea.c 
DESCRIPTION: 	calculates the statistics with regions.
AUTHOR:	 	Will Grey
VERSION:	2015-11-25	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int meanArea(int argc, char **argv){
 
 metaData p;
 FILE *fin, *fcls;
 
 if (argc < 4) meanAreaUsage();	
 
 p.dataType = 1;
 p.channels = 1; 

 fin=openFile("",argv[2],"rb");
 fcls=openFile("",argv[3],"rb");
 if (argc >= 5) p.channels = atoi(argv[4]);
 if (argc == 6) p.dataType = atoi(argv[5]);
 p.bpp=dataType2bpp(p.dataType);
	
 getPixels(argv[2], &p);

 if (p.dataType == 1) meanAreaByte (fin,fcls,&p);		
 if (p.dataType == 2) meanAreaShort (fin,fcls,&p);	
 if (p.dataType == 3) meanAreaLong (fin,fcls,&p);	
 if (p.dataType == 4) meanAreaFloat (fin,fcls,&p);	
 if (p.dataType == 5) meanAreaDouble (fin,fcls,&p);		
 
 fclose(fin);
 fclose(fcls);	

 return (EXIT_SUCCESS);
	
}

void meanAreaUsage(){
 fprintf(stderr,"Usage: earth -meanArea inImg inCls [channels] [bytesPerPixel]\n\n");
 fprintf(stderr, "   inImg           Input image                    \n");
 fprintf(stderr, "   inCls           Input classified image         \n");
 fprintf(stderr, "   channels        Number of channels             \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n\n");
 exit(EXIT_FAILURE);
}

int meanAreaShort (FILE *fin, FILE *fcls, metaData *p)
{

 short *img;
 unsigned char *cls;
 int i, j;
 double sum[NUM_CLASSES], mean[NUM_CLASSES]; 
 int num[NUM_CLASSES];
 short min[NUM_CLASSES], max[NUM_CLASSES];

 if((img  = (short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck();	
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, 1, p->pixels, fcls);

 for(i=0;i<NUM_CLASSES;i++){
  num[i]=0;
  sum[i]=0;
  mean[i]=0;
  min[i]=3e4;
  max[i]=-3e4;
 }

 for (j=0;j<p->channels;j++){
  
  fread(img, p->bpp, p->pixels, fin);
  for(i=0; i < p->pixels; i++){
   if (*(img + i) < min[j]) min[j] = *(img + i);
   if (*(img + i) > max[j]) max[j] = *(img + i);
   sum[*(cls + i)] += (double)*(img + i);
   num[*(cls + i)]++;
  }
 
  for(i=0;i<NUM_CLASSES;i++){
   mean[i]=sum[i]/(double)num[i];
   sum[i]=0.0;
  }
  
  for(i=0; i < p->pixels; i++){
   sum[*(cls + i)] += pow(*(img + i) - mean[*(cls + i)],2);
  
  }
  
  fprintf(stdout,"\n channel %d\n",j);
  for(i=1;i<NUM_CLASSES;i++)
   if (num[i]!=0)
    fprintf(stdout,"%d\t%d\t%f\t%f\t%d\t%d\n",i,num[i],mean[i],sqrt(sum[i]/(double)num[i]),min[i],max[i]);

 }

 return (EXIT_SUCCESS);
}

int meanAreaLong (FILE *fin, FILE *fcls, metaData *p)
{

 long *img;
 unsigned char *cls;
 int i, j;
 double sum[NUM_CLASSES], mean[NUM_CLASSES]; 
 int num[NUM_CLASSES];
 long min[NUM_CLASSES], max[NUM_CLASSES];;

 if((img  = (long *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck();	
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, 1, p->pixels, fcls);

 for(i=0;i<NUM_CLASSES;i++){
  num[i]=0;
  sum[i]=0;
  mean[i]=0;
  min[i]=3e8;
  max[i]=-3e8;
 }

 for (j=0;j<p->channels;j++){
  
  fread(img, p->bpp, p->pixels, fin);
  for(i=0; i < p->pixels; i++){
   if (*(img + i) < min[j]) min[j] = *(img + i);
   if (*(img + i) > max[j]) max[j] = *(img + i);
   sum[*(cls + i)] += (double)*(img + i);
   num[*(cls + i)]++;
  }
 
  for(i=0;i<NUM_CLASSES;i++){
   mean[i]=sum[i]/(double)num[i];
   sum[i]=0.0;
  }
  
  for(i=0; i < p->pixels; i++){
   sum[*(cls + i)] += pow(*(img + i) - mean[*(cls + i)],2);
  
  }
  
  fprintf(stdout,"\n channel %d\n",j);
  for(i=1;i<NUM_CLASSES;i++)
   if (num[i]!=0)
    fprintf(stdout,"%d\t%d\t%f\t%f\t%ld\t%ld\n",i,num[i],mean[i],sqrt(sum[i]/(double)num[i]),min[i],max[i]);

 }

 return (EXIT_SUCCESS);
}

int meanAreaFloat (FILE *fin, FILE *fcls, metaData *p)
{

 float *img;
 unsigned char *cls;
 int i, j;
 double sum[NUM_CLASSES], mean[NUM_CLASSES]; 
 int num[NUM_CLASSES];
 float min[NUM_CLASSES], max[NUM_CLASSES];;

 if((img  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, 1, p->pixels, fcls);

 for(i=0;i<NUM_CLASSES;i++){
  num[i]=0;
  sum[i]=0;
  mean[i]=0;
  min[i]=3e8;
  max[i]=-3e8;
 }

 for (j=0;j<p->channels;j++){
  
  fread(img, p->bpp, p->pixels, fin);
  for(i=0; i < p->pixels; i++){
   if (*(img + i) < min[j]) min[j] = *(img + i);
   if (*(img + i) > max[j]) max[j] = *(img + i);
   sum[*(cls + i)] += (double)*(img + i);
   num[*(cls + i)]++;
  }
 
  for(i=0;i<NUM_CLASSES;i++){
   mean[i]=sum[i]/(double)num[i];
   sum[i]=0.0;
  }
  
  for(i=0; i < p->pixels; i++){
   sum[*(cls + i)] += pow(*(img + i) - mean[*(cls + i)],2);
  
  }
  
  fprintf(stdout,"\n channel %d\n",j);
  for(i=1;i<NUM_CLASSES;i++)
   if (num[i]!=0)
    fprintf(stdout,"%d\t%d\t%f\t%f\t%f\t%f\n",i,num[i],mean[i],sqrt(sum[i]/(double)num[i]),min[i],max[i]);

 }

 return (EXIT_SUCCESS);
}

int meanAreaDouble (FILE *fin, FILE *fcls, metaData *p)
{

 double *img;
 unsigned char *cls;
 int i, j;
 double sum[NUM_CLASSES], mean[NUM_CLASSES]; 
 int num[NUM_CLASSES];
 double min[NUM_CLASSES], max[NUM_CLASSES];

 if((img  = (double *) calloc(p->pixels,sizeof(double)))== NULL) memoryCheck();	
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, 1, p->pixels, fcls);

 for(i=0;i<NUM_CLASSES;i++){
  num[i]=0;
  sum[i]=0;
  mean[i]=0;
  min[i]=3e8;
  max[i]=-3e8;
 }

 for (j=0;j<p->channels;j++){
  
  fread(img, p->bpp, p->pixels, fin);
  for(i=0; i < p->pixels; i++){
   if (*(img + i) < min[j]) min[j] = *(img + i);
   if (*(img + i) > max[j]) max[j] = *(img + i);
   sum[*(cls + i)] += (double)*(img + i);
   num[*(cls + i)]++;
  }
 
  for(i=0;i<NUM_CLASSES;i++){
   mean[i]=sum[i]/(double)num[i];
   sum[i]=0.0;
  }
  
  for(i=0; i < p->pixels; i++){
   sum[*(cls + i)] += pow(*(img + i) - mean[*(cls + i)],2);
  
  }
  
  fprintf(stdout,"\n channel %d\n",j);
  for(i=1;i<NUM_CLASSES;i++)
   if (num[i]!=0)
    fprintf(stdout,"%d\t%d\t%f\t%f\t%f\t%f\n",i,num[i],mean[i],sqrt(sum[i]/(double)num[i]),min[i],max[i]);

 }

 return (EXIT_SUCCESS);
}

int meanAreaByte (FILE *fin, FILE *fcls, metaData *p)
{

 unsigned char *img;
 unsigned char *cls;
 int i, j;
 double sum[NUM_CLASSES], mean[NUM_CLASSES]; 
 int num[NUM_CLASSES];
 unsigned char min[NUM_CLASSES], max[NUM_CLASSES];

 if((img  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 if((cls  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 fread(cls, 1, p->pixels, fcls);

 for(i=0;i<NUM_CLASSES;i++){
  num[i]=0;
  sum[i]=0;
  mean[i]=0;
  min[i]=255;
  max[i]=0;
 }

 for (j=0;j<p->channels;j++){
  
  fread(img, p->bpp, p->pixels, fin);
  for(i=0; i < p->pixels; i++){
   if (*(img + i) < min[j]) min[j] = *(img + i);
   if (*(img + i) > max[j]) max[j] = *(img + i);
   sum[*(cls + i)] += (double)*(img + i);
   num[*(cls + i)]++;
  }
 
  for(i=0;i<NUM_CLASSES;i++){
   mean[i]=sum[i]/(double)num[i];
   sum[i]=0.0;
  }
  
  for(i=0; i < p->pixels; i++){
   sum[*(cls + i)] += pow(*(img + i) - mean[*(cls + i)],2);
  
  }
  
  fprintf(stdout,"\n channel %d\n",j);
  for(i=1;i<NUM_CLASSES;i++)
   if (num[i]!=0)
    fprintf(stdout,"%d\t%d\t%f\t%f\t%d\t%d\n",i,num[i],mean[i],sqrt(sum[i]/(double)num[i]),min[i],max[i]);

 }

 return (EXIT_SUCCESS);
}


