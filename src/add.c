/*
NAME:		add.c 
DESCRIPTION: 	Add two images together
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int add(int argc, char **argv)
{
 
 FILE *fin1, *fin2, *fout;
 metaData hdrData;
 initialiseHdrData(&hdrData);
 
 hdrData.dataType=1;

 if (argc < 4) {
  arithmaticUsage("-add");	
 } 

 strcpy(hdrData.infile, argv[2]);
 strcpy(hdrData.infile2, argv[3]);
 strcpy(hdrData.outfile, argv[4]);
 if(argc == 6) hdrData.dataType = atoi(argv[5]);
	
 fin1=openFile("",hdrData.infile,"rb");
 fin2=openFile("",hdrData.infile2,"rb");
 fout=openFile("",hdrData.outfile,"wb");	

 compareFileSize(argv[2], argv[3]);
		
 if (hdrData.dataType == 1) addByte(fin1,fin2,fout);
 if (hdrData.dataType == 2) addShort(fin1,fin2,fout);
 if (hdrData.dataType == 3) addLong(fin1,fin2,fout);
 if (hdrData.dataType == 4) addFloat(fin1,fin2,fout);
 if (hdrData.dataType == 8) addDouble(fin1,fin2,fout);
	
 fclose(fin1);
 fclose(fin2);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void arithmaticUsage(char *option){
 fprintf(stderr,"Usage: leaf %s infile1 infile2 outfile [data_type] \n\n", option);
 fprintf(stderr, "   infile1          input image 1\n");
 fprintf(stderr, "   infile2          input image 2\n");
 fprintf(stderr, "   outfile          output image\n");	   		
 fprintf(stderr, "   data_type        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n\n");
 exit(EXIT_FAILURE);
}

int addByte (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned char *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(char),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(char), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) + *(inImg2 + x);
						
  fwrite(outImg, sizeof(char), PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) + *(inImg2 + x);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int addLong(FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned long *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (unsigned long *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned long *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();
 if((outImg = (unsigned long *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(long),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(long), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) + *(inImg2 + x);
						
  fwrite(outImg, sizeof(long),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) + *(inImg2 + x);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}	

int addShort (FILE *fin1, FILE *fin2, FILE *fout)
{	
 unsigned short *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();
 if((outImg = (unsigned short *) calloc(PIXELS,sizeof(short)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(short),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(short), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) + *(inImg2 + x);
						
  fwrite(outImg, sizeof(short),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) + *(inImg2 + x);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int addFloat (FILE *fin1, FILE *fin2, FILE *fout)
{	
 float *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 if((inImg2  = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(PIXELS,sizeof(float)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(float),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(float), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) + *(inImg2 + x);
						
  fwrite(outImg, sizeof(float),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) + *(inImg2 + x);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}	
	
int addDouble (FILE *fin1, FILE *fin2, FILE *fout)
{	
 double *inImg1, *inImg2, *outImg;
 int x, remainderPixels;
	
 if((inImg1  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 if((inImg2  = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();
 if((outImg = (double *) calloc(PIXELS,sizeof(double)))== NULL) memoryCheck();	
 
 while ((remainderPixels=fread(inImg1,sizeof(double),PIXELS,fin1)) == PIXELS){
  fread(inImg2, sizeof(double), PIXELS, fin2);
  
 for(x = 0; x < PIXELS; x++)
   *(outImg + x) = *(inImg1 + x) + *(inImg2 + x);
						
  fwrite(outImg, sizeof(double),PIXELS, fout);
						
 }

 for (x=0;x<remainderPixels;x++)
  *(outImg + x)=*(inImg1 + x) + *(inImg2 + x);
  
 fwrite(outImg,sizeof(double),remainderPixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}	
		
