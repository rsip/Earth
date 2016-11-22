/*
NAME:		thresh.c 
DESCRIPTION: 	Apply threshold to image
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int thresh(int argc, char **argv)
{
 
 FILE *fin, *fout;
 double minThresh=0.0, maxThresh=0.0;
 metaData hdrData;
 initialiseHdrData(&hdrData);

 hdrData.dataType=1;

 if (argc < 6) {
  threshUsage();	
 } 

 strcpy(hdrData.infile, argv[2]);
 strcpy(hdrData.outfile,argv[ 3 ]); 
 minThresh = atof(argv[4]);
 maxThresh = atof(argv[5]);
 if(argc == 7) hdrData.dataType = atoi(argv[6]);
	
 fin=openFile("",hdrData.infile,"rb");
 fout=openFile("",hdrData.outfile,"wb");	
	
 if (hdrData.dataType == 1) threshByte(fin,fout,minThresh,maxThresh);
 if (hdrData.dataType == 2) threshShort(fin,fout,minThresh,maxThresh);
 if (hdrData.dataType == 3) threshLong(fin,fout,minThresh,maxThresh);
 if (hdrData.dataType == 4) threshFloat(fin,fout,minThresh,maxThresh);
 if (hdrData.dataType == 8) threshDouble(fin,fout,minThresh,maxThresh);
	
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void threshUsage(){
 fprintf(stderr,"Usage: earth -thresh infile outfile max_thresh min_thresh [data_type] \n\n");
 fprintf(stderr, "   infile          input image 1\n");
 fprintf(stderr, "   outfile          output image\n");
 fprintf(stderr, "   threshold (max)  upper threshold value \n");
 fprintf(stderr, "   threshold (min)  lower threshold value \n");	   		
 fprintf(stderr, "   data_type        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n\n");
 exit(EXIT_FAILURE);
}

int threshByte (FILE *fin, FILE *fout, float threshMax, float threshMin)
{	
 char *inImg; 
 unsigned char *outImg;
 int x, remainderPixels;
	
 if((inImg  = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++){
   *(outImg + x) = 0;
   if (*(inImg + x) >= (char) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (char) threshMin)) *(outImg + x) = 1;

  }
	
  fwrite(outImg, sizeof(char), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  *(outImg + x) = 0;
   if (*(inImg + x) >= (char) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (char) threshMin)) *(outImg + x) = 1;
 }
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int threshShort (FILE *fin, FILE *fout, float threshMax, float threshMin)
{	
 short *inImg; 
 unsigned char *outImg;
 int x, remainderPixels;
	
 if((inImg  = (short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++){
   *(outImg + x) = 0;
   if (*(inImg + x) >= (short) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (short) threshMin)) *(outImg + x) = 1;

  }
	
  fwrite(outImg, sizeof(char), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  *(outImg + x) = 0;
   if (*(inImg + x) >= (short) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (short) threshMin)) *(outImg + x) = 1;
 }
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int threshLong (FILE *fin, FILE *fout, float threshMax, float threshMin)
{	
 long *inImg; 
 unsigned char *outImg;
 int x, remainderPixels;
	
 if((inImg  = (long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++){
   *(outImg + x) = 0;
   if (*(inImg + x) >= (long) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (long) threshMin)) *(outImg + x) = 1;

  }
	
  fwrite(outImg, sizeof(char), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  *(outImg + x) = 0;
   if (*(inImg + x) >= (long) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (long) threshMin)) *(outImg + x) = 1;
 }
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int threshFloat (FILE *fin, FILE *fout, float threshMax, float threshMin)
{	
 float *inImg; 
 unsigned char *outImg;
 int x, remainderPixels;
	
 if((inImg  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++){
   *(outImg + x) = 0;
   if (*(inImg + x) >= threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= threshMin)) *(outImg + x) = 1;

  }
	
  fwrite(outImg, sizeof(char), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  *(outImg + x) = 0;
   if (*(inImg + x) >= threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= threshMin)) *(outImg + x) = 1;
 }
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int threshDouble (FILE *fin, FILE *fout, float threshMax, float threshMin)
{	
 double *inImg; 
 unsigned char *outImg;
 int x, remainderPixels;
	
 if((inImg  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(double),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++){
   *(outImg + x) = 0;
   if (*(inImg + x) >= (double) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (double) threshMin)) *(outImg + x) = 1;

  }
	
  fwrite(outImg, sizeof(char), PIXELS, fout);						
 }

 for (x=0;x<remainderPixels;x++){
  *(outImg + x) = 0;
   if (*(inImg + x) >= (double) threshMax) *(outImg + x) = 1;
   if ((threshMax != threshMin) && (*(inImg + x) <= (double) threshMin)) *(outImg + x) = 1;
 }
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}


	

