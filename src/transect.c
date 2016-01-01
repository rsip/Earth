/*
NAME:		transect.c 
DESCRIPTION: 	Get values along a transect from image.
AUTHOR:	 	Will Grey
VERSION:	2015-11-23	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int transect(int argc, char *argv[]){

 metaData p;       
 FILE *fin;
 int x, y, n;

 if(argc < 8) getTransectUsage();
 
 fin=openFile("",argv[2],"rb");

 p.xdim = atoi(argv[3]);
 p.xoffset = atoi(argv[4])-1;
 p.yoffset = atoi(argv[5])-1;
 p.xoffset2 = atoi(argv[6])-1;
 p.yoffset2 = atoi(argv[7])-1;
 if (argc >=9) p.dataType = atoi(argv[8]); 
 if (argc ==10) p.channels = atoi(argv[9]); 
 
 getYdim(argv[2],&p);
 p.bpp=dataType2bpp(p.dataType); 
 n=getTransect(&p,&x,&y);	
 
 if(p.dataType == 1) getTransectByte(fin, &p, &x, &y, n);
 if(p.dataType == 2) getTransectShort(fin, &p, &x, &y, n);
 if(p.dataType == 3) getTransectLong(fin, &p, &x, &y, n);
 if(p.dataType == 4) getTransectFloat(fin, &p, &x, &y, n);
 if(p.dataType == 8) getTransectDouble(fin, &p, &x, &y, n);


 fclose(fin);
 return (EXIT_SUCCESS);

}

int getTransect(metaData *p, int *x, int *y)
{
 
 int x1, x2, y1, y2, x1start, y1start, i=0;
 double subx, suby,  theta;
 
 if((x  = (int *) calloc(MAX_LINE_LEN, sizeof(int)))== NULL) memoryCheck();
 if((y  = (int *) calloc(MAX_LINE_LEN, sizeof(int)))== NULL) memoryCheck();

 x1=p->xoffset;
 y1=p->yoffset;
 x2=p->xoffset2;
 y2=p->xoffset2;
 subx=0.5;
 suby=0.5;

 x1start=x1;
 y1start=y1;

 theta=atan((double)(x1-x2)/(double)(y1-y2));

 while((x1!=x2)||(y1!=y2)){
  
  if( fabs(subx - suby*fabs(tan(theta))) < 0.00001){
   if (x2 > x1start) x1=x1+1;
   if (y2 > y1start) y1=y1+1;
   if (x2 < x1start) x1=x1-1;
   if (y2 < y1start) y1=y1-1;
   subx=1.0;
   suby=1.0;
  }

  else if(subx<suby*fabs(tan(theta))){
   y1=y1;
   if (x2 > x1start) x1=x1+1;
   if (x2 < x1start) x1=x1-1;
   suby=suby-subx*fabs(tan(DTOR(90)-theta)); 
   subx=1.0;
  }

  else if(subx>suby*fabs(tan(theta))){
   x1=x1;
   if (y2 > y1start) y1=y1+1;
   if (y2 < y1start) y1=y1-1;
   subx=subx-suby*fabs(tan(theta)); 
   suby=1.0;
  }
  
  x[i]=x1;
  y[i]=y1;
  i++;
  
 } 
 
 return i;

} 

int getTransectFloat(FILE *fin, metaData *p, int *x, int *y, int n){
 
 int i,j;
 float *pixVal;

 if((pixVal  = (float *) calloc(n * p->channels, sizeof(float)))== NULL) memoryCheck();
 
 for (i=0;i<p->channels;i++){
  for (j=0;j<n;j++){
   fseek(fin, sizeof(float) * ((i * p->xdim * p->ydim) + p->xdim * (y[j] - 1) + x[j] - 1), SEEK_SET);
   fread(pixVal+i*n+j, sizeof(float), 1, fin);		  
   }
  }

 for (i=0;i<p->channels;i++) fprintf(stdout,"\t%d\t", i);

 for (j=0;j<n;j++){
  fprintf(stdout,"%d %d ", x[j], y[j]);
  for (i=0;i<p->channels;i++)
   fprintf(stdout," %f ", (float)*(pixVal+j*p->channels+i));	  
  fprintf(stdout,"/n");
   }

 return (EXIT_SUCCESS);
}

int getTransectByte(FILE *fin, metaData *p, int *x, int *y, int n){
 
 int i,j;
 char *pixVal;

 if((pixVal  = (char *) calloc(n * p->channels, sizeof(char)))== NULL) memoryCheck();
 
 for (i=0;i<p->channels;i++){
  for (j=0;j<n;j++){
   fseek(fin, sizeof(char) * ((i * p->xdim * p->ydim) + p->xdim * (y[j] - 1) + x[j] - 1), SEEK_SET);
   fread(pixVal+i*n+j, sizeof(char), 1, fin);		  
   }
  }

 for (i=0;i<p->channels;i++) fprintf(stdout,"\t%d\t", i);

 for (j=0;j<n;j++){
  fprintf(stdout,"%d %d ", x[j], y[j]);
  for (i=0;i<p->channels;i++)
   fprintf(stdout," %f ", (float)*(pixVal+j*p->channels+i));	  
  fprintf(stdout,"/n");
   }

 return (EXIT_SUCCESS);
}

int getTransectShort(FILE *fin, metaData *p, int *x, int *y, int n){
 
 int i,j;
 short *pixVal;

 if((pixVal  = (short *) calloc(n * p->channels, sizeof(short)))== NULL) memoryCheck();
 
 for (i=0;i<p->channels;i++){
  for (j=0;j<n;j++){
   fseek(fin, sizeof(short) * ((i * p->xdim * p->ydim) + p->xdim * (y[j] - 1) + x[j] - 1), SEEK_SET);
   fread(pixVal+i*n+j, sizeof(short), 1, fin);		  
   }
  }

 for (i=0;i<p->channels;i++) fprintf(stdout,"\t%d\t", i);

 for (j=0;j<n;j++){
  fprintf(stdout,"%d %d ", x[j], y[j]);
  for (i=0;i<p->channels;i++)
   fprintf(stdout," %f ", (float)*(pixVal+j*p->channels+i));	  
  fprintf(stdout,"/n");
   }

 return (EXIT_SUCCESS);
}

int getTransectLong(FILE *fin, metaData *p, int *x, int *y, int n){
 
 int i,j;
 long *pixVal;

 if((pixVal  = (long *) calloc(n * p->channels, sizeof(long)))== NULL) memoryCheck();
 
 for (i=0;i<p->channels;i++){
  for (j=0;j<n;j++){
   fseek(fin, sizeof(long) * ((i * p->xdim * p->ydim) + p->xdim * (y[j] - 1) + x[j] - 1), SEEK_SET);
   fread(pixVal+i*n+j, sizeof(long), 1, fin);		  
   }
  }

 for (i=0;i<p->channels;i++) fprintf(stdout,"\t%d\t", i);

 for (j=0;j<n;j++){
  fprintf(stdout,"%d %d ", x[j], y[j]);
  for (i=0;i<p->channels;i++)
   fprintf(stdout," %f ", (float)*(pixVal+j*p->channels+i));	  
  fprintf(stdout,"/n");
   }

 return (EXIT_SUCCESS);
}

int getTransectDouble(FILE *fin, metaData *p, int *x, int *y, int n){
 
 int i,j;
 double *pixVal;

 if((pixVal  = (double *) calloc(n * p->channels, sizeof(double)))== NULL) memoryCheck();
 
 for (i=0;i<p->channels;i++){
  for (j=0;j<n;j++){
   fseek(fin, sizeof(double) * ((i * p->xdim * p->ydim) + p->xdim * (y[j] - 1) + x[j] - 1), SEEK_SET);
   fread(pixVal+i*n+j, sizeof(double), 1, fin);		  
   }
  }

 for (i=0;i<p->channels;i++) fprintf(stdout,"\t%d\t", i);

 for (j=0;j<n;j++){
  fprintf(stdout,"%d %d ", x[j], y[j]);
  for (i=0;i<p->channels;i++)
   fprintf(stdout," %f ", *(pixVal+j*p->channels+i));	  
  fprintf(stdout,"/n");
   }

 return (EXIT_SUCCESS);
}


void getTransectUsage(){

 fprintf(stderr,"Usage: leaf -transect inImg xdim xpos1 ypos1 xpos2 ypos2 [dataType] [Channels] \n");	
 fprintf(stderr, "    inImg           Input image\n");
 fprintf(stderr, "    xdim            Number of pixels per row\n");
 fprintf(stderr, "    xpos1           x position of pixel 1 \n");
 fprintf(stderr, "    ypos1           y position of pixel 1\n");
 fprintf(stderr, "    xpos2           x position of pixel 2 \n");
 fprintf(stderr, "    ypos2           y position of pixel 2\n");
 fprintf(stderr, "    [dataType]      1: byte; 2: short; 3: long; 4: float; 8: double\n");
 fprintf(stderr, "    [channels]      Number of channels\n\n");
 exit(EXIT_FAILURE);

}


