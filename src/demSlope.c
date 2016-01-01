/*
NAME:		demSlope.c 
DESCRIPTION: 	Calculates the slope and 
		aspect from an input DEM float image using the 
		method of Zevenbergen and Thorne.
REFERENCE:	Zevenbergen and Thorne (1987), Quantitative 
                analysis of land surface topography.  
		Earth Surface Processes and Landcforms, 
		vol. 12, pp.47-56.
AUTHOR:	 	Will Grey
VERSION:	2015-12-23	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int demSlope(int argc, char **argv){
 
 metaData p;
 FILE *fin, *fslope, *faspect;
 float spacing;
 struct stat size;
 
 if (argc != 7) demSlopeUsage();
 
 fin=openFile("",argv[ 2 ],"rb");
 fslope=openFile("",argv[ 3 ],"wb");
 faspect=openFile("",argv[ 4 ],"wb");
	
 p.xdim=atoi(argv[ 5 ]);
 spacing = atof(argv[ 6 ]);
 p.bpp=4;
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else p.ydim = size.st_size / (p.xdim * p.bpp);
	
 demSlopeFloat(fin,fslope,faspect,&p,spacing);
 
	
 fclose(fin);
 fclose(fslope);
 fclose(faspect);
	
 return (EXIT_SUCCESS);
	
}

void demSlopeUsage(){
 fprintf(stderr,"Usage: leaf -demSlope inDEM outSlope outAspect xdim spacing\n\n");
 fprintf(stderr, "   inDEM            input DEM image \n");
 fprintf(stderr, "   outSlope         Output slope image\n");
 fprintf(stderr, "   outAspect        Output aspect image\n");
 fprintf(stderr, "   xdim             Number of pixels in x dimension \n");
 fprintf(stderr, "   spacing          Pixel spacing (m) \n\n");	   		
 exit(EXIT_FAILURE);
}



int demSlopeFloat(FILE *fin, FILE *fslope, FILE *faspect, metaData *p, float d){

 float *dem;
 float *slope, *aspect;
 int x, y, edge=1;
 float dzdy, dzdx;
	
 if((dem     = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 if((slope  = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 if((aspect = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 
 
 fread(dem,sizeof(float),p->xdim*p->ydim,fin);
 
 for(y=edge; y < p->ydim-edge; y++){ 
 
  for(x=edge; x < p->xdim-edge; x++){
   dzdx = (float)((*(dem + (y * p->xdim) + x + 1)   - *(dem + (y * p->xdim) + x - 1)) / (2 * d));
   dzdy = (float)((*(dem + ((y + 1) * p->xdim) + x) - *(dem + ((y - 1) * p->xdim) + x )) / (2 * d)); 

   *(slope + (y * p->xdim) + x)  = RTOD((float)sqrt((dzdx * dzdx) + (dzdy * dzdy)));

  if(dzdy != 0){				
   *(aspect + (y * p->xdim) + x) = RTOD(atan2(-1*dzdx,-1*dzdy));
   if(*(aspect + (y * p->xdim) + x) < 0) 
    *(aspect + (y * p->xdim) + x) +=360;   
  }
  else *(aspect + (y * p->xdim) + x) = 90.0; 

  }
 }

 fwrite(slope, sizeof(float), p->xdim * p->ydim, fslope);			
 fwrite(aspect, sizeof(float), p->xdim * p->ydim, faspect);
	
 free(dem);
 free(slope);
 free(aspect);
	
 return (EXIT_SUCCESS);

}


