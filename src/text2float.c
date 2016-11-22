/*
NAME:		text2float.c 
DESCRIPTION: 	Convert from text files to float
AUTHOR:	 	Will Grey
VERSION:	2015-12-20	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int runTxt2float(int argc, char **argv){
 
 metaData hdrData;
 if (argc !=4) usageTxt2float(argv[1]);
 strcpy(hdrData.infile,argv[ 2 ]); 
 strcpy(hdrData.outfile,argv[ 3 ]); 
 
 txt2float(&hdrData); 
 return (EXIT_SUCCESS);

}

void usageTxt2float(char *tool){
 fprintf(stderr,"\nUsage: earth %s infile outfile \n\n", tool);
 fprintf(stderr, "   infile        Input image\n"); 	   
 fprintf(stderr, "   outfile       Output image\n\n");
 exit(EXIT_FAILURE);
}

int txt2float(metaData *hdrData){
 
 FILE *fin, *fout;
 char *inImg;
 float *outImg;
 char *p;
 int cols=0, rows=0;   			 

 fin  = openFile("", hdrData->infile, "r");
 fout = openFile("", hdrData->outfile, "wb");

 if((inImg  = (char *) calloc(MAX_LINE_LEN, sizeof(char)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(MAX_LINE_LEN, sizeof(float)))== NULL) memoryCheck();

 while(fgets(inImg, MAX_LINE_LEN, fin) !=NULL){
  
  if (inImg[0] != '\n'){ 
   cols=0;
   p = strtok(inImg," \t");
   
   while (p!=NULL){
    outImg[cols]=atof(p); 
    p = strtok (NULL, "  \t");
    cols++; 
   } 
   rows++;
   }    
  fwrite(outImg, sizeof(float),cols, fout);
 } 
 
 free(inImg);
 free(outImg);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}		
