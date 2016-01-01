/*
NAME:		calibrate.c 
DESCRIPTION: 	Apply gain and offset to image pixels
AUTHOR:	 	Will Grey
VERSION:	2015-11-11	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int calibrate(int argc, char **argv){
 
 metaData p;
 FILE *fin, *fout, *ftext;
 float gain[MAX_NUM_CHANNELS], offset[MAX_NUM_CHANNELS];
 int lines=0;
 
 p.channels=1;
 p.dataType=1;
 p.ignoreZeroValue = 0;

 if (argc < 5) calibrateUsage();	
 
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
 ftext=openFile("",argv[4],"r");

 if (argc >=6) p.dataType = atoi(argv[5]);
 if (argc >=7) p.channels = atoi(argv[6]);
 if (argc == 8) p.ignoreZeroValue = atoi(argv[7]);
 
 lines=readGainOffset(ftext, gain, offset);		
 p.bpp=dataType2bpp(p.dataType);
 getPixels(argv[2], &p);

 if (lines !=p.channels){
  fprintf(stderr,"Number of channels and gain offset parameters differ.");
  exit(EXIT_FAILURE);
 }
 if (p.dataType == 1) calibrateByte(fin,fout, &p, gain, offset);
 if (p.dataType == 2) calibrateShort(fin,fout, &p, gain, offset);
 if (p.dataType == 3) calibrateLong(fin,fout, &p, gain, offset);
 if (p.dataType == 4) calibrateFloat(fin,fout, &p, gain, offset);
 if (p.dataType == 8) calibrateDouble(fin,fout, &p, gain, offset); 
	
 fclose(fin);
 fclose(fout);
 fclose(ftext);
	
 return (EXIT_SUCCESS);
	
}

int readGainOffset(FILE *ftext, float *gain, float *offset){
 
 char buffer[TEXT_LINE_LEN];
 int row=0,j;
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext) !=NULL){
  
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",&gain[row]);
  
   for(j=0; j<TEXT_LINE_LEN; j++) 
    if( buffer[j] != '\n' && isspace(buffer[j]))
     sscanf(buffer+j,"%f",&offset[row]); 			
   row++; 
  }
 }    	

 return row;
}

void calibrateUsage(){
 fprintf(stderr,"Usage: leaf -calibrate inImg outImg gainOffsetFile [dataType] [channels] [ignoreZeroValue]\n\n");
 fprintf(stderr, "   inImg            input image\n");
 fprintf(stderr, "   outImg           output image\n");
 fprintf(stderr, "   gainOffsetFile   File containing gain and offset for each channel: \n");   	
 fprintf(stderr, "                    outputVal = offset + gain * inputVal  \n");   		
 fprintf(stderr, "   dataType         1: byte (default), 2: short, 3: long, 4: float, 8: Double\n");
 fprintf(stderr, "   channels         Number of channels (default=1)\n");
 fprintf(stderr, "   ignoreZeroValue  Ignore zero values (default=No(0))   \n\n");
 exit(EXIT_FAILURE);
}

int calibrateByte(FILE *fin, FILE *fout, metaData *p, float *gain, float *offset){

 unsigned char *inImg;
 float *outImg;
 int x, i;
	
 if((inImg  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
   
 for (i = 0; i < p->channels; i++){
  fread(inImg,sizeof(char),p->pixels,fin);

  for(x = 0; x < p->pixels; x++){
   if ((*(inImg + x) == 0) && (p->ignoreZeroValue == 1)){
    *(outImg + x) = (float)*(inImg + x);
   }
   else{
   *(outImg + x) = offset[i] + gain[i] * (float)*(inImg + x); 
   }
  }						
  fwrite(outImg, sizeof(float), p->pixels, fout);						
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int calibrateShort(FILE *fin, FILE *fout, metaData *p, float *gain, float *offset){

 unsigned short *inImg;
 float *outImg;
 int x, i;
	
 if((inImg  = (unsigned short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
   
 for (i = 0; i < p->channels; i++){
  fread(inImg,sizeof(short),p->pixels,fin);

  for(x = 0; x < p->pixels; x++){
   if ((*(inImg + x) == 0) && (p->ignoreZeroValue == 1)){
    *(outImg + x) = (float)*(inImg + x);
   }
   else{
   *(outImg + x) = offset[i] + gain[i] * (float)*(inImg + x); 
   }
  }						
  fwrite(outImg, sizeof(float), p->pixels, fout);						
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int calibrateLong(FILE *fin, FILE *fout, metaData *p, float *gain, float *offset){

 unsigned long *inImg;
 float *outImg;
 int x, i;
	
 if((inImg  = (unsigned long *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
   
 for (i = 0; i < p->channels; i++){
  fread(inImg,sizeof(long),p->pixels,fin);

  for(x = 0; x < p->pixels; x++){
   if ((*(inImg + x) == 0) && (p->ignoreZeroValue == 1)){
    *(outImg + x) = (float)*(inImg + x);
   }
   else{
   *(outImg + x) = offset[i] + gain[i] * (float)*(inImg + x); 
   }
  }						
  fwrite(outImg, sizeof(float), p->pixels, fout);						
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int calibrateFloat(FILE *fin, FILE *fout, metaData *p, float *gain, float *offset){

 float *inImg;
 float *outImg;
 int x, i;
	
 if((inImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
   
 for (i = 0; i < p->channels; i++){
  fread(inImg,sizeof(float),p->pixels,fin);

  for(x = 0; x < p->pixels; x++){
   if ((*(inImg + x) == 0) && (p->ignoreZeroValue == 1)){
    *(outImg + x) = (float)*(inImg + x);
   }
   else{
   *(outImg + x) = offset[i] + gain[i] * (float)*(inImg + x); 
   }
  }						
  fwrite(outImg, sizeof(float), p->pixels, fout);						
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int calibrateDouble(FILE *fin, FILE *fout, metaData *p, float *gain, float *offset){

 double *inImg;
 double *outImg;
 int x, i;
	
 if((inImg  = (double *) calloc(p->pixels,sizeof(double )))== NULL) memoryCheck();	
 if((outImg = (double  *) calloc(p->pixels,sizeof(double )))== NULL) memoryCheck();	
   
 for (i = 0; i < p->channels; i++){
  fread(inImg,sizeof(double ),p->pixels,fin);

  for(x = 0; x < p->pixels; x++){
   if ((*(inImg + x) == 0) && (p->ignoreZeroValue == 1)){
    *(outImg + x) = (double)*(inImg + x);
   }
   else{
   *(outImg + x) = offset[i] + gain[i] * (double)*(inImg + x); 
   }
  }						
  fwrite(outImg, sizeof(double), p->pixels, fout);						
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

