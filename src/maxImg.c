/*
NAME:		max.c 
DESCRIPTION: 	Calculate max of seqence of input images
AUTHOR:	 	Will Grey
VERSION:	2015-12-23	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int maxImg(int argc, char **argv){
 
 metaData hdrData;
 FILE **fin, *fout, *ftext;
 int nFiles, file;
 
 hdrData.dataType = 1;
 hdrData.ignoreValue = 1;
 hdrData.nullValue = 0.0;

 if (argc < 4) meanUsage("maxImg");	 

 ftext=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
 
 if (argc >= 5) hdrData.dataType = atoi(argv[4]);
 if (argc >= 6) hdrData.ignoreValue = atoi(argv[5]);
 if (argc >= 7) hdrData.nullValue = atoi(argv[6]);

 if((fin = malloc (sizeof(FILE *) * MAX_NUM_FILES)) == NULL) memoryCheck();

 fin=openMultipleFiles(ftext, &nFiles);

 if (hdrData.dataType == 1) maxImgByte(fin,fout, &hdrData, nFiles);
 if (hdrData.dataType == 2) maxImgShort(fin,fout, &hdrData,nFiles);
 if (hdrData.dataType == 3) maxImgLong(fin,fout, &hdrData, nFiles);
 if (hdrData.dataType == 4) maxImgFloat(fin,fout, &hdrData,nFiles); 
 if (hdrData.dataType == 8) maxImgDouble(fin,fout, &hdrData, nFiles); 
	
 for(file = 0; file < nFiles; file++)
  fclose(fin[file]);
 
 free(fin);
 fclose(fout);
 fclose(ftext);
	
 return (EXIT_SUCCESS);
	
}

int maxImgByte(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 char *inImg[MAX_NUM_FILES], *outImg;
 int x, file, remainderPixels;
 double m=1e-9;
 

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 if((outImg = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(char),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(char),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   m=0;
 
   for(file = 0; file < nFiles; file++) 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
     m = MAXIMUM(m,(double)*(inImg[file] + x));
   	 
   *(outImg + x) = (char)m;
   }						
   fwrite(outImg, sizeof(char), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(char),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  m=0;
  
  for(file = 0; file < nFiles; file++) 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
    m = MAXIMUM(m,(double)*(inImg[file] + x));
    	 
  *(outImg + x) = (char)m;
 }						 
 
 fwrite(outImg,sizeof(char),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int maxImgShort(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 short *inImg[MAX_NUM_FILES], *outImg;
 int x, file, remainderPixels;
 double m=1e-9;
 

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 if((outImg = (short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(short),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(char),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   m=0;
 
   for(file = 0; file < nFiles; file++) 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
     m = MAXIMUM(m,(double)*(inImg[file] + x));
   	 
   *(outImg + x) = (short)m;
   }						
   fwrite(outImg, sizeof(short), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(short),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  m=0;
  
  for(file = 0; file < nFiles; file++) 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
    m = MAXIMUM(m,(double)*(inImg[file] + x));
    	 
  *(outImg + x) = (short)m;
 }						 
 
 fwrite(outImg,sizeof(short),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int maxImgLong(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 long *inImg[MAX_NUM_FILES], *outImg;
 int x, file, remainderPixels;
 double m=1e-9;
 

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 
 if((outImg = (long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(long),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(long),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   m=0;
 
   for(file = 0; file < nFiles; file++) 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
     m = MAXIMUM(m,(double)*(inImg[file] + x));
   	 
   *(outImg + x) = (long)m;
   }						
   fwrite(outImg, sizeof(long), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(long),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  m=0;
  
  for(file = 0; file < nFiles; file++) 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
    m = MAXIMUM(m,(double)*(inImg[file] + x));
    	 
  *(outImg + x) = (long)m;
 }						 
 
 fwrite(outImg,sizeof(long),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int maxImgFloat(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 float *inImg[MAX_NUM_FILES], *outImg;
 int x, file, remainderPixels;
 double m=1e-9;
 

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(float),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(float),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   m=0;
 
   for(file = 0; file < nFiles; file++) 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
     m = MAXIMUM(m,(double)*(inImg[file] + x));
   	 
   *(outImg + x) = (float)m;
   }						
   fwrite(outImg, sizeof(float), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(float),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  m=0;
  
  for(file = 0; file < nFiles; file++) 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
    m = MAXIMUM(m,(double)*(inImg[file] + x));
    	 
  *(outImg + x) = (float)m;
 }						 
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int maxImgDouble(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 double *inImg[MAX_NUM_FILES], *outImg;
 int x, file, remainderPixels;
 double m=1e-9;
 

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(double),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(double),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   m=0;
 
   for(file = 0; file < nFiles; file++) 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
     m = MAXIMUM(m,(double)*(inImg[file] + x));
   	 
   *(outImg + x) = (double)m;
   }						
   fwrite(outImg, sizeof(double), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(double),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  m=0;
  
  for(file = 0; file < nFiles; file++) 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue)
    m = MAXIMUM(m,(double)*(inImg[file] + x));
    	 
  *(outImg + x) = (double)m;
 }						 
 
 fwrite(outImg,sizeof(double),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}



