/*
NAME:		areaCounter.c 
DESCRIPTION: 	Count pixels in 1/0 binary value byte image
AUTHOR:	 	Will Grey
VERSION:	2015-11-15	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int areaCounter(int argc, char **argv){

 FILE *fin;
 unsigned char *inImg;
 long int total=0, sum=0;
 int i, remainderPixels;
 
 if (argc != 3) areaUsage();

 fin=openFile("",argv[2],"rb");	
		
 if((inImg  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	

 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
  for(i = 0; i < PIXELS; i++){
   total++;
   if (*(inImg + i) == 1) sum++; 
  }						 			
 }

 for(i = 0; i < remainderPixels; i++){
  total++;
  if (*(inImg + i) == 1) sum++;   
 }						 
 
 fprintf(stdout,"NumPixelsVal0: %ld\n", total-sum);
 fprintf(stdout,"NumPixelsVal1: %ld\n", sum);
 fprintf(stdout,"TotalPixels: %ld\n", total);
	
 free(inImg);
 fclose(fin);
 	
 return (EXIT_SUCCESS);
	
}

void areaUsage(){
 fprintf(stderr,"Usage: leaf -areaCounter inImg\n");
 fprintf(stderr, "   inImg           input image (byte)\n\n");
 exit(EXIT_FAILURE);
}

