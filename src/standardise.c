/*
NAME:		standardise.c 
DESCRIPTION: 	Subtract mean from values and divide by standard deviation
AUTHOR:	 	Will Grey
VERSION:	2015-11-18	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int standardise(int argc, char **argv){
 
 metaData hdrData;
 FILE *fin, *fout;
 struct stat size; 

 hdrData.dataType = 1;
 hdrData.channels = 1;
 hdrData.ignoreValue = 0;
 hdrData.nullValue = 0.0;

 if (argc < 4) anomaliesUsage("-standardise");	

 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
 
 if (argc >= 5) hdrData.dataType = atoi(argv[4]);
 if (argc >= 6) hdrData.channels = atoi(argv[5]);
 if (argc >= 7) hdrData.ignoreValue = atoi(argv[6]);
 if (argc >= 8) hdrData.nullValue = atoi(argv[7]);

 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 hdrData.bpp=dataType2bpp(hdrData.dataType);
 hdrData.pixels = size.st_size / (hdrData.bpp * hdrData.channels);
	
 if (hdrData.dataType == 1) standardiseByte(fin,fout, &hdrData);
 if (hdrData.dataType == 2) standardiseShort(fin,fout, &hdrData);
 if (hdrData.dataType == 3) standardiseLong(fin,fout, &hdrData);
 if (hdrData.dataType == 4) standardiseFloat(fin,fout, &hdrData);
 if (hdrData.dataType == 8) standardiseDouble(fin,fout, &hdrData);
	
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

int standardiseByte(FILE *fin, FILE *fout, metaData *hdrData){

 char *inImg;
 int x, i, n;
 float sum, sumsq, ave, stdev;
 float *outImg;
 
 if((outImg = (float *) calloc(hdrData->pixels,sizeof(float)))== NULL) memoryCheck();
 if((inImg  = (char *) calloc(hdrData->pixels,sizeof(char)))== NULL) memoryCheck();	

 for (i=0;i<hdrData->channels;i++){
  sum=0;
  n=0;
  fread(inImg,sizeof(char),hdrData->pixels,fin);
  
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sum += (float)*(inImg + x);
    n++;
   }
  }						
  ave=sum/(float)n;

  sumsq=0;
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sumsq += ((float)*(inImg + x) - ave) * ((float)*(inImg + x) - ave);
   }
  }
  
  stdev=sqrt(sumsq/n);

  fprintf(stdout, "channel %d mean: %f stdev: %f\n",i+1,ave,stdev);
 
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= ((float)*(inImg + x) - ave) / stdev;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int standardiseShort(FILE *fin, FILE *fout, metaData *hdrData){

 short *inImg;
 int x, i, n;
 float sum, sumsq, ave, stdev;
 float *outImg;
 
 if((outImg = (float *) calloc(hdrData->pixels,sizeof(float)))== NULL) memoryCheck();
 if((inImg  = (short *) calloc(hdrData->pixels,sizeof(short)))== NULL) memoryCheck();	

 for (i=0;i<hdrData->channels;i++){
  sum=0;
  n=0;
  fread(inImg,sizeof(short),hdrData->pixels,fin);
  
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sum += (float)*(inImg + x);
    n++;
   }
  }						
  ave=sum/(float)n;

  sumsq=0;
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sumsq += ((float)*(inImg + x) - ave) * ((float)*(inImg + x) - ave);
   }
  }
  
  stdev=sqrt(sumsq/n);

  fprintf(stdout, "channel %d mean: %f stdev: %f\n",i+1,ave,stdev);
 
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= ((float)*(inImg + x) - ave) / stdev;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int standardiseLong(FILE *fin, FILE *fout, metaData *hdrData){

 long *inImg;
 int x, i, n;
 float sum, sumsq, ave, stdev;
 float *outImg;
 
 if((outImg = (float *) calloc(hdrData->pixels,sizeof(float)))== NULL) memoryCheck();
 if((inImg  = (long *) calloc(hdrData->pixels,sizeof(long)))== NULL) memoryCheck();	

 for (i=0;i<hdrData->channels;i++){
  sum=0;
  n=0;
  fread(inImg,sizeof(long),hdrData->pixels,fin);
  
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sum += (float)*(inImg + x);
    n++;
   }
  }						
  ave=sum/(float)n;

  sumsq=0;
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sumsq += ((float)*(inImg + x) - ave) * ((float)*(inImg + x) - ave);
   }
  }
  
  stdev=sqrt(sumsq/n);

  fprintf(stdout, "channel %d mean: %f stdev: %f\n",i+1,ave,stdev);
 
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= ((float)*(inImg + x) - ave) / stdev;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int standardiseFloat(FILE *fin, FILE *fout, metaData *hdrData){

 float *inImg;
 int x, i, n;
 float sum, sumsq, ave, stdev;
 float *outImg;
 
 if((outImg = (float *) calloc(hdrData->pixels,sizeof(float)))== NULL) memoryCheck();
 if((inImg  = (float *) calloc(hdrData->pixels,sizeof(float)))== NULL) memoryCheck();	

 for (i=0;i<hdrData->channels;i++){
  sum=0;
  n=0;
  fread(inImg,sizeof(float),hdrData->pixels,fin);
  
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sum += (float)*(inImg + x);
    n++;
   }
  }						
  ave=sum/(float)n;

  sumsq=0;
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sumsq += ((float)*(inImg + x) - ave) * ((float)*(inImg + x) - ave);
   }
  }
  
  stdev=sqrt(sumsq/n);

  fprintf(stdout, "channel %d mean: %f stdev: %f\n",i+1,ave,stdev);
 
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= ((float)*(inImg + x) - ave) / stdev;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int standardiseDouble(FILE *fin, FILE *fout, metaData *hdrData){

 double *inImg;
 int x, i, n;
 double sum, sumsq, ave, stdev;
 double  *outImg;
 
 if((outImg = (double *) calloc(hdrData->pixels,sizeof(double)))== NULL) memoryCheck();
 if((inImg  = (double *) calloc(hdrData->pixels,sizeof(double)))== NULL) memoryCheck();	

 for (i=0;i<hdrData->channels;i++){
  sum=0;
  n=0;
  fread(inImg,sizeof(double),hdrData->pixels,fin);
  
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sum += (double)*(inImg + x);
    n++;
   }
  }						
  ave=sum/(double)n;

  sumsq=0;
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    sumsq += (*(inImg + x) - ave) * (*(inImg + x) - ave);
   }
  }
  
  stdev=sqrt(sumsq/n);

  fprintf(stdout, "channel %d mean: %f stdev: %f\n",i+1,ave,stdev);
 
  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= (*(inImg + x) - ave) / stdev;
    n++;
   }
  }
  fwrite(outImg,sizeof(double),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

