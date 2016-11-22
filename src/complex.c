/*
NAME:		complex.c 
DESCRIPTION: 	Convert complex data
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int complex(int argc, char **argv, int (*f)(FILE *, FILE *, FILE *)){
 
 FILE *fcomplex, *freal, *fimag;
 
 if (argc < 5) {
  complexUsage(argv[1]);	
 } 
	
 fcomplex=openFile("",argv[2],"rb");
 freal=openFile("",argv[3],"wb");	
 fimag=openFile("",argv[4],"wb");
	
 f(fcomplex,freal,fimag);
 	
 fclose(fcomplex);
 fclose(freal);
 fclose(fimag);
	
 return (EXIT_SUCCESS);
	
}


int complex2PwrPhase(FILE *fcomplex, FILE *fpwr, FILE *fphase){

 float *complexImg, *pwrImg, *phaseImg;
 int i, remainderPixels;
	
 if((complexImg  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((pwrImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();
 if((phaseImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(complexImg,sizeof(float),PIXELS,fcomplex)) == PIXELS){
  
  for(i = 0; i < PIXELS; i=i+2){
    
   *(pwrImg + i) = atan2(*(complexImg + i+1),*(complexImg + i));
   *(phaseImg + i) = sqrt((*(complexImg + i+1) * *(complexImg + i+1)) 
                    + (*(complexImg + i)* *(complexImg + i)));
  }						
  fwrite(pwrImg, sizeof(float), PIXELS/2, fpwr);
  fwrite(phaseImg, sizeof(float), PIXELS/2, fphase);						
 }

 for(i = 0; i < remainderPixels; i=i+2){
  *(pwrImg + i) = atan2(*(complexImg + i+1),*(complexImg + i));
  *(phaseImg + i) = sqrt((*(complexImg + i+1) * *(complexImg + i+1)) 
                    + (*(complexImg + i)* *(complexImg + i)));
  }					 
 
 fwrite(pwrImg, sizeof(float), remainderPixels/2, fpwr);
 fwrite(phaseImg, sizeof(float), remainderPixels/2, fphase);	
	
 free(pwrImg);
 free(phaseImg);
 free(complexImg);
	
 return (EXIT_SUCCESS);

}


int complex2RealImag(FILE *fcomplex, FILE *freal, FILE *fimag){

 float *complexImg;
 float *realImg;
 float *imagImg;
 int i, remainderPixels;
	
 if((complexImg  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((realImg = (float *) calloc(PIXELS/2,sizeof(float)))== NULL) memoryCheck();
 if((imagImg = (float *) calloc(PIXELS/2,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(complexImg,sizeof(float),PIXELS,fcomplex)) == PIXELS){
  
  for(i = 0; i < PIXELS; i=i+2){
    *(realImg + i) = *(complexImg + i);
    *(imagImg + i) = *(complexImg + i+1);
  }						
  fwrite(realImg, sizeof(float), PIXELS/2, freal);
  fwrite(imagImg, sizeof(float), PIXELS/2, fimag);						
 }

 for(i = 0; i < remainderPixels; i=i+2){
    *(realImg + i) = *(complexImg + i);
    *(imagImg + i) = *(complexImg + i+1);
  }					 
 
 fwrite(realImg, sizeof(float), remainderPixels/2, freal);
 fwrite(imagImg, sizeof(float), remainderPixels/2, fimag);	
	
 free(realImg);
 free(imagImg);
 free(complexImg);
	
 return (EXIT_SUCCESS);

}

void complexUsage(char *tool){
 fprintf(stderr,"Usage: earth %s complexfile realfile imagfile \n\n",tool);
 fprintf(stderr, "   complexfile      input complex image\n");
 fprintf(stderr, "   realfile         output real image\n");
 fprintf(stderr, "   imagfile         output imaginary image\n\n");
 exit(EXIT_FAILURE);
}


