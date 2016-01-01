/*
NAME:		getPixel.c 
DESCRIPTION: 	Get pixel from image.
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int getPixelValue(int argc, char *argv[]){

 metaData p;       
 FILE *fin;

 if(argc < 7) getPixelUsage();

 fin=openFile("",argv[2],"rb");

 p.xdim = atoi(argv[3]);
 p.xpos = atoi(argv[4]);
 p.ypos = atoi(argv[5]);
 p.dataType = atoi(argv[6]);
 
 if(argc == 8){
  p.channels = atoi(argv[7]); 
 }
 else{
  p.channels=1; 
 }
 
 p.bpp = dataType2bpp(p.dataType); 
 getYdim(argv[2],&p);
 
 if ( (p.xdim < p.xpos) || (p.ydim < p.ypos) || (p.xpos <=0) || (p.ypos <=0)){
  fprintf(stderr,"Error: Selected Pixel not within image dimensions\n");
  exit(EXIT_FAILURE);
 }

 getPixel(fin,&p);	
 
 fclose(fin);
 return (EXIT_SUCCESS);

}

int getPixel(FILE *fin, metaData *p){
 
 int j=0;
 char pixValByte;
 short pixValShort;
 long pixValLong;
 float pixValFloat;
 double pixValDouble;

 if (p->dataType==1){

 for (j=0;j<p->channels;j++){ 
    fseek(fin, sizeof(char) * ((j * p->xdim * p->ydim) + p->xdim * (p->ypos - 1) + p->xpos - 1), SEEK_SET);
    fread(&pixValByte, sizeof(char), 1, fin);		  
    fprintf(stdout,"Channel %d value: %d\n", j+1, pixValByte);
   } 
 }

 if (p->dataType==2){ 
   for (j=0;j<p->channels;j++){ 
    fseek(fin, sizeof(short) * ((j * p->xdim * p->ydim) + p->xdim * (p->ypos - 1) + p->xpos - 1), SEEK_SET);
    fread(&pixValShort, sizeof(short), 1, fin);		  
    fprintf(stdout,"Channel %d value: %d\n", j+1, pixValShort);
   }
} 

  if (p->dataType==3){
   for (j=0;j<p->channels;j++){ 
    fseek(fin, sizeof(long) * ((j * p->xdim * p->ydim) + p->xdim * (p->ypos - 1) + p->xpos - 1), SEEK_SET);
    fread(&pixValLong, sizeof(long), 1, fin);		  
    fprintf(stdout,"Channel %d value: %ld\n", j+1, pixValLong);
   }
 } 

 if (p->dataType==4){
   for (j=0;j<p->channels;j++){ 
    fseek(fin, sizeof(float) * ((j * p->xdim * p->ydim) + p->xdim * (p->ypos - 1) + p->xpos - 1), SEEK_SET);
    fread(&pixValFloat, sizeof(float), 1, fin); 		  
    fprintf(stdout,"Channel %d value: %f\n", j+1, pixValFloat);
   }
  }

  if (p->dataType==8){
   for (j=0;j<p->channels;j++){ 
    fseek(fin, sizeof(double) * ((j * p->xdim * p->ydim) + p->xdim * (p->ypos - 1) + p->xpos - 1), SEEK_SET);
    fread(&pixValDouble, sizeof(double), 1, fin);		  
    fprintf(stdout,"Channel %d value: %f\n", j+1, pixValDouble);
   }
   }
 
 return (EXIT_SUCCESS);
}


void getPixelUsage(){

 fprintf(stderr,"Usage: leaf -getPixelValue inImg xdim xpos ypos dataType [channels]\n");	
 fprintf(stderr, "    inImg           Input image\n");
 fprintf(stderr, "    xdim            Number of pixels per row\n");
 fprintf(stderr, "    xpos            x position of pixel \n");
 fprintf(stderr, "    ypos            y position of pixel \n");
 fprintf(stderr, "    dataType        1: byte; 2: short; 3: long; 4: float; 8: double\n");
 fprintf(stderr, "    channels        Number of channels (default=1)\n\n");
 exit(EXIT_FAILURE);

}


