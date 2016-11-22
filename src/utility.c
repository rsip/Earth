
/*
NAME:		utility.c 
DESCRIPTION: 	Utility tools for memory management,
                reading and writing to files and other
                housekeping.
AUTHOR:	 	Will Grey
VERSION:	2015-05-05	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int diagnosticTest(metaData *p){

 fprintf(stdout," %d\n", p->xdim);
 fprintf(stdout," %d\n", p->ydim);
 fprintf(stdout," %d\n", p->channels);
 return (EXIT_SUCCESS);

}

int getYdim2(char *filename, metaData *param){
 
 struct stat size;
 if (stat(filename, &size) == -1) fileReadError(filename);
 param->ydim2 = size.st_size / (param->xdim2 * param->bpp * param->channels);

 return (EXIT_SUCCESS);
}

int getYdim(char *filename, metaData *param){
 
 struct stat size;
 if (stat(filename, &size) == -1) fileReadError(filename);
 param->ydim = size.st_size / (param->xdim * param->bpp * param->channels);

 return (EXIT_SUCCESS);
}

int getPixels(char *filename, metaData *param){
 
 struct stat size;
 if (stat(filename, &size) == -1) fileReadError(filename);
 param->pixels = size.st_size / (param->bpp * param->channels);

 return (EXIT_SUCCESS);
}

int dataType2bpp(int datatype){
 
 int bpp;

 switch (datatype){
 case 1:
  bpp=1;  
  break;
 case 2:
  bpp=2;  
  break; 
 case 3:
  bpp=2;  
  break;  
 case 4:
  bpp=4; 
  break;
 case 8:
  bpp=8;  
  break; 
 default:
  break;
 } 
 return bpp;
}

char * itoa(int num){

 int size;
 char *x;
 
 size = log10(num) + 1;
 x = malloc(size);
 sprintf(x, "%d", num);
 return x;

}

int compareFileSize(char *img1, char *img2)
{
 struct stat size1, size2;
 if (stat(img1, &size1) == -1) fileReadError(img1);
 if (stat(img2, &size2) == -1) fileReadError(img2);
 if (size1.st_size != size2.st_size) fileSizeErr(img1,img2); 
 return(EXIT_SUCCESS);
}

int fileSizeErr(char *img1, char *img2)
{
 fprintf(stderr,"\nFiles %s and %s differ in size\n\n",img1, img2);
 exit(EXIT_FAILURE);
}

int fileReadError(char *img)
{
 fprintf(stderr,"\nCannot access file: %s\n\n",img);
 exit(EXIT_FAILURE);
}

int checkFileExists(char *f) {
 struct stat s;
 return stat(f, &s) == 0;
}

FILE *openFile(char *path, char *fileName, char *rw)
{
 
 FILE *fp;
 char fullPathName[MAX_PATH_NAME_LENGTH];
 
 strcpy(fullPathName,path);
 strcat(fullPathName,fileName); 
 
 
 if ( !strcmp(rw, "rb") ){
 
  fp = fopen(fullPathName, "rb");
  if ( fp == NULL ){
   fprintf( stderr, "Error opening file %s\n", fullPathName);
   exit(EXIT_FAILURE); 
  }
  
 }
 
 if ( !strcmp(rw, "wb") ){
 
  fp = fopen(fullPathName, "wb");
  if ( fp == NULL ){
   fprintf( stderr, "Error creating %s\n", fullPathName);
   exit(EXIT_FAILURE); 
  }
 
 }
 
 if ( !strcmp(rw, "r") ){
 
  fp = fopen(fullPathName, "r");
  if ( fp == NULL ){
   fprintf( stderr, "Error opening file %s\n", fullPathName);
   exit(EXIT_FAILURE); 
  }
  
 }
 
 
 if ( !strcmp(rw, "r++") ){
 
  fp = fopen(fullPathName, "r++");
  if ( fp == NULL ){
   fprintf( stderr, "Error opening file %s\n", fullPathName);
   exit(EXIT_FAILURE); 
  }
  
 }

 if ( !strcmp(rw, "w") ){
 
  fp = fopen(fullPathName, "w");
  if ( fp == NULL ){
   fprintf( stderr, "Error creating %s\n", fullPathName);
   exit(EXIT_FAILURE); 
  }
 
 }

 if ( !strcmp(rw, "a") ){
 
  fp = fopen(fullPathName, "a");
  if ( fp == NULL ){
   fprintf( stderr, "Error creating %s\n", fullPathName);
   exit(EXIT_FAILURE); 
  }
 
 }

 return fp;

}

float *readFloatData(char *pathName, char *fileName, int n)
{
 
 FILE *fp;
 float *data;

 fp=openFile(pathName, fileName, "rb");
 
 if((data = (float *) calloc(n,sizeof(float)))==NULL) memoryCheck();  
 fread(data, sizeof(float), n, fp);
 
 fclose(fp);
 
 return data;

} 

short *readShortData(char *pathName, char *fileName, int n)
{
 
 FILE *fp;
 short *data;

 fp=openFile(pathName, fileName, "rb");
 
 if((data = (short*) calloc(n,sizeof(short)))==NULL) memoryCheck();  
 fread(data, sizeof(short), n, fp);
 
 fclose(fp);
 
 return data;

} 

long *readLongData(char *pathName, char *fileName, int n)
{
 
 FILE *fp;
 long *data;

 fp=openFile(pathName, fileName, "rb");
 
 if((data = (long *) calloc(n,sizeof(long)))==NULL) memoryCheck();  
 fread(data, sizeof(long), n, fp);
 
 fclose(fp);
 
 return data;

} 

unsigned char *readByteData(char *pathName, char *fileName, int n)
{
 
 FILE *fp;
 unsigned char *data;

 fp=openFile(pathName, fileName, "rb");
 
 if((data = (unsigned char *) calloc(n,sizeof(unsigned char)))==NULL) memoryCheck();  
 fread(data, sizeof(unsigned char), n, fp);
 
 fclose(fp);
 
 return data;

} 




int memoryCheck(void)	
{	
 fprintf(stderr,"\nUnable to allocate memory.\n\n");
 exit(EXIT_FAILURE);
}

int createEnviHeader(char *pathName, char *fileName, metaData *hdrFile){
 
 FILE *fp;
 fp=openFile(pathName, fileName, "w");
 
 fprintf(fp,"ENVI\n");
 fprintf(fp,"samples   = %d\n", hdrFile->xdim);
 fprintf(fp,"lines     = %d\n", hdrFile->ydim);
 fprintf(fp,"bands     = %d\n", hdrFile->channels);
 fprintf(fp,"data type = %d\n", hdrFile->dataType);
 fprintf(fp,"byte order = %d\n", hdrFile->byteOrder);
 
 fclose(fp);
 
 return 0;

}

int readEnviHeader(char *pathName, char *headerFile, metaData *hdrFile){

 FILE *f;
 f = fopen (headerFile, "r");
 char line[ENVI_HEADER_LINE_LEN];
 char *token;
 int i;

 while(fgets(line, ENVI_HEADER_LINE_LEN, f) != NULL){

  token = strtok(line," ");

  if (!strcasecmp(token, "samples")) {
   for (i=0;i<2;i++)
    token = strtok(NULL," ");
   hdrFile->xdim=atoi(token);    }

  else if (!strcasecmp(token, "lines")) {
   for (i=0;i<2;i++)
    token = strtok(NULL," ");
   hdrFile->ydim=atoi(token); }

  else if (!strcasecmp(token, "bands")) {
   for (i=0;i<2;i++)
    token = strtok(NULL," ");
   hdrFile->channels=atoi(token);  }

  else if (!strcasecmp(token, "data")) {
   for (i=0;i<3;i++)
    token = strtok(NULL," ");
   hdrFile->dataType=atoi(token);

   switch (hdrFile->dataType){
    case 1:
     hdrFile->bpp=1;
    case 2:
     hdrFile->bpp=2;
    case 3:
     hdrFile->bpp=4;
    case 4:
     hdrFile->bpp=4;
    case 8:
     hdrFile->bpp=8;
   }
  }

  else if (!strcasecmp(token, "byte")) {
   for (i=0;i<3;i++)
    token = strtok(NULL," ");
   hdrFile->byteOrder=atoi(token);  }  

 } 

 return (EXIT_SUCCESS);
}


int counter(unsigned int element, unsigned int nElements)

/* In code use something like:
 if (element % nElements == 0) counter (element,nElements);
*/

