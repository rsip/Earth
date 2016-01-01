/*
NAME:		copy.c 
DESCRIPTION: 	Copy binary data from one file to another
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int runCopy(int argc, char **argv){
 
 metaData hdrData;

 if (argc <=2) copyUsage();
 
 strcpy(hdrData.infile,argv[ 2 ]); 
 if (argc ==4){ 
  strcpy(hdrData.outfile,argv[ 3 ]); 
 }
 else{
  strcpy(hdrData.outfile, hdrData.infile); 
  strcat(hdrData.outfile,".out");
 }
 copy(&hdrData); 
 return (EXIT_SUCCESS);
}


int copy(metaData *hdrData)
{
 
 FILE *fin, *fout;
 int remainderPixels;
 void *img; 

 if (!strcmp(hdrData->infile,"")) {
  copyUsage();
 } 
	
 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((img  = (void *) calloc(PIXELS, 1))== NULL) memoryCheck();

  while ((remainderPixels=fread(img,1,PIXELS,fin)) == PIXELS)
   fwrite(img,1,PIXELS,fout);
 		
  fwrite(img,1,remainderPixels,fout);

 free(img);
 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

void copyUsage(){
 fprintf(stderr,"\nUsage: leaf -copy inImg [outImg] \n\n");
 fprintf(stderr, "   inImg        Input image\n"); 	   
 fprintf(stderr, "   [outImg]     Output image\n\n");
 exit(EXIT_FAILURE);
}
