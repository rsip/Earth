/*
NAME:		modeFilter.c 
DESCRIPTION: 	Apply mode (majority) filter to byte image data
AUTHOR:	 	Will Grey
VERSION:	2015-11-11	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int modeFilter(int argc, char *argv[]){

 int xdim, ydim, winsize; 
 FILE *fin;
 FILE *fout;
 struct stat size; 
	
 if(argc < 5) modeUsage();
 xdim = atoi(argv[4]);
	
 if(argc == 6) winsize = atoi(argv[5]);
 else winsize = 3;
	
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim;  
	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");	
	
 mode(fin, fout, xdim, ydim, winsize);
	
 fclose(fin);
 fclose(fout);
 return(EXIT_SUCCESS);		
}

void mode(FILE *fin, FILE *fout, int xdim, int ydim, int winsize){

 unsigned int edge, i, j, x, y, hist[256], max;
 unsigned char *inRows, *outRow, **line, *topLine, maxval;
 edge = winsize/2;
	
 if((inRows  = (unsigned char *)  calloc(winsize * xdim, sizeof(char))) == NULL) memoryCheck();
 if((outRow  = (unsigned char *)  calloc(xdim,           sizeof(char))) == NULL) memoryCheck();
 if((line     = (unsigned char **) calloc(winsize,       sizeof(char))) == NULL) memoryCheck();

/*  Set line to point to various places within inRows */
 for(i = 0; i < winsize; i++) *(line + i) = inRows + i*xdim;	
 /*  Read in winsize - 1 ydim into inRows  */
 for(i = 0; i < winsize-1; i++) fread(*(line + i), sizeof(char), xdim, fin); 						
 /* write zero data to edge ydim */
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(char), xdim, fout); 
		
 for(y = edge; y < ydim - edge; y++){
  fread(*(line + winsize-1), sizeof(char), xdim, fin); 
  for(x = edge; x < xdim - edge; x++){
   for(i = 0; i < 256; i++) hist[i] = 0;
   for(i = 0; i < winsize; i++) 
    for(j = 0; j < winsize; j++) 	
     hist[*(inRows + (i * xdim) + x + j - edge)]++;			
   max = 1;
   maxval = *(inRows + (edge * xdim) + x);
   for(i = 0; i < 256; i++) {
    if(hist[i] > max) {
     max = hist[i];
     maxval = i;
    }
   }
  *(outRow + x) = maxval;	
 }
	
  fwrite(outRow, sizeof(char), xdim, fout);														
/* Switch pointers around */							
  topLine = *(line);
  for(i = 0; i < winsize - 1; i++) *(line + i) = *(line + i + 1);	
  *(line + winsize - 1) = topLine;   		
 }
/* write zero data to edge ydim */
 for(x = 0; x < xdim; x++) *(outRow + x) = 0;
 for (y = 0; y < edge ; y++) fwrite(outRow, sizeof(char), xdim, fout); 
	
 free(inRows);
 free(outRow);
 free(line);	
}

int modeUsage(){
 fprintf(stderr,"Usage: leaf -modeFlter inImg outImg xdim [winsize] \n\n");	 	
 fprintf(stderr, "   inImg            Input image (byte)\n");
 fprintf(stderr, "   outImg           Output image (byte)\n");      
 fprintf(stderr, "   xdim             Number of pixels per row\n"); 
 fprintf(stderr, "   winsize          Window size; odd only Default: 3\n\n"); 
 exit(EXIT_FAILURE);	
}