{
 unsigned int percentage;
	
 percentage = (element*100)/nElements;
 fprintf(stderr,"\rprocessing line: %d (%3d%% completed)",element, percentage);
 fflush(NULL);
		
 if(percentage == 100){
  fprintf(stderr,"\n"); 
  fflush(NULL);
 }	
	
 return(EXIT_SUCCESS);	 

}

double timer()
{
/* in code write:
 double startTime=timer();
at start of program

At end of program write:
 double endTime=timer();
 fprintf(stderr," %s: Runtime %f seconds\n", argv[0], endTime-startTime);
*/

 struct timeval tv;
 struct timezone tz;
 double walltime;

  gettimeofday(&tv, &tz);
  walltime = tv.tv_sec +tv.tv_usec*1.0e-6;

  return(walltime);
}

float * convertByte2Float(unsigned char *dataIn, int n){

 int i;
 float *dataOut;

 if((dataOut  = (float *) calloc(n, sizeof(float)))== NULL) memoryCheck();

 for (i=0;i<n;i++)
   *(dataOut +i) = (float)*(dataIn +i); 

 return dataOut;

}

float * convertDouble2Float(double *dataIn, int n){

 int i;
 float *dataOut;

 if((dataOut  = (float *) calloc(n, sizeof(float)))== NULL) memoryCheck();

 for (i=0;i<n;i++)
   *(dataOut +i) = (float)*(dataIn +i); 

 return dataOut;

}

float * convertLong2Float(unsigned long int *dataIn, int n){

 int i;
 float *dataOut;

 if((dataOut  = (float *) calloc(n, sizeof(float)))== NULL) memoryCheck();

 for (i=0;i<n;i++)
   *(dataOut +i) = (float)*(dataIn +i); 

 return dataOut;

}

float * convertShort2Float(unsigned short int *dataIn, int n){

 int i;
 float *dataOut;
 

 if((dataOut  = (float *) calloc(n, sizeof(float)))== NULL) memoryCheck();

 for (i=0;i<n;i++)
   *(dataOut +i) = (float)*(dataIn +i); 

 return dataOut;

}

