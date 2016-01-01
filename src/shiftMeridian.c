/*
NAME:		shiftMeridian.c 
DESCRIPTION: 	In global datasets shift meridian from middle to edge.
AUTHOR:	 	Will Grey
VERSION:	2015-11-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#include "leaf.h"

int shiftMeridian(int argc, char **argv){

 metaData p;
 FILE *fin, *fout;
 struct stat size; 

 p.bpp=1;
 p.channels=1;

 if (argc < 5) flipUsage("-shiftMeridian");
 
 fin=openFile("",argv[ 2 ],"rb");
 fout=openFile("",argv[ 3 ],"wb");	
 p.xdim=atoi(argv[ 4 ]);
 if (argc >= 6) p.bpp=atoi(argv[ 5 ]);
 if (argc == 7) p.channels=atoi(argv[ 6 ]);
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else p.ydim = size.st_size / (p.xdim * p.bpp * p.channels);

 meridian(fin,fout,&p); 
 return (EXIT_SUCCESS);

}

int meridian(FILE *fin, FILE *fout,  metaData *p){

unsigned char *inImg, *outImg;
 int x, y, i, j, xdimDiv2;
 
 inImg  = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 outImg = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 
 xdimDiv2=p->xdim/2;
 
 for (j = 0; j < p->channels; j++){
  fread(inImg, p->bpp, p->xdim*p->ydim, fin);
  for (y = 0; y < p->ydim; y++){
   for (x = 0; x < xdimDiv2; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + ((y * p->xdim) +  (x + xdimDiv2)) * p->bpp + i) 
     = *(inImg + ((y * p->xdim) + x) * p->bpp + i);
  
   for (x = xdimDiv2; x < p->xdim; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + ((y * p->xdim) +  (x - xdimDiv2)) * p->bpp + i) 
     = *(inImg + ((y * p->xdim) + x) * p->bpp + i); 
  }
  fwrite(outImg, p->bpp, p->xdim*p->ydim, fout);
 } 

 free(inImg);
 free(outImg);
 return EXIT_SUCCESS;

}

