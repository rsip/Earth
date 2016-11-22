/*
NAME:		demVolume.c 
DESCRIPTION: 	Calculates the volume of a DEM difference
                eg. for elevation changes with Glaciers
                or mining.
AUTHOR:	 	Will Grey
VERSION:	2016-03-26	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int demVolume(int argc, char **argv){
 
 metaData p;
 FILE *fin;
 float spacing, zres;
 struct stat size;
 
 if (argc != 6) demVolumeUsage();
 
 fin=openFile("",argv[ 2 ],"rb");
 p.xdim=atoi(argv[ 3 ]);
 spacing = atof(argv[ 4 ]);
 zres = atof(argv[ 5 ]);
 p.bpp=4;
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else p.ydim = size.st_size / (p.xdim * p.bpp);
	
 demVol(fin,&p,spacing,zres);
 	
 fclose(fin);	
 return (EXIT_SUCCESS);
	
}

void demVolumeUsage(){
 fprintf(stderr,"Usage: earth -demVolume inDEM xdim spacing zres\n\n");
 fprintf(stderr, "   inDEM            input DEM image \n");
 fprintf(stderr, "   xdim             Number of pixels is x dimension \n");	
 fprintf(stderr, "   spacing          Pixel spacing (m) \n");	
 fprintf(stderr, "   zres             Resolution in height (m) \n\n");	   		
 exit(EXIT_FAILURE);
}


int demVol(FILE *fin, metaData *p, float spacing, float zres){

 float *dem;
 double volume=0;
 int x, y;
	
 if((dem = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 fread(dem,sizeof(float),p->xdim*p->ydim,fin);
 
 for(y=0; y < p->ydim; y++) 
  for(x=0; x < p->xdim; x++)
   if  ( *(dem + (y * p->xdim) + x) != 0)
    volume = volume + *(dem + (y * p->xdim) + x) * spacing * spacing * zres;

 fprintf(stdout,"volume: %f\n",volume);	
 
 free(dem);	
 return (EXIT_SUCCESS);

}

