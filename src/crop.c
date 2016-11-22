/*
NAME:		crop.c 
DESCRIPTION: 	To crop an image.
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int runCrop(int argc, char *argv[]){

 struct stat size;
 metaData p;       
 FILE *fin, *fout;

 if(argc < 10) cropUsage();
 
 p.channels=1;	 
 
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");

 p.xdim = atoi(argv[4]);
 p.xoffset = atoi(argv[5]);
 p.yoffset = atoi(argv[6]);
 p.xsize = atoi(argv[7]);
 p.ysize = atoi(argv[8]);
 p.bpp = atoi(argv[9]);
 if (argc==11) p.channels =  atoi(argv[10]);
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 p.ydim = size.st_size / (p.xdim * p.bpp * p.channels);
 
 if ( ( p.xsize + p.xoffset ) > p.xdim  || ( p.ysize + p.yoffset ) > p.ydim ){
  fprintf(stderr,"Error: Image geometry is incorrect. Retry with different xoffset, yoffset, xsize and/or ysize.\n");
  exit(EXIT_FAILURE);
 }
 
 crop(fin,fout,&p);	
 
 fclose(fin);
 fclose(fout);
 return (EXIT_SUCCESS);

}

int crop(FILE *fin, FILE *fout, metaData *p){
 
 void *img;	 
 int i, y;	

 if((img  = malloc(p->xsize * p->bpp)) == NULL) memoryCheck();

 for (i=0;i<p->channels;i++){
  for(y = 0; y < p->ysize; y++){
   fseek(fin, ( ( p->xoffset + p->yoffset * p->xdim + y * p->ydim) * p->bpp )
            + ( i * p->xdim * p->ydim * p->bpp ), 0);
   fread(img, p->bpp, p->xsize, fin);
   fwrite(img, p->bpp, p->xsize, fout);
  }
 }
	
 free(img);
 return (EXIT_SUCCESS);
}


void cropUsage(){

 fprintf(stderr,"Usage: earth -crop inImg cropImg xdim xoffset yoffset xsize ysize bytesPerPixel [channels] \n\n");
 fprintf(stderr, "    inImg           Input image\n");
 fprintf(stderr, "    outImg          Output crop image\n");  
 fprintf(stderr, "    xdim            Number of pixels per row\n");
 fprintf(stderr, "    xoffset         Start pixel in x\n");
 fprintf(stderr, "    yoffset         Start pixel in y\n");
 fprintf(stderr, "    xsize           Cropped image number of pixels in x\n");
 fprintf(stderr, "    ysize           Cropped image number of pixels in y\n");
 fprintf(stderr, "    bytesPerPixel   Bytes per pixel: 1,2,4, or 8\n");
 fprintf(stderr, "    [channels]      Number of channels\n\n"); 

 exit(EXIT_FAILURE);

}


