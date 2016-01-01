/*
NAME:		mosaic.c 
DESCRIPTION: 	Mosaic images.
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int runMosaic(int argc, char *argv[]){

 metaData p;       
 FILE *fin, *fmosaic;

 if(argc != 9) mosaicUsage();
 
 fmosaic=openFile("",argv[2],"r++");
 fin=openFile("",argv[3],"rb");
 
 p.xdim2 = atoi(argv[4]);
 p.xdim = atoi(argv[5]);
 p.xoffset = atoi(argv[6]);
 p.yoffset = atoi(argv[7]);
 p.bpp = atoi(argv[8]);
 p.channels=1; 
 
 getYdim2(argv[2], &p);
 getYdim(argv[3], &p); 

 if( ((p.xoffset + p.xdim) > p.xdim2) || ((p.yoffset + p.ydim) > p.ydim2)){
  fprintf(stderr,"Check file dimensions and offset\n"); 
  exit(0);
 } 

 mosaic(fin,fmosaic,&p);	
 
 fclose(fin);
 fclose(fmosaic);
 return (EXIT_SUCCESS);

}

int mosaic(FILE *fin, FILE *fmosaic, metaData *p){
 
 unsigned char *img;	 
 int y;	

 if((img  = (unsigned char *) malloc(p->xdim * p->bpp)) == NULL) memoryCheck();

 for(y = 0; y < p->ydim; y++){
    
  fseek(fmosaic, ( p->xoffset + p->yoffset * p->ydim2 + y * p->ydim2) * p->bpp, 0);
  fread(img, p->bpp, p->xdim, fin);
  fwrite(img, p->bpp, p->xdim, fmosaic);
			
 }
	
 free(img);
 return (EXIT_SUCCESS);
}

void mosaicUsage(){

 fprintf(stderr,"Usage: leaf -mosaic mosaicImg inImg mosaicXdim inXdim  xoff yoff bytesPerPixel\n\n");
 fprintf(stderr, "    mosaicImg       Mosaic image to be overwritten\n");
 fprintf(stderr, "    inImg           Imput image\n");  
 fprintf(stderr, "    mosaicXdim      Number of pixels per row in mosaic image\n");
 fprintf(stderr, "    inXdim          Number of pixels per row in input image\n");
 fprintf(stderr, "    xoff            Start pixel in x\n");
 fprintf(stderr, "    yoff            Start pixel in y\n");
 fprintf(stderr, "    bytesPerPixel   Bytes per pixel: 1,2,4, or 8\n\n");
 exit(EXIT_FAILURE);

}


