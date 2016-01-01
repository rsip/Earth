/**************************************************
 
 Program for georeferncing images using affine transform.
 To compile: gcc leafrotate.c -o leafrotate -Wall
 Last update: 20 September 2015

***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>

#include "leaf.h"

int georeference(int argc, char *argv[])
{
 int xdim, ydim,  dataType=1, x0, y0, w, h, i0, j0;
 struct stat size;
 double **gcp, *x, *y;
 double *ptsX, *ptsY, **ptsReverse; 
 int row; 
		
 if (argc < 6) georeferenceUsage();	 
 
  
	
 gcp=allocateDoubleMatrix(MAX_NUM_GCPS, 3);
 x=allocateDoubleVector(MAX_NUM_GCPS);
 y=allocateDoubleVector(MAX_NUM_GCPS);
 
 row=readGCPFile(argv[2],gcp,x,y);
 ptsX=calcLeastSquaresGCP(gcp,x,row);
 ptsY=calcLeastSquaresGCP(gcp,y,row); 

 ptsReverse=runMatrixInverse(ptsX,ptsY,3);
  
 xdim = atoi(argv[4]);	
 if(argc == 7) dataType = atoi(argv[6]);	
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / (xdim * dataType2bpp(dataType));
       			
 x0 = (int)xdim/2;
 y0 = (int)ydim/2;
        
 calcOutputDims(x0, y0, ptsX, ptsY, &w, &h, &i0, &j0);
 if (dataType== 1) mapImgByte(ptsReverse, xdim, ydim, w, h, argv[2], argv[3], i0, j0, x0, y0);
 if (dataType== 2) mapImgShort(ptsReverse, xdim, ydim, w, h, argv[2], argv[3], i0, j0, x0, y0);
 if (dataType== 3) mapImgLong(ptsReverse, xdim, ydim, w, h, argv[2], argv[3], i0, j0, x0, y0);
 if (dataType== 4) mapImgFloat(ptsReverse, xdim, ydim, w, h, argv[2], argv[3], i0, j0, x0, y0);
 if (dataType== 8) mapImgDouble(ptsReverse, xdim, ydim, w, h, argv[2], argv[3], i0, j0, x0, y0);	
 
 return (EXIT_SUCCESS);
	
}

void georeferenceUsage(){
 fprintf(stderr,"Usage: leaf -georeference infile outfile xdim gcpFile [bytesPerPixel]\n\n");
 fprintf(stderr, "   infile            Unregistered input image 1\n");
 fprintf(stderr, "   outfile           Georeferenced output image 2\n");   		
 fprintf(stderr, "   xdim              Number of pixels in x dimension\n");
 fprintf(stderr, "   gcpFile           Text file of GCP points\n");
 fprintf(stderr, "   dataType          1 char; 2 short; 3 long; 4 float; double 8\n\n");	
 exit(EXIT_FAILURE); 
}


double **runMatrixInverse(double *ptsX, double *ptsY, int n){
 
 double **A, **B;
 int i;
 A=allocateDoubleMatrix(n, n);
 
 for (i=0;i<n;i++){
  A[0][i]=ptsX[i];
  A[1][i]=ptsY[i];
 }
 
 A[2][0]=0.0;
 A[2][1]=0.0;
 A[2][2]=1.0;

 B=matrixInverse(A,n);

 return B;
}



int readGCPFile(char *gcpList, double **gcp, double *x, double *y){
 
 FILE *fin;
 char  *gcpfile;
 int i, j=0;

 int row=0;
 
 fin=openFile("",gcpList, "r");

 if((gcpfile = (char *) calloc(MAX_LINE_LEN, 1)) == NULL) memoryCheck();
 
 while(!feof(fin)){
  fgets(gcpfile, MAX_LINE_LEN, fin);
  sscanf(gcpfile+j,"%lf %lf %lf %lf",&gcp[row][0],&gcp[row][1],&x[row],&y[row]); 	
  row++; 
 }    
 
 fclose(fin);
 
 row=row-1;

 for (i=0;i<row;i++)
  gcp[i][2]=1.0;

/* for (i=0;i<row;i++)
  printf("%lf %lf %lf %lf %d\n",gcp[i][0],gcp[i][1],x[i],y[i],row);*/ 

 return row;

}

double *calcLeastSquaresGCP(double **X, double *y, int m){

 int n=3;
 double  *x;
  
 x=multipleLinearRegression(X,y,n,m);

/* for(i=0;i<n;i++) fprintf(stdout,"%f ",x[i]);
 fprintf(stdout,"\n"); */

 return x;

}

