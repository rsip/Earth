/*
NAME:		meanFilter.c 
DESCRIPTION: 	Apply mean filter
AUTHOR:	 	Will Grey
VERSION:	2015-11-18	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int meanFilter(int argc, char *argv[]){

 int xdim, ydim, winsize, dataType; 
 FILE *fin;
 FILE *fout;
 struct stat size; 
	
 if(argc < 5) meanFiltUsage();
 xdim = atoi(argv[4]);
	
 if(argc >= 6) winsize = atoi(argv[5]);
 else winsize = 3;

 if(argc == 7) dataType = atoi(argv[6]);
 else dataType = 1;
 
	
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim;  
	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
	
 if (dataType == 1) meanByte(fin, fout, xdim, ydim, winsize);
 if (dataType == 2) meanShort(fin, fout, xdim, ydim, winsize);
 if (dataType == 3) meanLong(fin, fout, xdim, ydim, winsize);
 if (dataType == 4) meanFloat(fin, fout, xdim, ydim, winsize);
 if (dataType == 8) meanDouble(fin, fout, xdim, ydim, winsize);
	
 fclose(fin);
 fclose(fout);
 return(EXIT_SUCCESS);		
}


void meanByte(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 unsigned char *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0;
	
 if((inRows  = (unsigned char *)  calloc(winsize * xdim, sizeof(char))) == NULL) memoryCheck();
 if((outRow  = (unsigned char *)  calloc(xdim,           sizeof(char))) == NULL) memoryCheck();
 if((line     = (unsigned char **) calloc(winsize,       sizeof(char))) == NULL) memoryCheck();


 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	
 /*  Read in winsize - 1 ydim into inRows  */
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(char), xdim, fin); 						
 /* write zero data to edge ydim */
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(char), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(char), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);

  *(outRow + x) = (unsigned char)rint((double)(sum / (winsize * winsize)));
 }
	
  fwrite(outRow, sizeof(char), xdim, fout);														
/* Switch pointers around */							
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }
/* write zero data to edge ydim */
 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(char), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void meanShort(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 unsigned short *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0;
	
 if((inRows  = (unsigned short *)  calloc(winsize * xdim, sizeof(short))) == NULL) memoryCheck();
 if((outRow  = (unsigned short *)  calloc(xdim,           sizeof(short))) == NULL) memoryCheck();
 if((line     = (unsigned short **) calloc(winsize,       sizeof(short))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	
 /*  Read in winsize - 1 ydim into inRows  */
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(short), xdim, fin); 						
 /* write zero data to edge ydim */
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(short), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(short), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);

  *(outRow + x) = (unsigned short)rint((double)(sum / (winsize * winsize)));
 }
	
  fwrite(outRow, sizeof(short), xdim, fout);														
/* Switch pointers around */							
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }
/* write zero data to edge ydim */
 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(short), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void meanLong(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 unsigned long *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0;
	
 if((inRows  = (unsigned long *)  calloc(winsize * xdim, sizeof(long))) == NULL) memoryCheck();
 if((outRow  = (unsigned long *)  calloc(xdim,           sizeof(long))) == NULL) memoryCheck();
 if((line     = (unsigned long **) calloc(winsize,       sizeof(long))) == NULL) memoryCheck();


 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	
 /*  Read in winsize - 1 ydim into inRows  */
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(long), xdim, fin); 						
 /* write zero data to edge ydim */
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(long), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(long), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=(float)*(inRows + (i * xdim) + x + j - edge);

  *(outRow + x) = (long)rint((double)(sum / (winsize * winsize)));
 }
	
  fwrite(outRow, sizeof(long), xdim, fout);														
/* Switch pointers around */							
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }
/* write zero data to edge ydim */
 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(long), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void meanFloat(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 float *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 float sum=0;
	
 if((inRows  = (float *)  calloc(winsize * xdim, sizeof(float ))) == NULL) memoryCheck();
 if((outRow  = (float  *)  calloc(xdim,           sizeof(float ))) == NULL) memoryCheck();
 if((line     = (float  **) calloc(winsize,       sizeof(float ))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	
 /*  Read in winsize - 1 ydim into inRows  */
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(float ), xdim, fin); 						
 /* write zero data to edge ydim */
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(float ), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(float ), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=*(inRows + (i * xdim) + x + j - edge);

  *(outRow + x) = (float)rint((double)(sum / (winsize * winsize)));
 }
	
  fwrite(outRow, sizeof(float), xdim, fout);														
/* Switch pointers around */							
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }
/* write zero data to edge ydim */
 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(float), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

void meanDouble(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y;
 double *inRows, *outRow, **line, *topLine;
 edge = winsize/2;
 double sum=0;
	
 if((inRows  = (double *)  calloc(winsize * xdim, sizeof(double ))) == NULL) memoryCheck();
 if((outRow  = (double  *)  calloc(xdim,           sizeof(double ))) == NULL) memoryCheck();
 if((line     = (double  **) calloc(winsize,       sizeof(double ))) == NULL) memoryCheck();

 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	
 /*  Read in winsize - 1 ydim into inRows  */
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(double ), xdim, fin); 						
 /* write zero data to edge ydim */
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(double ), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(double ), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   sum=0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     sum+=*(inRows + (i * xdim) + x + j - edge);

  *(outRow + x) = (double)rint((double)(sum / (winsize * winsize)));
 }
	
  fwrite(outRow, sizeof(double), xdim, fout);														
/* Switch pointers around */							
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }
/* write zero data to edge ydim */
 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(double), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}


int meanFiltUsage(){
 fprintf(stderr,"Usage: leaf -meanFlter inImg outImg xdim [winsize] [dataType] \n\n");	 	
 fprintf(stderr, "   inImg            Input image (byte)\n");
 fprintf(stderr, "   outImg           Output image (byte)\n");      
 fprintf(stderr, "   xdim             Number of pixels per row\n"); 
 fprintf(stderr, "   winsize          Window size; odd only Default: 3\n"); 
 fprintf(stderr, "   dataType         1: byte (default); 2: short; 3: long; 4: float; 8: double\n\n"); 
 exit(EXIT_FAILURE);	
}
