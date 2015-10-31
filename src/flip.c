/*
NAME:		flip.c 
DESCRIPTION: 	Flips images left/right or up/down.
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
COMPILE:        gcc flip.c utility.c -o flip -Wall
*/


#include "leaf.h"

int flipImg(clparse *clinput){

 int ydim;
 struct stat size;
 FILE *fin, *fout;
   	
 if (clinput->xdim < clinput->bpp){
  fprintf(stderr, "Need number of pixels in x dimension (-xdim)\n");  
  exit(EXIT_FAILURE);
 }
	
 fin=openFile("",clinput->infile,"rb");
 fout=openFile("",clinput->outfile,"wb");
	
 ydim = size.st_size / (clinput->xdim * clinput->bpp);
 flip(fin,fout,clinput->xdim,ydim,clinput->bpp,clinput->flag);			
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

int flip(FILE *fin, FILE *fout, int xdim, int ydim, int bpp, int flip){
 
 data_t imgIn, imgOut;

 if((imgIn.s  = malloc(xdim * ydim * bpp)) == NULL) memoryCheck();
 if((imgOut.s = malloc(xdim * ydim * bpp)) == NULL) memoryCheck();
 fread(imgIn.s,bpp,xdim*ydim,fin);
 
 switch(flip){
  case 0:
   switch (bpp){
    case 1:
     xFlip8(&imgIn,&imgOut,xdim,ydim,bpp);
     break;
    case 2:
     xFlip16(&imgIn,&imgOut,xdim,ydim,bpp);
     break;
    case 4:
     xFlip32(&imgIn,&imgOut,xdim,ydim,bpp);
     break;
    case 8:
     xFlip64(&imgIn,&imgOut,xdim,ydim,bpp);
     break; 
    default:
     break;
  }
  case 1:
   switch (bpp){
    case 1:
     xFlip8(&imgIn,&imgOut,xdim,ydim,bpp);
     break;
    case 2:
     xFlip16(&imgIn,&imgOut,xdim,ydim,bpp);
     break;
    case 4:
     xFlip32(&imgIn,&imgOut,xdim,ydim,bpp);
     break;
    case 8:
     xFlip64(&imgIn,&imgOut,xdim,ydim,bpp);
     break; 
    default:
     break;
  }
 }


 fwrite(imgOut.s,bpp,xdim*ydim,fout);
 free(imgIn.s);
 free(imgOut.s);

 return (EXIT_SUCCESS);

}

int xFlip8(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->c[((y * xdim) + (xdim - 1 - x)) * bpp]=imgIn->c[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int yFlip8(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->c[((((ydim - 1 - y) * xdim)) + x) * bpp]=imgIn->c[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int xFlip16(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->i[((y * xdim) + (xdim - 1 - x)) * bpp]=imgIn->i[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int yFlip16(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->i[((((ydim - 1 - y) * xdim)) + x) * bpp]=imgIn->i[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int xFlip32(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->f[((y * xdim) + (xdim - 1 - x)) * bpp]=imgIn->f[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int yFlip32(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->f[((((ydim - 1 - y) * xdim)) + x) * bpp]=imgIn->f[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int xFlip64(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->d[((y * xdim) + (xdim - 1 - x)) * bpp]=imgIn->d[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

int yFlip64(data_t *imgIn, data_t *imgOut, int xdim, int ydim, int bpp){
 
 int x, y;

 for (y = 0; y < ydim; y++)
  for (x = 0; x < xdim; x++)	
    imgOut->d[((((ydim - 1 - y) * xdim)) + x) * bpp]=imgIn->d[((y * xdim) + x) * bpp];
  
 return (EXIT_SUCCESS);

}

