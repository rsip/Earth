/*
NAME:		byte2pgm.c 
DESCRIPTION: 	Converts from binary byte data to pgm
AUTHOR:	 	Will Grey
VERSION:	2015-11-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int byte2pgm(int argc, char *argv[]){
 
 int xdim, ydim, i, j, nColours;
 struct stat size;
 FILE *fin, *fout;
 char *row;   			 
 
 if (argc != 6) {
  fprintf(stderr,"Usage: leaf -byte2pgm inImg outImg xdim nColours\n");
  fprintf(stderr, "    inImg           input byte image\n");
  fprintf(stderr, "    outImg          output pgm image\n");   
  fprintf(stderr, "    xdim            number of pixels per row\n"); 
  fprintf(stderr, "    nColours        number of colours\n\n");
  exit(EXIT_FAILURE);
 }
  
 fin  = openFile("", argv[2], "rb");
 fout = openFile("", argv[3], "w");

 xdim = atoi(argv[4]);
 nColours=atoi(argv[5]);
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim;   
 row = (char *) calloc(xdim,sizeof(char));



 if (nColours==2){
  fprintf(fout,"P1\n");
 }
 else{
  fprintf(fout,"P2\n");
 }
 
 fprintf(fout,"%d %d\n",xdim,ydim);
 
 if (atoi(argv[5])>2){
  fprintf(fout,"%d\n",nColours);
 }		
 
 for (i=0;i<ydim;i++){ 

   fread(row, sizeof(char), xdim, fin); 
   
   fprintf(fout,"%d",(int)*(row)); 
   for (j=1;j<xdim;j++) 
    fprintf(fout,"%3d",(int)*(row+j)); 
   fprintf(fout,"  \n"); 

 } 
 
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}			

