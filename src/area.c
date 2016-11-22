/*
NAME:		imgVolume.c 
DESCRIPTION: 	Calculates area
AUTHOR:	 	Will Grey
VERSION:	2016-03-26	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int areaCalc(int argc, char **argv){
 
 metaData p;
 FILE *fin;
 float spacing;
 struct stat size;
 p.dataType=1;

 if (argc < 5) areaCalcUsage();
 
 fin=openFile("",argv[ 2 ],"rb");
 p.xdim=atoi(argv[ 3 ]);
 spacing = atof(argv[ 4 ]);
 if (argc == 6) p.dataType=atoi(argv[ 5 ]);

 p.bpp=4;
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else p.ydim = size.st_size / (p.xdim * p.bpp);
	
 if (p.dataType == 1) areaByte(fin,&p,spacing);
 if (p.dataType == 2) areaShort(fin,&p,spacing);
 if (p.dataType == 3) areaLong(fin,&p,spacing);
 if (p.dataType == 4) areaFloat(fin,&p,spacing);
 if (p.dataType == 8) areaDouble(fin,&p,spacing);
 	
 fclose(fin);	
 return (EXIT_SUCCESS);
	
}

void areaCalcUsage(){
 fprintf(stderr,"Usage: earth -areaCalc inimg xdim spacing [dataType]\n\n");
 fprintf(stderr, "   inimg           Input img image \n");
 fprintf(stderr, "   spacing         Pixel spacing (m) \n");	
 fprintf(stderr, "   xdim            Number of pixels is x dimension \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n\n");			
 exit(EXIT_FAILURE);
}


int areaByte(FILE *fin, metaData *p, float spacing){

 unsigned char *img;
 double area=0;
 int x, y;
 	
 if((img = (unsigned char  *) calloc(p->xdim*p->ydim,sizeof(unsigned char)))== NULL) memoryCheck();	
 fread(img,sizeof(unsigned char ),p->xdim*p->ydim,fin);
 
 for(y=0; y < p->ydim; y++) 
  for(x=0; x < p->xdim; x++)
   if  ( *(img + (y * p->xdim) + x) != 0)
    area = area + *(img + (y * p->xdim) + x) * spacing * spacing;

 fprintf(stdout,"area: %f\n",area);	
 
 free(img);	
 return (EXIT_SUCCESS);

}

int areaShort(FILE *fin, metaData *p, float spacing){

 short *img;
 double area=0;
 int x, y;
 	
 if((img = (short *) calloc(p->xdim*p->ydim,sizeof(short)))== NULL) memoryCheck();	
 fread(img,sizeof(short),p->xdim*p->ydim,fin);
 
 for(y=0; y < p->ydim; y++) 
  for(x=0; x < p->xdim; x++)
   if  ( *(img + (y * p->xdim) + x) != 0)
    area = area + *(img + (y * p->xdim) + x) * spacing * spacing;

  fprintf(stdout,"area: %f\n",area);	
 
 free(img);	
 return (EXIT_SUCCESS);

}

int areaLong(FILE *fin, metaData *p, float spacing){

 long *img;
 double area=0;
 int x, y;
 	
 if((img = (long *) calloc(p->xdim*p->ydim,sizeof(long)))== NULL) memoryCheck();	
 fread(img,sizeof(long),p->xdim*p->ydim,fin);
 
 for(y=0; y < p->ydim; y++) 
  for(x=0; x < p->xdim; x++)
   if  ( *(img + (y * p->xdim) + x) != 0)
    area = area + *(img + (y * p->xdim) + x) * spacing * spacing;

  fprintf(stdout,"area: %f\n",area);	
 
 free(img);	
 return (EXIT_SUCCESS);

}

int areaFloat(FILE *fin, metaData *p, float spacing){

 float *img;
 double area=0;
 int x, y;
 	
 if((img = (float *) calloc(p->xdim*p->ydim,sizeof(float)))== NULL) memoryCheck();	
 fread(img,sizeof(float),p->xdim*p->ydim,fin);
 
 for(y=0; y < p->ydim; y++) 
  for(x=0; x < p->xdim; x++)
   if  ( *(img + (y * p->xdim) + x) != 0)
    area = area + *(img + (y * p->xdim) + x) * spacing * spacing;

  fprintf(stdout,"area: %f\n",area);	
 
 free(img);	
 return (EXIT_SUCCESS);

}

int areaDouble(FILE *fin, metaData *p, float spacing){

 double *img;
 double area=0;
 int x, y;
 	
 if((img = (double *) calloc(p->xdim*p->ydim,sizeof(double)))== NULL) memoryCheck();	
 fread(img,sizeof(double),p->xdim*p->ydim,fin);
 
 for(y=0; y < p->ydim; y++) 
  for(x=0; x < p->xdim; x++)
   if  ( *(img + (y * p->xdim) + x) != 0)
    area = area + *(img + (y * p->xdim) + x) * spacing * spacing;

  fprintf(stdout,"area: %f\n",area);	
 
 free(img);	
 return (EXIT_SUCCESS);

}


