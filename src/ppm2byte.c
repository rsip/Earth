/*
NAME:		ppm2byte.c 
DESCRIPTION: 	Converts ppm to binary byte data
AUTHOR:	 	Will Grey
VERSION:	2015-11-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int ppm2byte(int argc, char *argv[]){
 
 int xdim, ydim, i, j, k, r, g, b, x;
 FILE *fin, *fout;
 unsigned char *row;   			 
 char buffer[MAX_LINE_LEN];

 unsigned char red[]   ={  0,  0,  0,127,127,127,255,255,255,  0,  0,  0,127,127,127,255,255,255,  0,  0,  0,127,127,127,255,255,255};
 unsigned char green[] ={  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255,  0,127,255};
 unsigned char blue[]  ={  0,  0,  0,  0,  0,  0,  0,  0,  0,127,127,127,127,127,127,127,127,127,255,255,255,255,255,255,255,255,255};


 if (argc != 4) {
  fprintf(stderr,"Usage: leaf -ppm2byte infile outfile\n");
  fprintf(stderr, "  infile           input ppm image\n");
  fprintf(stderr, "  outfile          output byte image\n\n"); 
  exit(EXIT_FAILURE);
 } 
 		
 fin  = openFile("", argv[2], "r");
 fout = openFile("", argv[3], "wb");
 
 fgets(buffer, MAX_LINE_LEN, fin);
 fgets(buffer, MAX_LINE_LEN, fin);

 sscanf(buffer,"%d %d",&xdim,&ydim);
 row = (unsigned char *) calloc(xdim,sizeof(char)); 
 fprintf(stdout, "xdim: %d\n",xdim);
 fprintf(stdout, "ydim: %d\n",ydim);
  
 fgets(buffer, MAX_LINE_LEN, fin);   

 for (i=0;i<ydim;i++){
   
  fgets(buffer, MAX_LINE_LEN, fin);  
  x=0;
  for(j=0; j<xdim*PPM_FACTOR; j=j+PPM_FACTOR){
   sscanf(buffer+j," %3d %3d %3d",&r,&g,&b);
      for (k=0;k<MAX_COLOURS;k++){         
       if (red[k]==r && green[k]==g && blue[k]==b){
        *(row + x)=k;    
       }
      }
       x++;			
  }   
   fwrite(row, sizeof(char), xdim, fout);   
 }

 free(row);
 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}			

