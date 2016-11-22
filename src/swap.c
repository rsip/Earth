/*
NAME:		swap.c 
DESCRIPTION: 	Byte swapping routine from Little
		Endian to Big Endian and vice versa
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
COMPILE:        gcc swap.c utility.c -o swap -Wall
*/

#include "earth.h"

int runSwap(int argc, char **argv){

 metaData hdrData;
 
 if (argc <3) swapUsage();
 strcpy(hdrData.infile,argv[ 2 ]); 
 if (argc >=4){ 
  strcpy(hdrData.outfile,argv[ 3 ]); 
 }
 else{
  strcpy(hdrData.outfile, hdrData.infile); 
  strcat(hdrData.outfile,".out");
 }
 if (argc == 5){
  hdrData.bpp=atoi(argv[ 4 ]);
 }
 else{
  hdrData.bpp=2;
 }

 swap(&hdrData); 
 return (EXIT_SUCCESS);
}

int swap(metaData *hdrData)
{
 
 FILE *fin, *fout;
 int remainderPixels;
 void *img; 

 if (!strcmp(hdrData->infile,"")) {
  swapUsage();
 } 
	
 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((img  = (void *) calloc(PIXELS, hdrData->bpp))== NULL) memoryCheck();

 if ((hdrData->bpp == 2) | (hdrData->bpp == 4)| (hdrData->bpp == 8)){

  while ((remainderPixels=fread(img,hdrData->bpp,PIXELS,fin)) == PIXELS){
   byteSwap(img, PIXELS, hdrData->bpp);
   fwrite(img,hdrData->bpp,PIXELS,fout);
  }	
	
  byteSwap(img,remainderPixels, hdrData->bpp);
  fwrite(img,hdrData->bpp,remainderPixels,fout);

 }

 free(img); 

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int byteSwap(void *dataIn, int n,  int numBytes){
 
 /* convert from little endian to big endian or vice versa */
 /* 2 bytes: bytes ab reordered to ba */
 /* 4 bytes: bytes abcd reordered to dcba */ 
 /* 8 bytes: bytes abcdefgh reordered to hgfedcba */ 

 int i,j;
 unsigned char *value;
 unsigned char byte;
 int swap;
 swap = numBytes / 2;

 for (i=0;i<n*numBytes;i=i+numBytes){

  value = (unsigned char *)(dataIn+i); 
  
  for (j=0; j<swap;j++){
    
   byte = *(value + j);
   *(value) = *(value+(numBytes-1)-j);
   *(value+(numBytes-1)-j) = byte;
   
  }
 }

 return (EXIT_SUCCESS);

}

void swapUsage(){
 fprintf(stderr,"\nUsage: earth -swap infile [outfile] [bpp] \n\n");
 fprintf(stderr, "   infile        Input image\n"); 	   
 fprintf(stderr, "   outfile       Output image\n"); 
 fprintf(stderr, "   bpp           bytes per pixel (2,4,8) \n\n");
 exit(EXIT_FAILURE);
}
