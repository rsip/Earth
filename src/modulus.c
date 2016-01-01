/*
NAME:		modImg.c 
DESCRIPTION: 	Make all pixels values positive
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int modulus(int argc, char **argv)
{
 
 FILE *fin, *fout;
 metaData hdrData;
 initialiseHdrData(&hdrData);

 hdrData.dataType=1;
  
 if (argc < 4)  modUsage();	
  
 strcpy(hdrData.infile, argv[2]);
 strcpy(hdrData.outfile,argv[3]); 
 if(argc == 5) hdrData.dataType = atoi(argv[4]);
	
 fin=openFile("",hdrData.infile,"rb");
 fout=openFile("",hdrData.outfile,"wb");	
	
 if (hdrData.dataType == 1) modByte(fin,fout);
 if (hdrData.dataType == 2) modShort(fin,fout);
 if (hdrData.dataType == 3) modLong(fin,fout);
 if (hdrData.dataType == 4) modFloat(fin,fout);
 if (hdrData.dataType == 8) modDouble(fin,fout);
	
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void modUsage(){
 fprintf(stderr,"Usage: leaf -modImg infile outfile [dataType] \n\n");
 fprintf(stderr, "   infile          input image 1\n");
 fprintf(stderr, "   outfile         output image\n");	   		
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n\n");
 exit(EXIT_FAILURE);
}

int modByte (FILE *fin, FILE *fout)
{	
 char *inImg; 
 unsigned char *outImg;
 int x, remainderPixels;
	
 if((inImg  = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
  
 for(x = 0; x < PIXELS; x++)
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }						
  fwrite(outImg, sizeof(char), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }
 }
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int modShort (FILE *fin, FILE *fout)
{	
 short *inImg; 
 unsigned short *outImg;
 int x, remainderPixels;
	
 if((inImg  = (short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 if((outImg = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
  
 for(x = 0; x < PIXELS; x++)
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }						
  fwrite(outImg, sizeof(short), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }
 }
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int modLong (FILE *fin, FILE *fout)
{	
 long *inImg; 
 unsigned long *outImg;
 int x, remainderPixels;
	
 if((inImg  = (long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 if((outImg = (unsigned long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
  
 for(x = 0; x < PIXELS; x++)
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }						
  fwrite(outImg, sizeof(long), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }
 }
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int modFloat (FILE *fin, FILE *fout)
{	
 float *inImg; 
 float *outImg;
 int x, remainderPixels;
	
 if((inImg  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
  
 for(x = 0; x < PIXELS; x++)
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1.0;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }						
  fwrite(outImg, sizeof(float), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1.0;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }
 }
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int modDouble (FILE *fin, FILE *fout)
{	
 double *inImg; 
 double *outImg;
 int x, remainderPixels;
	
 if((inImg  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(double),PIXELS,fin)) == PIXELS){
  
 for(x = 0; x < PIXELS; x++)
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1.0;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }						
  fwrite(outImg, sizeof(double), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  if (*(inImg + x) < 0){
    *(outImg + x)  = *(inImg + x) * -1.0;
  }
  else{
   *(outImg + x)  = *(inImg + x);
  }
 }
  
 fwrite(outImg,sizeof(double),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}




	

