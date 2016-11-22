/*
NAME:		diff.c 
DESCRIPTION: 	Calculate the difference between two images
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int diff(int argc, char **argv)
{
 
 FILE *fin1, *fin2, *fout;
 metaData hdrData;
 initialiseHdrData(&hdrData);
 hdrData.dataType=1;

 if (argc < 5) {
  arithmaticUsage("-diff");	
 } 

 strcpy(hdrData.infile, argv[2]);
 strcpy(hdrData.infile2, argv[3]);
 strcpy(hdrData.outfile, argv[4]);
 if(argc == 6) hdrData.dataType = atoi(argv[5]);
	
 fin1=openFile("",hdrData.infile,"rb");
 fin2=openFile("",hdrData.infile2,"rb");
 fout=openFile("",hdrData.outfile,"wb");	

 compareFileSize(argv[2], argv[3]);

 fin1=openFile("",hdrData.infile,"rb");
 fin2=openFile("",hdrData.infile2,"rb");
 fout=openFile("",hdrData.outfile,"wb");	
	
 if (hdrData.dataType == 1) diffByte(fin1,fin2,fout);
 if (hdrData.dataType == 2) diffShort(fin1,fin2,fout);
 if (hdrData.dataType == 3) diffLong(fin1,fin2,fout);
 if (hdrData.dataType == 4) diffFloat(fin1,fin2,fout);
 if (hdrData.dataType == 8) diffDouble(fin1,fin2,fout);
	
 fclose(fin1);
 fclose(fin2);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

int diffByte (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned char *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(char),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) - *(inImg2 + x);
						
  fwrite(outImg, sizeof(char), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) - *(inImg2 + x);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int diffLong(FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned long *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (unsigned long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();
 if((outImg = (unsigned long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(long),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(long), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) - *(inImg2 + x);
						
  fwrite(outImg, sizeof(long),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) - *(inImg2 + x);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}	

int diffShort (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned short *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();
 if((outImg = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(short),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(short), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) - *(inImg2 + x);
						
  fwrite(outImg, sizeof(short),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) - *(inImg2 + x);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int diffFloat (FILE *fin1, FILE *fin2, FILE *fout)
{	
 float *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((inImg2  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(float),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(float), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) - *(inImg2 + x);
						
  fwrite(outImg, sizeof(float),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) - *(inImg2 + x);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}	
	
int diffDouble (FILE *fin1, FILE *fin2, FILE *fout)
{	
 double *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 if((inImg2  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(double),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(double), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) - *(inImg2 + x);
						
  fwrite(outImg, sizeof(double),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) - *(inImg2 + x);
  
 fwrite(outImg,sizeof(double),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}	
		
