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

#include "leaf.h"

int swap(clparse *clinput)
{
 
 FILE *fin, *fout;
 int remainderPixels;
 void *img; 
	
 fin=openFile("",clinput->infile,"rb");
 fout=openFile("",clinput->outfile,"wb");
 	
 if((img  = (void *) calloc(PIXELS, clinput->bpp))== NULL) memoryCheck();

 if ((clinput->bpp == 2) | (clinput->bpp == 4)| (clinput->bpp == 8)){

  while ((remainderPixels=fread(img,clinput->bpp,PIXELS,fin)) == PIXELS){
   byteSwap(img, PIXELS, clinput->bpp);
   fwrite(img,clinput->bpp,PIXELS,fout);
  }	
	
  byteSwap(img,remainderPixels, clinput->bpp);
  fwrite(img,clinput->bpp,remainderPixels,fout);

 }

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


