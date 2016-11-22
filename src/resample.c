/*
NAME:		resample.c 
DESCRIPTION: 	Resamples raw binary image data using
                nearest-neighbour interpolation
AUTHOR:	 	Will Grey
VERSION:	2015-11-22	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int resample(int argc, char **argv){
 
 metaData hdrData;
 FILE *fin, *fout;
 float factor;

 if (argc < 5) resampleUsage();	
 
 hdrData.bpp = 1;
 hdrData.channels = 1; 

 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	

 hdrData.xdim = atoi(argv[4]);
 factor = atof(argv[5]);
 if (argc >= 7) hdrData.channels = atoi(argv[6]);
 if (argc >= 8) hdrData.bpp = atoi(argv[7]);
 hdrData.dataType=hdrData.bpp;
	
 getYdim(argv[2], &hdrData);
 hdrData.xdimOut = (int)floor((float)hdrData.xdim*factor);
 hdrData.ydimOut = (int)floor((float)hdrData.ydim*factor);
 
 resampleNearestNeighbour (fin, fout, factor, &hdrData);	
 	
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void resampleUsage(){
 fprintf(stderr,"Usage: earth -resample inImg outImg xdim factor [channels] [bytesPerPixel]\n\n");
 fprintf(stderr, "   inImg           Input image                    \n");
 fprintf(stderr, "   outImg          Output image                   \n");
 fprintf(stderr, "   xdim            Number of pixel in x dimension \n");
 fprintf(stderr, "   factor          Resampling factor              \n");	
 fprintf(stderr, "   channels        Number of channels (default =1)  \n");	   		
 fprintf(stderr, "   bpp             Bytes Per Pixel (default =1)    \n\n");
 exit(EXIT_FAILURE);
}

int resampleNearestNeighbour (FILE *fin, FILE *fout, double factor, metaData *p){

 char *inImg, *outImg;
 int x, y, i, j, xpos, ypos;

 if((inImg  = (char *) calloc(p->xdim*p->ydim,p->bpp))== NULL) memoryCheck();
 if((outImg  = (char *) calloc(p->xdimOut*p->ydimOut,p->bpp))== NULL) memoryCheck();

 fprintf(stdout,"Output dimensions:\n");
 fprintf(stdout,"xdim: %d\n",p->xdimOut);
 fprintf(stdout,"ydim: %d\n",p->ydimOut);
	
 for (i=0;i<p->channels;i++){
  fread(inImg,p->bpp,p->xdim*p->ydim,fin);
  
  for(y=0; y<p->ydimOut; y++){
   for(x=0; x<p->xdimOut*p->bpp; x++){
    xpos=rint(x/factor);
    ypos=rint(y/factor);
    for(j=0; j<p->bpp; j++)
     *(outImg + (y * p->xdimOut) + x + j) = *(inImg + (ypos * p->xdimOut) + xpos + j);
   }
  }
  fwrite(outImg,p->bpp,p->xdimOut*p->ydimOut,fout); 
 }
 
 free(inImg);
 free(outImg);
 return (EXIT_SUCCESS);
}

