/*
NAME:		autoregressive.c 
DESCRIPTION: 	Calculates AR coefficients for
                a sequence of images in a time series.
AUTHOR:	 	Will Grey
VERSION:	2015-11-22	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int autoregressive(int argc, char **argv){
 
 metaData hdrData;
 FILE **fin1, **fin2, *fout, *ftext;
 int nFiles, file;
 
 hdrData.ignoreValue = 1;
 hdrData.nullValue = 0.0;
 hdrData.ar = 0;
 
 if (argc < 5) arUsage();	 

 ftext=openFile("",argv[2],"rb");
 fin1=openMultipleFiles(ftext, &nFiles);

 ftext=openFile("",argv[3],"rb");
 fin2=openMultipleFiles(ftext, &nFiles);

 fout=openFile("",argv[4],"wb");	
 
 if (argc >= 6) hdrData.ar = atoi(argv[5]);
 if (argc >= 7) hdrData.ignoreValue = atoi(argv[6]);
 if (argc >= 8) hdrData.nullValue = atoi(argv[7]);

 if((fin1 = malloc (sizeof(FILE *) * MAX_NUM_FILES)) == NULL) memoryCheck();
 if((fin2 = malloc (sizeof(FILE *) * MAX_NUM_FILES)) == NULL) memoryCheck();

 if (hdrData.ar>=nFiles-1){
  fprintf(stderr,"AR shift is greater than length of sequence");
  exit(EXIT_FAILURE);
 }

 autor(fin1, fin2, fout, &hdrData, nFiles); 

 for(file = 0; file < nFiles; file++){
  fclose(fin1[file]);
  fclose(fin2[file]);
 }

 free(fin1);
 free(fin2);
 fclose(fout);
 fclose(ftext);
	
 return (EXIT_SUCCESS);
	
}

void arUsage(){

 fprintf(stderr,"Usage: earth -autoregressive infile1 infile2 outfile [arNum default=0] [dataType] [IgnoreValue] [nullValue]\n\n");
 fprintf(stderr, "   infile1          input textfile of image list 1\n");
 fprintf(stderr, "   infile2          input textfile of image list 2\n");
 fprintf(stderr, "   outfile          output image\n");
 fprintf(stderr, "   arNum            Auto Regression shift \n");   		
 fprintf(stderr, "   IgnoreValues     0: No, 1: yes (default)\n");
 fprintf(stderr, "   nullValue        0.0  \n\n");
 exit(EXIT_FAILURE);

}

int autor(FILE **fin1,  FILE **fin2, FILE *fout, metaData *hdrData, int nFiles){

 float *inImg1[MAX_NUM_FILES], *inImg2[MAX_NUM_FILES];
 float col1[MAX_NUM_FILES], col2[MAX_NUM_FILES];
 float *outImg;
 int x, file, remainderPixels;
 
 for (x=0;x<nFiles;x++){
  if((inImg1[x]  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
  if((inImg2[x]  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();
 }
  
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	


 while ((remainderPixels=fread(inImg1[0],sizeof(float),PIXELS,fin1[0])) == PIXELS){

  for(x = 1; x < nFiles; x++) 
   fread(inImg1[x],sizeof(float),PIXELS,fin1[x]);
  
  for(x = 0; x < nFiles; x++) 
   fread(inImg2[x],sizeof(float),PIXELS,fin2[x]);
  
  for(x = 0; x < PIXELS; x++){ 
   for(file = 0; file < nFiles; file++){
    col1[file]=*(inImg1[file] + x);
    col2[file]=*(inImg2[file] + x);
    } 	 
   *(outImg + x) = correlation (col2+hdrData->ar, col1, nFiles-hdrData->ar);
   }						
   fwrite(outImg, sizeof(float), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++){ 
  fread(inImg1[x],sizeof(float),remainderPixels,fin1[x]);
  fread(inImg2[x],sizeof(float),remainderPixels,fin2[x]);
 }

 for(x = 0; x < remainderPixels; x++){ 
  for(file = 0; file < nFiles; file++){ 
   col1[file]=*(inImg1[file] + x);
   col2[file]=*(inImg2[file] + x);
  } 	 
  *(outImg + x) = correlation (col2+hdrData->ar, col1, nFiles-hdrData->ar);
 }						 
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 for (x=0;x<nFiles;x++){
  free(inImg1[x]);
  free(inImg2[x]);
 }

 free(outImg);
	
 return (EXIT_SUCCESS);

}


