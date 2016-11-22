/*
NAME:		noiseImg.c 
DESCRIPTION: 	Box Muller transform to add Gaussian noise to image
AUTHOR:	 	Will Grey
VERSION:	2015-11-11	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int addNoiseImg(int argc, char **argv){
 
 int dataType=1;
 FILE *fin, *fout;
 double sigma;
 
 if (argc < 5) addNoiseImgUsage();	
  	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");
 sigma = atof(argv[4]);	
 if (argc==6) dataType = atoi(argv[5]);	
	
 if (dataType == 1) addNoiseImgByte(fin,fout, sigma);
 if (dataType == 2) addNoiseImgShort(fin,fout, sigma);
 if (dataType == 3) addNoiseImgLong(fin,fout, sigma);
 if (dataType == 4) addNoiseImgFloat(fin,fout, sigma);
 if (dataType == 8) addNoiseImgDouble(fin,fout, sigma);
	
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void addNoiseImgUsage(){
 fprintf(stderr,"Usage: earth -addNoiseImg inImg outImg sigma [dataType]\n\n");
 fprintf(stderr, "   inImg           input image\n");
 fprintf(stderr, "   outImg          output image\n");
 fprintf(stderr, "   sigma           add standard deviation such that r = sigma * z + mu \n");   		
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n\n");
 
 exit(EXIT_FAILURE);
}

int addNoiseImgFloat(FILE *fin, FILE *fout, double sigma){

 float *inImg;
 float *outImg;
 int x, remainderPixels;
	
 if((inImg  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++)
   *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
   						
  fwrite(outImg, sizeof(float), PIXELS, fout);						
 }

 for(x = 0; x < remainderPixels; x++)
  *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
  						 
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int addNoiseImgByte(FILE *fin, FILE *fout, double sigma){

 char *inImg;
 float *outImg;
 int x, remainderPixels;
	
 if((inImg  = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++)
   *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
   						
  fwrite(outImg, sizeof(float), PIXELS, fout);						
 }

 for(x = 0; x < remainderPixels; x++)
  *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
  						 
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int addNoiseImgShort(FILE *fin, FILE *fout, double sigma){

 short *inImg;
 float *outImg;
 int x, remainderPixels;
	
 if((inImg  = (short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++)
   *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
   						
  fwrite(outImg, sizeof(float), PIXELS, fout);						
 }

 for(x = 0; x < remainderPixels; x++)
  *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
  						 
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int addNoiseImgLong(FILE *fin, FILE *fout, double sigma){

 long *inImg;
 float *outImg;
 int x, remainderPixels;
	
 if((inImg  = (long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++)
   *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
   						
  fwrite(outImg, sizeof(float), PIXELS, fout);						
 }

 for(x = 0; x < remainderPixels; x++)
  *(outImg + x) = (float)generateGaussianNoise((double)*(inImg + x), sigma);
  						 
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int addNoiseImgDouble(FILE *fin, FILE *fout, double sigma){

 double *inImg;
 double *outImg;
 int x, remainderPixels;
	
 if((inImg  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg,sizeof(double),PIXELS,fin)) == PIXELS){
  
  for(x = 0; x < PIXELS; x++)
   *(outImg + x) = generateGaussianNoise((double)*(inImg + x), sigma);
   						
  fwrite(outImg, sizeof(double), PIXELS, fout);						
 }

 for(x = 0; x < remainderPixels; x++)
  *(outImg + x) = generateGaussianNoise((double)*(inImg + x), sigma);
  						 
 fwrite(outImg,sizeof(double),remainderPixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

