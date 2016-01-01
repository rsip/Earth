/*
NAME:		mkimg.c 
DESCRIPTION: 	Creates a single value raw binary image file.
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int mkimg(int argc, char **argv)
{
 
 metaData hdrData;
 hdrData.dataType=1;
 hdrData.channels=1;
 FILE *fout;
 float pixVal=0.0;
 
 if (argc < 7) {
  mkimgUsage();	
 } 

 strcpy(hdrData.outfile,argv[2]); 
 hdrData.xdim = atoi(argv[3]);
 hdrData.ydim = atoi(argv[4]);
 hdrData.dataType = atoi(argv[5]);
 pixVal=atof(argv[6]);
 if (argc==8)  hdrData.channels = atoi(argv[7]);
	
 fout=openFile("",hdrData.outfile,"wb");	
	
 if (hdrData.dataType == 1) mkimgByte(fout,&hdrData,(char)pixVal);
 if (hdrData.dataType == 2) mkimgShort(fout,&hdrData,(short)pixVal);
 if (hdrData.dataType == 3) mkimgLong(fout,&hdrData,(long)pixVal);
 if (hdrData.dataType == 4) mkimgFloat(fout,&hdrData,(float)pixVal);
 if (hdrData.dataType == 8) mkimgDouble(fout,&hdrData,(double)pixVal);
	
 
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void mkimgUsage(){
 fprintf(stderr,"Usage: leaf -mkimg outImg xdim ydim dataType pixVal [channels]\n\n"); 
 fprintf(stderr, "   outImg          Name of image to create\n");
 fprintf(stderr, "   xdim            Number of pixels in x dimension \n");
 fprintf(stderr, "   ydim            Number of pixels in y dimension \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n");
 fprintf(stderr, "   pixVal          Pixel value\n");
 fprintf(stderr, "   [channels]      Number of channels \n\n");
 exit(EXIT_FAILURE);
}

int mkimgByte (FILE *fout, metaData *hdrData, char pixVal){	
 
 char *outImg;
 int i,j;
	
 if((outImg = (char *) calloc(hdrData->xdim,sizeof(char)))== NULL) memoryCheck();	
 for(i = 0; i < hdrData->xdim; i++)
  *(outImg + i) = pixVal;

 for(i = 0; i < hdrData->channels; i++)  
  for(j = 0; j < hdrData->ydim; j++) 
   fwrite(outImg, sizeof(char), hdrData->xdim, fout);						
 
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int mkimgShort (FILE *fout, metaData *hdrData, short pixVal){	
 
 short *outImg;
 int i,j;
	
 if((outImg = (short *) calloc(hdrData->xdim,sizeof(short)))== NULL) memoryCheck();	
 for(i = 0; i < hdrData->xdim; i++)
  *(outImg + i) = pixVal;

 for(i = 0; i < hdrData->channels; i++)  
  for(j = 0; j < hdrData->ydim; j++) 
   fwrite(outImg, sizeof(short), hdrData->xdim, fout);						
 
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int mkimgLong (FILE *fout, metaData *hdrData, long pixVal){	
 
 long *outImg;
 int i,j;
	
 if((outImg = (long *) calloc(hdrData->xdim,sizeof(long)))== NULL) memoryCheck();	
 for(i = 0; i < hdrData->xdim; i++)
  *(outImg + i) = pixVal;

 for(i = 0; i < hdrData->channels; i++)  
  for(j = 0; j < hdrData->ydim; j++) 
   fwrite(outImg, sizeof(long), hdrData->xdim, fout);						
 
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int mkimgFloat (FILE *fout, metaData *hdrData, float pixVal){	
 
 float *outImg;
 int i,j;
	
 if((outImg = (float *) calloc(hdrData->xdim,sizeof(float)))== NULL) memoryCheck();	
 for(i = 0; i < hdrData->xdim; i++)
  *(outImg + i) = pixVal;

 for(i = 0; i < hdrData->channels; i++)  
  for(j = 0; j < hdrData->ydim; j++) 
   fwrite(outImg, sizeof(float), hdrData->xdim, fout);						
 
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int mkimgDouble (FILE *fout, metaData *hdrData, double pixVal){	
 
 double *outImg;
 int i,j;
	
 if((outImg = (double *) calloc(hdrData->xdim,sizeof(double)))== NULL) memoryCheck();	
 for(i = 0; i < hdrData->xdim; i++)
  *(outImg + i) = pixVal;

 for(i = 0; i < hdrData->channels; i++)  
  for(j = 0; j < hdrData->ydim; j++) 
   fwrite(outImg, sizeof(double), hdrData->xdim, fout);						
 
 free(outImg);
	
 return (EXIT_SUCCESS);
}	

