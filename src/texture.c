/*
NAME:		meanFilter.c 
DESCRIPTION: 	Apply texture filter
AUTHOR:	 	Will Grey
VERSION:	2015-11-18	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int textureFilter(int argc, char *argv[]){

 int xdim, ydim, winsize, dataType; 
 FILE *fin;
 FILE *fout;
 struct stat size; 
	
 if(argc < 5) textureFiltUsage();
 xdim = atoi(argv[4]);
	
 if(argc >= 6) winsize = atoi(argv[5]);
 else winsize = 3;

 if(argc == 7) dataType = atoi(argv[6]);
 else dataType = 1;
 
	
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim;  
	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
	
 if (dataType == 1) textureByte(fin, fout, xdim, ydim, winsize);
 if (dataType == 2) textureShort(fin, fout, xdim, ydim, winsize);
 if (dataType == 3) textureLong(fin, fout, xdim, ydim, winsize);
 if (dataType == 4) textureFloat(fin, fout, xdim, ydim, winsize);
 if (dataType == 8) textureDouble(fin, fout, xdim, ydim, winsize);
	
 fclose(fin);
 fclose(fout);
 return(EXIT_SUCCESS);		
}


void textureByte(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 unsigned char *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0, mean, sumsq, stdev;
	
 if((inRows  = (unsigned char *)  calloc(winsize * xdim, sizeof(char))) == NULL) memoryCheck();
 if((outRow  = (unsigned char *)  calloc(xdim,           sizeof(char))) == NULL) memoryCheck();
 if((line     = (unsigned char **) calloc(winsize,       sizeof(char))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	 
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(char), xdim, fin); 						
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(char), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(char), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);
   
   mean=sum/(winsize*winsize);

   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 
     sumsq+=pow((float)*(inRows + (i * xdim) + x + j - edge) - mean,2);
   
    stdev = sqrt(sumsq / ((winsize * winsize) -1));

  *(outRow + x) = (unsigned char)stdev;
 }
	
  fwrite(outRow, sizeof(char), xdim, fout);														
						
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }

 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(char), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void textureShort(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 short *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0, mean, sumsq, stdev;
	
 if((inRows  = (short *)  calloc(winsize * xdim, sizeof(short))) == NULL) memoryCheck();
 if((outRow  = (short *)  calloc(xdim,           sizeof(short))) == NULL) memoryCheck();
 if((line     = (short **) calloc(winsize,       sizeof(short))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	 
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(short), xdim, fin); 						
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(short), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(short), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);
   
   mean=sum/(winsize*winsize);

   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 
     sumsq+=pow((float)*(inRows + (i * xdim) + x + j - edge) - mean,2);
   
    stdev = sqrt(sumsq / ((winsize * winsize) -1));

  *(outRow + x) = (short)stdev;
 }
	
  fwrite(outRow, sizeof(short), xdim, fout);														
						
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }

 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(short), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void textureFloat(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 float *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0, mean, sumsq, stdev;
	
 if((inRows  = (float *)  calloc(winsize * xdim, sizeof(float))) == NULL) memoryCheck();
 if((outRow  = (float *)  calloc(xdim,           sizeof(float))) == NULL) memoryCheck();
 if((line     = (float **) calloc(winsize,       sizeof(float))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	 
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(float), xdim, fin); 						
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(float), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(float), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);
   
   mean=sum/(winsize*winsize);

   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 
     sumsq+=pow((float)*(inRows + (i * xdim) + x + j - edge) - mean,2);
   
    stdev = sqrt(sumsq / ((winsize * winsize) -1));

  *(outRow + x) = (float)stdev;
 }
	
  fwrite(outRow, sizeof(float), xdim, fout);														
						
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }

 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(float), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void textureLong(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 long *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0, mean, sumsq, stdev;
	
 if((inRows  = (long *)  calloc(winsize * xdim, sizeof(long))) == NULL) memoryCheck();
 if((outRow  = (long *)  calloc(xdim,           sizeof(long))) == NULL) memoryCheck();
 if((line     = (long **) calloc(winsize,       sizeof(long))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	 
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(long), xdim, fin); 						
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(long), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(long), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);
   
   mean=sum/(winsize*winsize);

   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 
     sumsq+=pow((float)*(inRows + (i * xdim) + x + j - edge) - mean,2);
   
    stdev = sqrt(sumsq / ((winsize * winsize) -1));

  *(outRow + x) = (long)stdev;
 }
	
  fwrite(outRow, sizeof(long), xdim, fout);														
						
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }

 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(long), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void textureDouble(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 double *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 double sum=0, mean, sumsq, stdev;
	
 if((inRows  = (double *)  calloc(winsize * xdim, sizeof(double))) == NULL) memoryCheck();
 if((outRow  = (double *)  calloc(xdim,           sizeof(double))) == NULL) memoryCheck();
 if((line     = (double **) calloc(winsize,       sizeof(double))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	 
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(double), xdim, fin); 						
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(double), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(double), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(double)*(inRows + (i * xdim) + x + j - edge);
   
   mean=sum/(winsize*winsize);

   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 
     sumsq+=pow((double)*(inRows + (i * xdim) + x + j - edge) - mean,2);
   
    stdev = sqrt(sumsq / ((winsize * winsize) -1));

  *(outRow + x) = (double)stdev;
 }
	
  fwrite(outRow, sizeof(double), xdim, fout);														
						
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }

 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(double), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}


int textureFiltUsage(){
 fprintf(stderr,"Usage: earth -texture inImg outImg xdim [winsize] [dataType] \n\n");	 	
 fprintf(stderr, "   inImg            Input image (byte)\n");
 fprintf(stderr, "   outImg           Output image (byte)\n");      
 fprintf(stderr, "   xdim             Number of pixels per row\n"); 
 fprintf(stderr, "   winsize          Window size; odd only Default: 3\n"); 
 fprintf(stderr, "   dataType         1: byte (default); 2: short; 3: long; 4: float; 8: double\n\n"); 
 exit(EXIT_FAILURE);	
}
