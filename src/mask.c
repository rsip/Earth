/*
NAME:		mask.c 
DESCRIPTION: 	Apply mask to image
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int mask(int argc, char **argv)
{
 
 FILE *fin1, *fin2, *fout;
 metaData hdrData;
 initialiseHdrData(&hdrData);
 hdrData.dataType=1;


 if (argc < 5) {
  maskUsage();	
 } 

 strcpy(hdrData.infile, argv[2]);
 strcpy(hdrData.infile2, argv[3]);
 strcpy(hdrData.outfile, argv[4]);

 if(argc == 6) hdrData.dataType = atoi(argv[5]);
	
 fin1=openFile("",hdrData.infile,"rb");
 fin2=openFile("",hdrData.infile2,"rb");
 fout=openFile("",hdrData.outfile,"wb");	
	
 if (hdrData.dataType == 1) maskByte(fin1,fin2,fout);
 if (hdrData.dataType == 2) maskShort(fin1,fin2,fout);
 if (hdrData.dataType == 3) maskLong(fin1,fin2,fout);
 if (hdrData.dataType == 4) maskFloat(fin1,fin2,fout);
 if (hdrData.dataType == 8) maskDouble(fin1,fin2,fout);
	
 fclose(fin1);
 fclose(fin2);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void maskUsage(){
 fprintf(stderr,"Usage: earth -mask infile maskfile (Byte) outfile [data_type] \n\n");
 fprintf(stderr, "   infile           input image\n");
 fprintf(stderr, "   mask file        mask image\n");
 fprintf(stderr, "   outfile          output image\n");	   		
 fprintf(stderr, "   data_type        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n\n");
 exit(EXIT_FAILURE);
}

int maskByte (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned char *inImg, *outImg;
 unsigned char *maskImg;
 int x, remainderPixels;
	
 if((inImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();		
 if((maskImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin1)) == PIXELS){
  fread(maskImg, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg + x) * *(maskImg + x);
						
  fwrite(outImg, sizeof(char), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x) = *(inImg + x) * *(maskImg + x);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg);
 free(maskImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int maskShort (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned short *inImg, *outImg;
 unsigned char *maskImg;
 int x, remainderPixels;
	
 if((inImg  = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();
 if((outImg = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();		
 if((maskImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin1)) == PIXELS){
  fread(maskImg, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg + x) * (short)*(maskImg + x);
						
  fwrite(outImg, sizeof(short), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x) = *(inImg + x) * (short)*(maskImg + x);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
	
 free(inImg);
 free(maskImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int maskLong (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned long *inImg, *outImg;
 unsigned char *maskImg;
 int x, remainderPixels;
	
 if((inImg  = (unsigned long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();
 if((outImg = (unsigned long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();		
 if((maskImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin1)) == PIXELS){
  fread(maskImg, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg + x) * (long)*(maskImg + x);
						
  fwrite(outImg, sizeof(long), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x) = *(inImg + x) * (long)*(maskImg + x);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
	
 free(inImg);
 free(maskImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int maskFloat (FILE *fin1, FILE *fin2, FILE *fout)
{	
 float *inImg, *outImg;
 unsigned char *maskImg;
 int x, remainderPixels;
	
 if((inImg  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();		
 if((maskImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin1)) == PIXELS){
  fread(maskImg, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg + x) * (float)*(maskImg + x);
						
  fwrite(outImg, sizeof(float), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x) = *(inImg + x) * (float)*(maskImg + x);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg);
 free(maskImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int maskDouble (FILE *fin1, FILE *fin2, FILE *fout)
{	
 double *inImg, *outImg;
 unsigned char *maskImg;
 int x, remainderPixels;
	
 if((inImg  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();		
 if((maskImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(double),PIXELS,fin1)) == PIXELS){
  fread(maskImg, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg + x) * (double)*(maskImg + x);
						
  fwrite(outImg, sizeof(double), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x) = *(inImg + x) * (double)*(maskImg + x);
  
 fwrite(outImg,sizeof(double),remainderPixels,fout);
	
 free(inImg);
 free(maskImg);
 free(outImg);
	
 return (EXIT_SUCCESS);
}
		