int calcOutputDims(int x0, int y0, double *ptsX, double *ptsY, int *w, int *h, int *i0, int *j0){

 int i, xp[4], yp[4], cx[4],cy[4];
 float xmin, ymin, xmax, ymax;
 
 cx[0]=0-x0;
 cx[1]=0-x0;
 cx[2]=x0;
 cx[3]=x0;

 cy[0]=0-y0;
 cy[1]=y0;
 cy[2]=0-y0;
 cy[3]=y0;
        
 for (i=0;i<4;i++){
  xp[i]=(int)round(ptsX[0] * cx[i] + ptsX[1] * cy[i] + ptsX[2] * 1.0);
  yp[i]=(int)round(ptsY[0] * cx[i] + ptsY[1] * cy[i] + ptsY[2] * 1.0);
 }
        
 xmin=xp[0];
 xmax=xp[0];
 ymin=yp[0];
 ymax=yp[0];

 for (i=1;i<4;i++){
  if (xp[i]<xmin) xmin=xp[i];
  if (xp[i]>xmax) xmax=xp[i];        
  if (yp[i]<ymin) ymin=yp[i];
  if (yp[i]>ymax) ymax=yp[i];       
 }
         
 *w = (int)round(xmax-xmin);
 *h = (int)round(ymax-ymin);

 *i0=(int)*w/2;
 *j0=(int)*h/2;
  
 return EXIT_SUCCESS;

}


int mapImgByte(double **pts, int xdim, int ydim, int w, int h, char *inImg, char *outImg, int i0, int j0, int x0, int y0){
 
 int i,j,ip,jp,x,y,bpp=1;
 unsigned char *in_img, *out_img;
 FILE *fin, *fout;
 
 fin  = openFile("", inImg, "rb");
 fout = openFile("", outImg, "wb");

 in_img  = (unsigned char *) malloc(xdim * ydim * bpp);
 out_img = (unsigned char *) malloc(w * h * bpp);
	
 for (i=0;i<w*h;i++)
  *(out_img + i) = 0;
	
 fread(in_img, bpp, xdim*ydim, fin);

 for (i = 0; i < w; i++){
  for (j = 0; j < h; j++){

   ip=i-i0; 
   jp=j0-j;             

   x=(int)round(pts[0][0] * ip + pts[1][0] * jp + pts[2][0] * 1.0);
   y=(int)round(pts[0][1] * ip + pts[1][1] * jp + pts[2][1] * 1.0);

   x=x+x0;
   y=y0-y;

 /*  printf("%d %d %d %d\n",x,y,i,j); */
   if (y>=0 && x>=0 && y<ydim && x<xdim)          
    *(out_img + i + j * w) = *(in_img + x + y * xdim); 
  }   			
 }
		
 fwrite(out_img, bpp, w * h, fout);
 	
 free(in_img);
 free(out_img);

 fclose(fin);
 fclose(fout);

 return EXIT_SUCCESS;
}


int mapImgShort(double **pts, int xdim, int ydim, int w, int h, char *inImg, char *outImg, int i0, int j0, int x0, int y0){
 
 int i,j,ip,jp,x,y,bpp=2;
 short *in_img, *out_img;
 FILE *fin, *fout;
 
 fin  = openFile("", inImg, "rb");
 fout = openFile("", outImg, "wb");

 in_img  = (short *) malloc(xdim * ydim * bpp);
 out_img = (short *) malloc(w * h * bpp);
	
 for (i=0;i<w*h;i++)
  *(out_img + i) = 0;
	
 fread(in_img, bpp, xdim*ydim, fin);

 for (i = 0; i < w; i++){
  for (j = 0; j < h; j++){

   ip=i-i0; 
   jp=j0-j;             

   x=(int)round(pts[0][0] * ip + pts[1][0] * jp + pts[2][0] * 1.0);
   y=(int)round(pts[0][1] * ip + pts[1][1] * jp + pts[2][1] * 1.0);

   x=x+x0;
   y=y0-y;

 /*  printf("%d %d %d %d\n",x,y,i,j); */
   if (y>=0 && x>=0 && y<ydim && x<xdim)          
    *(out_img + i + j * w) = *(in_img + x + y * xdim); 
  }   			
 }
		
 fwrite(out_img, bpp, w * h, fout);
 	
 free(in_img);
 free(out_img);

 fclose(fin);
 fclose(fout);

 return EXIT_SUCCESS;
}

