/*
NAME:		flip.c 
DESCRIPTION: 	Flips images left/right or up/down.
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#include "earth.h"

int flip(int argc, char **argv, int (*f)(FILE *, FILE *, metaData *)){

 metaData p;
 FILE *fin, *fout;
 struct stat size; 

 p.bpp=1;
 p.channels=1;

 if (argc < 5) flipUsage("-[x/y]flip");
 
 fin=openFile("",argv[ 2 ],"rb");
 fout=openFile("",argv[ 3 ],"wb");	
 p.xdim=atoi(argv[ 4 ]);
 if (argc >= 6) p.bpp=atoi(argv[ 5 ]);
 if (argc == 7) p.channels=atoi(argv[ 6 ]);
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else p.ydim = size.st_size / (p.xdim * p.bpp * p.channels);

 f(fin,fout,&p); 
 return (EXIT_SUCCESS);

}

void flipUsage(char *t){

 fprintf(stderr,"\nUsage: earth %s inImg outImg xdims [bpp] [channels]\n", t);
 fprintf(stderr, "    infile           input image\n");
 fprintf(stderr, "    outfile          output image\n"); 
 fprintf(stderr, "    xdim             number of pixels per row\n"); 
 fprintf(stderr, "    bpp              bytes per pixel: 1,2,4, or 8\n");
 fprintf(stderr, "    channels         Number of channels\n\n");
 exit(EXIT_FAILURE);

}


int xflip(FILE *fin, FILE *fout,  metaData *p){

unsigned char *inImg, *outImg;
 int x, y, i, j;
 
 inImg  = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 outImg = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 
 for (j = 0; j < p->channels; j++){
  fread(inImg, p->bpp, p->xdim*p->ydim, fin);
  for (y = 0; y < p->ydim; y++)
   for (x = 0; x < p->xdim; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + ((y * p->xdim) + (p->xdim - x - 1)) * p->bpp + i) 
     = *(inImg + ((y * p->xdim) + x) * p->bpp + i);
  
  fwrite(outImg, p->bpp, p->xdim*p->ydim, fout);
 } 

 free(inImg);
 free(outImg);
 return EXIT_SUCCESS;

}

int yflip(FILE *fin, FILE *fout,  metaData *p){

unsigned char *inImg, *outImg;
 int x, y, i, j;
 
 inImg  = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 outImg = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 
 for (j = 0; j < p->channels; j++){
  fread(inImg, p->bpp, p->xdim*p->ydim, fin);
  for (y = 0; y < p->ydim; y++)
   for (x = 0; x < p->xdim; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + (((p->ydim - 1 - y) * p->xdim) + x) * p->bpp + i)
     = *(inImg + ((y * p->xdim) + x) * p->bpp + i);
  
  fwrite(outImg, p->bpp, p->xdim*p->ydim, fout);
 } 

 free(inImg);
 free(outImg);
 return EXIT_SUCCESS;

}

