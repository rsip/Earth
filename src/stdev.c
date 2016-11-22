/*
NAME:		stdev.c 
DESCRIPTION: 	Calculate standard deviation of seqence of input images
AUTHOR:	 	Will Grey
VERSION:	2015-11-11	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int stdv(int argc, char **argv){
 
 metaData hdrData;
 FILE **fin, *fout, *ftext;
 int nFiles, file;
 
 hdrData.dataType = 1;
 hdrData.ignoreValue = 1;
 hdrData.nullValue = 0.0;

 if (argc < 4) stdevUsage();	 

 ftext=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
 
 if (argc >= 5) hdrData.dataType = atoi(argv[4]);
 if (argc >= 6) hdrData.ignoreValue = atoi(argv[5]);
 if (argc >= 7) hdrData.nullValue = atoi(argv[6]);

 if((fin = malloc (sizeof(FILE *) * MAX_NUM_FILES)) == NULL) memoryCheck();

 fin=openMultipleFiles(ftext, &nFiles);

 if (hdrData.dataType == 1) stdevImgByte(fin,fout, &hdrData, nFiles);
 if (hdrData.dataType == 2) stdevImgShort(fin,fout, &hdrData,nFiles);
 if (hdrData.dataType == 3) stdevImgLong(fin,fout, &hdrData, nFiles);
 if (hdrData.dataType == 4) stdevImgFloat(fin,fout, &hdrData,nFiles); 
 if (hdrData.dataType == 8) stdevImgDouble(fin,fout, &hdrData, nFiles); 
	
 for(file = 0; file < nFiles; file++)
  fclose(fin[file]);
 
 free(fin);
 fclose(fout);
 fclose(ftext);
	
 return (EXIT_SUCCESS);
	
}

void stdevUsage(){
 fprintf(stderr,"Usage: earth -stdev infile outfile [dataType] [IgnoreValue] [nullValue]\n\n");
 fprintf(stderr, "   infile           input textfile of image list\n");
 fprintf(stderr, "   outfile          output image 2\n");   		
 fprintf(stderr, "   dataType         1: byte (default), 2: short, 3: long, 4: float, 8: Double\n");
 fprintf(stderr, "   IgnoreValues     0: No, 1: yes (default)\n");
 fprintf(stderr, "   nullValue        0.0  \n\n");
 exit(EXIT_FAILURE);
}

int stdevImgByte(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 char *inImg[MAX_NUM_FILES];
 float *outImg, mean, stdev;
 int x, file, remainderPixels;
 float sum=0;
 int n=0;

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(char),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(char),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   sum=0;
   n=0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     sum += *(inImg[file] + x);
      n++;
    }
   }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;

   }						
   fwrite(outImg, sizeof(float), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(char),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  sum=0;
  n=0;
 
  for(file = 0; file < nFiles; file++){ 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
    sum += *(inImg[file] + x);
    n++;
   }
  }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
 }						 
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int stdevImgShort(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 short *inImg[MAX_NUM_FILES];
 float *outImg, mean, stdev;
 int x, file, remainderPixels;
 float sum=0;
 int n=0;

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(short),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(short),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   sum=0;
   n=0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     sum += *(inImg[file] + x);
      n++;
    }
   }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
   }						
   fwrite(outImg, sizeof(float), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(short),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  sum=0;
  n=0;
 
  for(file = 0; file < nFiles; file++){ 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
    sum += *(inImg[file] + x);
    n++;
   }
  }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
 }						 
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int stdevImgLong(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 long *inImg[MAX_NUM_FILES];
 float *outImg, mean, stdev;
 int x, file, remainderPixels;
 float sum=0;
 int n=0;

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (long *) calloc(PIXELS,sizeof(long)))== NULL) memoryCheck();	
 
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(long),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(long),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   sum=0;
   n=0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     sum += *(inImg[file] + x);
      n++;
    }
   }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
   }						
   fwrite(outImg, sizeof(float), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(long),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  sum=0;
  n=0;
 
  for(file = 0; file < nFiles; file++){ 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
    sum += *(inImg[file] + x);
    n++;
   }
  }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
 }						 
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int stdevImgFloat(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 float *inImg[MAX_NUM_FILES];
 float *outImg, mean, stdev;
 int x, file, remainderPixels;
 float sum=0;
 int n=0;

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(float),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(float),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   sum=0;
   n=0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     sum += *(inImg[file] + x);
      n++;
    }
   }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
   }						
   fwrite(outImg, sizeof(float), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(float),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  sum=0;
  n=0;
 
  for(file = 0; file < nFiles; file++){ 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
    sum += *(inImg[file] + x);
    n++;
   }
  }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
 }						 
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int stdevImgDouble(FILE **fin, FILE *fout, metaData *hdrData, int nFiles){

 double *inImg[MAX_NUM_FILES];
 double *outImg, mean, stdev;
 int x, file, remainderPixels;
 double sum=0;
 int n=0;

 for (x=0;x<nFiles;x++)
  if((inImg[x]  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg[0],sizeof(double),PIXELS,fin[0])) == PIXELS){
 
  for(x = 1; x < nFiles; x++) 
   fread(inImg[x],sizeof(double),PIXELS,fin[x]);

  for(x = 0; x < PIXELS; x++){ 
   sum=0;
   n=0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     sum += *(inImg[file] + x);
      n++;
    }
   }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
   }						
   fwrite(outImg, sizeof(double), PIXELS, fout);						
 }
 
 for(x = 0; x < nFiles; x++) 
  fread(inImg[x],sizeof(double),remainderPixels,fin[x]);

 for(x = 0; x < remainderPixels; x++){ 
  sum=0;
  n=0;
 
  for(file = 0; file < nFiles; file++){ 
   if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
    sum += *(inImg[file] + x);
    n++;
   }
  }	 
   mean = (float)sum / (float)n;
   stdev=0.0;
   for(file = 0; file < nFiles; file++){ 
    if ((hdrData->ignoreValue == 0) || *(inImg[file] + x) != hdrData->nullValue){
     stdev += pow(*(inImg[file] + x)-mean,2);     
    }
   }
   
   *(outImg + x)=sqrt(stdev/n)/mean;
 }						 
 
 fwrite(outImg,sizeof(double),remainderPixels,fout);

 for (x=0;x<nFiles;x++)	
  free(inImg[x]);
 
 free(outImg);
	
 return (EXIT_SUCCESS);

}
