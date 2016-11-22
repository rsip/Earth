/*
NAME:		interleave.c 
DESCRIPTION: 	convert between different band, pixel and line interleaves
AUTHOR:	 	Will Grey
VERSION:	2015-11-11	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int interleave(int argc, char **argv, int (*f)(FILE *, FILE *, metaData *)){
 
 metaData hdrData;
 FILE *fin, *fout;
 struct stat size;

 if (argc < 5) {
  interleaveUsage(argv[1]);	
 } 
 
 hdrData.channels=3;
 hdrData.bpp=1;

 strcpy(hdrData.infile, argv[2]);
 strcpy(hdrData.outfile, argv[3]);
 hdrData.xdim = atoi(argv[4]);
 if (argc >= 6) hdrData.channels = atoi(argv[5]);
 if (argc == 7) hdrData.bpp = atoi(argv[6]);
 
 fin=openFile("",hdrData.infile,"rb");
 fout=openFile("",hdrData.outfile,"wb");	
 
 stat(hdrData.infile, &size);
 hdrData.ydim = size.st_size /  (hdrData.xdim * hdrData.channels * hdrData.bpp);
	
 f(fin,fout, &hdrData);
 
 fclose(fin);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void interleaveUsage(char *tool){
 fprintf(stderr,"\nUsage: earth %s infile outfile xdim [channels] [bytesPerPixel] \n\n",tool);
 fprintf(stderr, "   infile:            input image \n");
 fprintf(stderr, "   outfile:           output image \n");    
 fprintf(stderr, "   xdim:              number of pixels per line\n");
 fprintf(stderr, "   channels:          number of bands: default=3\n");
 fprintf(stderr, "   bytesPerPixel:     default=1 (byte)\n\n");
 exit(EXIT_FAILURE);
}

int bil2bsq(FILE *fin, FILE *fout, metaData *hdrData){

 void *img;
 int i,y;

 if((img = calloc(hdrData->xdim,hdrData->bpp))== NULL) memoryCheck();	
  for(i=0;i<hdrData->channels;i++){
   for(y = 0; y < hdrData->ydim * hdrData->channels ; y+=hdrData->channels){
    fseek(fin, ( i * hdrData->xdim  +  y * hdrData->xdim ) * hdrData->bpp, SEEK_SET);
    fread(img, hdrData->bpp, hdrData->xdim, fin);
    fwrite(img, hdrData->bpp, hdrData->xdim, fout);
   }
  }
	
 free(img);
 return (EXIT_SUCCESS);

}

int bip2bil(FILE *fin, FILE *fout, metaData *hdrData){

 unsigned char *inImg, *outImg;
 int y, i, x; 

 if((inImg  = (unsigned char *) calloc(hdrData->xdim*hdrData->channels,hdrData->bpp))== NULL) memoryCheck();	
 if((outImg = (unsigned char *) calloc(hdrData->xdim,hdrData->bpp))== NULL) memoryCheck();	
 
 for(y = 0; y < hdrData->ydim; y++){
  fread(inImg, hdrData->bpp, hdrData->xdim*hdrData->channels, fin);
  for(i=0;i<hdrData->channels;i++){
   for(x = 0; x < hdrData->xdim; x++)
    *(outImg + x) = *(inImg + (x * hdrData->channels) + i); 
   fwrite(outImg, hdrData->bpp, hdrData->xdim, fout);	 
  }
 }
	
 free(inImg);
 free(outImg);

 return (EXIT_SUCCESS);

}

int bip2bsq(FILE *fin, FILE *fout, metaData *hdrData){

 unsigned char *inImg, *outImg;
 int y, i, x; 

 if((inImg  = (unsigned char *)calloc(hdrData->xdim*hdrData->channels*hdrData->ydim,hdrData->bpp))== NULL) memoryCheck();	
 if((outImg = (unsigned char *)calloc(hdrData->xdim,hdrData->bpp))== NULL) memoryCheck();
 
 fread(inImg, hdrData->bpp, hdrData->xdim*hdrData->channels*hdrData->ydim, fin);		
	
 for(i=0;i<hdrData->channels;i++){
   for(y = 0; y < hdrData->ydim; y++){
    for(x = 0; x < hdrData->xdim; x++){
     *(outImg+x)=*(inImg + (( hdrData->channels * y * hdrData->xdim ) + ( x * hdrData->channels ) + i) * hdrData->bpp);  
   }
   fwrite(outImg, hdrData->bpp, hdrData->xdim, fout);
  }	
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int bil2bip(FILE *fin, FILE *fout, metaData *hdrData){

 unsigned char *inImg, *outImg;
 int y, i, x; 

 if((inImg  = (unsigned char *) calloc(hdrData->xdim*hdrData->channels,hdrData->bpp))== NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(hdrData->xdim,hdrData->bpp))== NULL) memoryCheck();
		
 for(y = 0; y < hdrData->ydim; y++){
  fread(inImg, hdrData->bpp, hdrData->xdim*hdrData->channels, fin);
  for(x = 0; x < hdrData->xdim; x++){	
   for(i=0;i<hdrData->channels;i++)
    *(outImg + x) = *(inImg + x  + (hdrData->xdim * i)); 
    fwrite(outImg, hdrData->bpp, hdrData->xdim, fout);
  }
 }
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}
