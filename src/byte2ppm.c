/*
NAME:		byte2ppm.c 
DESCRIPTION: 	Converts from binary byte data to ppm colour image
AUTHOR:	 	Will Grey
VERSION:	2015-11-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int byte2ppm(int argc, char *argv[]){
 
 int xdim, ydim, i, j;
 struct stat size;
 FILE *fin, *fout;
 char *row;   			 
 
 unsigned char red[]   ={  0,  0,  0,127,127,127,255,255,255,  0,  0,  0,127,127,127,255,255,255,  0,  0,  0,127,127,127,255,255,255};
 unsigned char green[] ={  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255};
 unsigned char blue[]  ={  0,  0,  0,  0,  0,  0,  0,  0,  0,127,127,127,127,127,127,127,127,127,255,255,255,255,255,255,255,255,255};

 if (argc != 5) {
  fprintf(stderr,"Usage: leaf -byte2ppm infile (byte)  outfile (pgm) xdim\n");
  fprintf(stderr, "    infile           input byte image\n");
  fprintf(stderr, "    outfile          output pgm image\n");   
  fprintf(stderr, "    xdim             number of pixels per row\n\n"); 
  exit(EXIT_FAILURE);
 }
 
 xdim = atoi(argv[4]);
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim;   
 
 fin  = openFile("", argv[2], "rb");
 fout = openFile("", argv[3], "w");
 row = (char *) calloc(xdim,sizeof(char));

 fprintf(fout,"P3\n");
 fprintf(fout,"%d %d\n",xdim,ydim);
 fprintf(fout,"255\n");
 		
 for (i=0;i<ydim;i++){ 

   fread(row, sizeof(char), xdim, fin); 
   
   for (j=0;j<xdim;j++) 
    fprintf(fout," %3d %3d %3d",red[(int)*(row + j)],green[(int)*(row + j)],blue[(int)*(row + j)]); 
   fprintf(fout,"  \n"); 

 } 
 
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}


int byte2ppm3(int argc, char *argv[]){
 
 int xdim, ydim, i, j, k, channels=3;
 struct stat size;
 FILE *fin, *fout;
 char *row;   			 
 
 if (argc != 5) {
  fprintf(stderr,"Usage: leaf -byte2ppm3 infile (byte)  outfile (pgm) xdim\n");
  fprintf(stderr, "    infile           input byte image\n");
  fprintf(stderr, "    outfile          output pgm image\n");   
  fprintf(stderr, "    xdim             number of pixels per row\n\n"); 
  exit(EXIT_FAILURE);
 }
 
 xdim = atoi(argv[4]);
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim / channels;   
 
 fin  = openFile("", argv[2], "rb");
 fout = openFile("", argv[3], "w");
 row = (char *) calloc(xdim*ydim*channels,sizeof(char));

 fprintf(fout,"P3\n");
 fprintf(fout,"%d %d\n",xdim,ydim);
 fprintf(fout,"255\n");
 
 fread(row, sizeof(char), xdim*ydim*channels, fin); 
		
 for (i=0;i<ydim;i++){ 
  for (j=0;j<xdim;j++){
   for (k=0;k<3;k++)
    fprintf(fout,"%4d ", (int)row[(k*xdim*ydim)+i*xdim+j]); 
  }  
  fprintf(fout,"  \n"); 
 } 
 
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}			
			