int mapImgLong(double **pts, int xdim, int ydim, int w, int h, char *inImg, char *outImg, int i0, int j0, int x0, int y0){
 
 int i,j,ip,jp,x,y,bpp=4;
 long *in_img, *out_img;
 FILE *fin, *fout;
 
 fin  = openFile("", inImg, "rb");
 fout = openFile("", outImg, "wb");

 in_img  = (long *) malloc(xdim * ydim * bpp);
 out_img = (long *) malloc(w * h * bpp);
	
 for (i=0;i<w*h;i++)
  *(out_img + i) = 0;
	
 fread(in_img, bpp, xdim*ydim, fin);

 for (i = 0; i < w; i++){
  for (j = 0; j < h; j++){

   ip=i-i0; 
   jp=j0-j;             

   x=(int)round(pts[0][0] * ip + pts[1][0] * jp + pts[2][0] * 1.0);
   y=(int)round(pts[0][1] * ip + pts[1][1] * jp + pts[2][1] * 1.0);

   x=x+x0;
   y=y0-y;

 /*  printf("%d %d %d %d\n",x,y,i,j); */
   if (y>=0 && x>=0 && y<ydim && x<xdim)          
    *(out_img + i + j * w) = *(in_img + x + y * xdim); 
  }   			
 }
		
 fwrite(out_img, bpp, w * h, fout);
 	
 free(in_img);
 free(out_img);

 fclose(fin);
 fclose(fout);

 return EXIT_SUCCESS;
}

int mapImgFloat(double **pts, int xdim, int ydim, int w, int h, char *inImg, char *outImg, int i0, int j0, int x0, int y0){
 
 int i,j,ip,jp,x,y,bpp=4;
 float *in_img, *out_img;
 FILE *fin, *fout;
 
 fin  = openFile("", inImg, "rb");
 fout = openFile("", outImg, "wb");

 in_img  = (float *) malloc(xdim * ydim * bpp);
 out_img = (float *) malloc(w * h * bpp);
	
 for (i=0;i<w*h;i++)
  *(out_img + i) = 0;
	
 fread(in_img, bpp, xdim*ydim, fin);

 for (i = 0; i < w; i++){
  for (j = 0; j < h; j++){

   ip=i-i0; 
   jp=j0-j;             

   x=(int)round(pts[0][0] * ip + pts[1][0] * jp + pts[2][0] * 1.0);
   y=(int)round(pts[0][1] * ip + pts[1][1] * jp + pts[2][1] * 1.0);

   x=x+x0;
   y=y0-y;

 /*  printf("%d %d %d %d\n",x,y,i,j); */
   if (y>=0 && x>=0 && y<ydim && x<xdim)          
    *(out_img + i + j * w) = *(in_img + x + y * xdim); 
  }   			
 }
		
 fwrite(out_img, bpp, w * h, fout);
 	
 free(in_img);
 free(out_img);

 fclose(fin);
 fclose(fout);

 return EXIT_SUCCESS;
}

int mapImgDouble(double **pts, int xdim, int ydim, int w, int h, char *inImg, char *outImg, int i0, int j0, int x0, int y0){
 
 int i,j,ip,jp,x,y,bpp=8;
 double *in_img, *out_img;
 FILE *fin, *fout;
 
 fin  = openFile("", inImg, "rb");
 fout = openFile("", outImg, "wb");

 in_img  = (double *) malloc(xdim * ydim * bpp);
 out_img = (double *) malloc(w * h * bpp);
	
 for (i=0;i<w*h;i++)
  *(out_img + i) = 0;
	
 fread(in_img, bpp, xdim*ydim, fin);

 for (i = 0; i < w; i++){
  for (j = 0; j < h; j++){

   ip=i-i0; 
   jp=j0-j;             

   x=(int)round(pts[0][0] * ip + pts[1][0] * jp + pts[2][0] * 1.0);
   y=(int)round(pts[0][1] * ip + pts[1][1] * jp + pts[2][1] * 1.0);

   x=x+x0;
   y=y0-y;

 /*  printf("%d %d %d %d\n",x,y,i,j); */
   if (y>=0 && x>=0 && y<ydim && x<xdim)          
    *(out_img + i + j * w) = *(in_img + x + y * xdim); 
  }   			
 }
		
 fwrite(out_img, bpp, w * h, fout);
 	
 free(in_img);
 free(out_img);

 fclose(fin);
 fclose(fout);

 return EXIT_SUCCESS;
}

