/*
NAME:		bin2txt.c 
DESCRIPTION: 	Convert binary to text files and vice versa
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int runTextConvert(int argc, char **argv, int (*f)(metaData *)){
 
 metaData hdrData;
 if (argc <=2)
  usageTextConvert(argv[1]);
 strcpy(hdrData.infile,argv[ 2 ]); 
 strcpy(hdrData.outfile,argv[ 3 ]); 
 hdrData.xdim=atoi(argv[ 4 ]);

 f(&hdrData); 
 return (EXIT_SUCCESS);

}

void usageTextConvert(char *tool){
 fprintf(stderr,"\nUsage: earth %s infile outfile xdim \n\n", tool);
 fprintf(stderr, "   infile        Input image\n"); 	   
 fprintf(stderr, "   outfile       Output image\n");
 fprintf(stderr, "   xdim          Number of pixels in x dimension\n\n");
 exit(EXIT_FAILURE);
}

int byte2txt(metaData *hdrData){
 
 int j;
 FILE *fin, *fout;
 char *row;   			 

 fin  = openFile("", hdrData->infile, "rb");
 fout = openFile("", hdrData->outfile, "w");
 if((row  = (char *) calloc(hdrData->xdim, sizeof(char)))== NULL) memoryCheck();
 
  while((fread(row, sizeof(char), hdrData->xdim, fin)!=0)){ 
  
   for (j=0;j<hdrData->xdim;j++) 
    fprintf(fout,"%4d ",*(row+j)); 
   fprintf(fout,"\n"); 

 } 
 
 free(row);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}

int short2txt(metaData *hdrData){
 
 int j;
 FILE *fin, *fout;
 short *row;   			 

 fin  = openFile("", hdrData->infile, "rb");
 fout = openFile("", hdrData->outfile, "w");
 if((row  = (short *) calloc(hdrData->xdim, sizeof(short)))== NULL) memoryCheck();
 
  while((fread(row, sizeof(short), hdrData->xdim, fin)!=0)){ 
  
   for (j=0;j<hdrData->xdim;j++) 
    fprintf(fout,"%6d ",*(row+j)); 
   fprintf(fout,"\n"); 

 } 
 
 free(row);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}

int float2txtSN(metaData *hdrData){
 
 int j;
 FILE *fin, *fout;
 float *row;   			 

 fin  = openFile("", hdrData->infile, "rb");
 fout = openFile("", hdrData->outfile, "w");
 if((row  = (float *) calloc(hdrData->xdim, sizeof(float)))== NULL) memoryCheck();
 
  while((fread(row, sizeof(float), hdrData->xdim, fin)!=0)){
  
   for (j=0;j<hdrData->xdim;j++) 
    fprintf(fout,"%.2e ",*(row+j)); 
   fprintf(fout,"\n"); 

 } 
 
 free(row);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}

int float2txt(metaData *hdrData){
 
 int j;
 FILE *fin, *fout;
 float *row;   			 

 fin  = openFile("", hdrData->infile, "rb");
 fout = openFile("", hdrData->outfile, "w");
 if((row  = (float *) calloc(hdrData->xdim, sizeof(float)))== NULL) memoryCheck();
 
  while((fread(row, sizeof(float), hdrData->xdim, fin)!=0)){
  
   for (j=0;j<hdrData->xdim;j++) 
    fprintf(fout,"%6.2f ",*(row+j)); 
   fprintf(fout,"\n"); 

 } 
 
 free(row);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}

int float2txtRow(metaData *hdrData){
 
 int j;
 FILE *fin, *fout;
 float *row;   			 

 fin  = openFile("", hdrData->infile, "rb");
 fout = openFile("", hdrData->outfile, "w");
 if((row  = (float *) calloc(hdrData->xdim, sizeof(float)))== NULL) memoryCheck();
 
  while((fread(row, sizeof(float), hdrData->xdim, fin)!=0)){ 
  
   for (j=0;j<hdrData->xdim;j++) 
    fprintf(fout,"%f\n",*(row+j)); 
   
 } 
 
 free(row);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}			

