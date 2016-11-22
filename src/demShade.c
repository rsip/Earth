/*
NAME:		demShade.c 
DESCRIPTION: 	Creates shaded relief maps from DEMs.
AUTHOR:	 	Will Grey
VERSION:	2016-02-25	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int demShade(int argc, char **argv){
 
 metaData p;
 FILE *fout, *fslope, *faspect;
 float azimuth=315.0, zenith=45.0;
 struct stat size;
 
 if (argc < 5) demShadeUsage();
 
 fslope=openFile("",argv[ 2 ],"rb");
 faspect=openFile("",argv[ 3 ],"rb");
 fout=openFile("",argv[ 4 ],"wb");
 if (argc>=6) azimuth = atof(argv[ 5 ]);
 if (argc==7) zenith = atof(argv[ 6 ]);
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else p.ydim = size.st_size / (p.xdim * p.bpp);
	
 demShadeFloat(fout,fslope,faspect,&p,azimuth,zenith);

 fclose(fout);
 fclose(fslope);
 fclose(faspect);
	
 return (EXIT_SUCCESS);
	
}

void demShadeUsage(){
 fprintf(stderr,"Usage: earth -demShade inSlope inAspect outShade azimuth zenith\n\n");
 fprintf(stderr, "   inSlope         input slope image \n");
 fprintf(stderr, "   inAspect        input aspect image \n");
 fprintf(stderr, "   outShade        Output shade image\n");
 fprintf(stderr, "   azimuth         Solar azimuth position (0-360) \n");
 fprintf(stderr, "   zenith          Solar zenith (0-90) \n\n");	
    		
 exit(EXIT_FAILURE);
}


int demShadeFloat(FILE *fout, FILE *fslope, FILE *faspect, metaData *p, float azimuth, float zenith){

 float *dem;
 float *slope, *aspect;
 int x, y;
 
 if((dem     = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 if((slope  = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 if((aspect = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 
 
 fread(slope,sizeof(float),p->xdim*p->ydim,fslope);
 fread(aspect,sizeof(float),p->xdim*p->ydim,faspect);
 
 for(y=0; y < p->ydim; y++){ 
 
  for(x=0; x < p->xdim; x++){
  
    *(dem + (y * p->xdim) + x) = SHADE_CONSTANT * 
    cos(DTOR(*(slope + (y * p->xdim) + x))) * cos(DTOR(zenith)) +
    sin(DTOR(*(slope + (y * p->xdim) + x))) * sin(DTOR(zenith)) *
    cos(DTOR(azimuth - *(aspect + (y * p->xdim) + x)));
 
  }
 }

 fwrite(dem, sizeof(float), p->xdim * p->ydim, fout);			
 	
 free(dem);
 free(slope);
 free(aspect);
	
 return (EXIT_SUCCESS);

}

