/*
NAME:		anomalies.c 
DESCRIPTION: 	Subtract mean from values
AUTHOR:	 	Will Grey
VERSION:	2015-11-18	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int anomalies(int argc, char **argv){
 
 metaData hdrData;
 FILE *fin, *fout;
 struct stat size; 

 hdrData.dataType = 1;
 hdrData.channels = 1;
 hdrData.ignoreValue = 0;
 hdrData.nullValue = 0.0;

 if (argc < 4) anomaliesUsage("-anomalies");	

 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
 
 if (argc >= 5) hdrData.dataType = atoi(argv[4]);
 if (argc >= 6) hdrData.channels = atoi(argv[5]);
 if (argc >= 7) hdrData.ignoreValue = atoi(argv[6]);
 if (argc >= 8) hdrData.nullValue = atoi(argv[7]);

 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 hdrData.bpp=dataType2bpp(hdrData.dataType);
 hdrData.pixels = size.st_size / (hdrData.bpp * hdrData.channels);
	
 if (hdrData.dataType == 1) anomaliesByte(fin,fout, &hdrData);
 if (hdrData.dataType == 2) anomaliesShort(fin,fout, &hdrData);
 if (hdrData.dataType == 3) anomaliesLong(fin,fout, &hdrData);
 if (hdrData.dataType == 4) anomaliesFloat(fin,fout, &hdrData);
 if (hdrData.dataType == 8) anomaliesDouble(fin,fout, &hdrData);
	
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void anomaliesUsage(char *t){
 fprintf(stderr,"Usage: leaf %s inImg outImg [dataType] [channels] [IgnoreValue] [nullValue]\n\n",t);
 fprintf(stderr, "   inImg            input image\n");
 fprintf(stderr, "   outImg           output image (float)\n");   		
 fprintf(stderr, "   dataType         1: byte (default), 2: short, 3: long, 4: float, 8: Double\n");
 fprintf(stderr, "   channels         1 (default)\n");
 fprintf(stderr, "   IgnoreValues     0: No (default), 1: yes \n");
 fprintf(stderr, "   nullValue        0.0 (default) \n\n");
 exit(EXIT_FAILURE);
}


int anomaliesByte(FILE *fin, FILE *fout, metaData *hdrData){

 char *inImg;
 int x, i, n;
 float sum, ave;
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
  fprintf(stdout, "channel %d mean: %f \n",i+1,ave);

  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= (float)*(inImg + x) - ave;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}


int anomaliesShort(FILE *fin, FILE *fout, metaData *hdrData){

 short *inImg;
 int x, i, n;
 float sum, ave;
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
  fprintf(stdout, "channel %d mean: %f\n",i+1,ave);

  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= (float)*(inImg + x) - ave;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int anomaliesLong(FILE *fin, FILE *fout, metaData *hdrData){

 long *inImg;
 int x, i, n;
 float sum, ave;
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
  fprintf(stdout, "channel %d mean: %f\n",i+1,ave);

  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= (float)*(inImg + x) - ave;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int anomaliesFloat(FILE *fin, FILE *fout, metaData *hdrData){

 float *inImg;
 int x, i, n;
 float sum, ave;
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
  fprintf(stdout, "channel %d mean: %f\n",i+1,ave);

  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= (float)*(inImg + x) - ave;
    n++;
   }
  }
  fwrite(outImg,sizeof(float),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}

int anomaliesDouble(FILE *fin, FILE *fout, metaData *hdrData){

 double *inImg;
 int x, i, n;
 double sum, ave;
 double *outImg;
 
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
  fprintf(stdout, "channel %d mean: %f\n",i+1,ave);

  for(x = 0; x < hdrData->pixels; x++){
   if ((hdrData->ignoreValue == 0) || *(inImg + x) != hdrData->nullValue){
    *(outImg + x)= (double)*(inImg + x) - ave;
    n++;
   }
  }
  fwrite(outImg,sizeof(double),hdrData->pixels,fout);					
 }
			
 free(inImg);
 free(outImg);	
 return (EXIT_SUCCESS);

}





