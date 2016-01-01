/*
NAME:		linear2Dinterp.c 
DESCRIPTION: 	Perform 2D linear interpolation to upscale image.
AUTHOR:	 	Will Grey
VERSION:	2015-12-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int linear2Dinterp(int argc, char *argv[]){

 metaData p;       


 if(argc < 7) linear2DinterpUsage();
 
 strcpy(p.infile,argv[ 2 ]); 
 strcpy(p.outfile,argv[ 3 ]);
 

 p.xdim = atoi(argv[4]);
 p.xscale = atoi(argv[5]);
 p.yscale = atoi(argv[6]);

 if(argc == 9){
  p.dataType = atoi(argv[8]); 
 }
 else{
  p.dataType=1; 
 }

 if(argc >= 8){
  p.channels = atoi(argv[7]); 
 }
 else{
  p.channels=1; 
 }

 getYdim(argv[2], &p);

 interpolReg2DGrid(&p);	
 

 return (EXIT_SUCCESS);

}


void linear2DinterpUsage(){

 fprintf(stderr,"Usage: leaf -linear2Dinterp inImg outImg xdim xscale yscale [channels] [dataType] \n");	
 fprintf(stderr, "    inImg           Input image\n");
 fprintf(stderr, "    outImg          Output image\n");
 fprintf(stderr, "    xdim            Number of pixels per row\n");
 fprintf(stderr, "    xscale          Scale in x\n");
 fprintf(stderr, "    yscale          Scale in y\n");
 fprintf(stderr, "    [channels]      Number of channels (default=1)\n");
 fprintf(stderr, "    [dataType]      Float Only\n\n");
 
 exit(EXIT_FAILURE);

}

int interpolReg2DGrid(metaData *p)
{  

 FILE *fin, *fout;
 float *inImg, *outImg;
 int xsize, ysize, x, y, i, j, k;
 int c[4];
 
 xsize=(p->xdim-1)*p->xscale;
 ysize=(p->ydim-1)*p->yscale;

 if((inImg  = (float *) calloc(p->xdim*p->ydim, sizeof(float)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(xsize * ysize, sizeof(float)))== NULL) memoryCheck();

 fin=openFile("",p->infile,"rb");
 fout=openFile("",p->outfile,"wb");

 for (k=0;k<p->channels;k++){

 fread(inImg,sizeof(float),p->xdim*p->ydim,fin);
 
  for (x=0;x<xsize;x+=p->xscale){ 

   for (y=0;y<xsize;y+=p->yscale){    
 
   c[3] = *(inImg + (int)((y+p->yscale)/p->yscale) * p->xdim + (int)((x+p->xscale)/p->xscale));
   c[2] = *(inImg + (int)((y+p->yscale)/p->yscale) * p->xdim + (int)((x          )/p->xscale));
   c[1] = *(inImg + (int)((y          )/p->yscale) * p->xdim + (int)((x+p->xscale)/p->xscale));
   c[0] = *(inImg + (int)((y          )/p->yscale) * p->xdim + (int)((x          )/p->xscale));
   
   for (i=0;i<p->yscale;i++){
    for (j=0;j<p->xscale;j++){
    
      *(outImg + (y + i) * p->xdim + x + j) = 
       (c[0] * ((p->xscale - j)/(float)(p->xscale)) * ((p->yscale - i)/(float)(p->yscale))) 
     + (c[1] * ((	    j)/(float)(p->xscale)) * ((p->yscale - i)/(float)(p->yscale))) 
     + (c[2] * ((p->xscale - j)/(float)(p->xscale)) * ((       i)/(float)(p->yscale)))
     + (c[3] * ((	    j)/(float)(p->xscale)) * ((       i)/(float)(p->yscale))); 
					 
      
    }
   }   
  }
 } 

 fread(outImg,sizeof(float),p->xdim*p->ydim,fin);

 }

 free(outImg);    
 free(inImg);
 fclose(fin);
 fclose(fout);      
 return 0;
   
}

