/*
NAME:		rotate.c 
DESCRIPTION: 	Rotate images
AUTHOR:	 	Will Grey
VERSION:	2015-11-24	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int rotate(int argc, char *argv[]){

 metaData p;
 int x0, y0, w, h, i0, j0;
 float cosAng, sinAng, angle=90;
 FILE *fin, *fout;
		
 if (argc < 5) rotateUsage();
 p.channels = 1;
 p.bpp = 1;
	
 p.xdim = atoi(argv[4]);	
 if(argc >= 6) angle = atof(argv[5]);
 if(argc >= 7) p.bpp = atoi(argv[6]);
 if(argc == 8) p.channels = atoi(argv[7]);
 
 getYdim(argv[2], &p);	
 
 fin  = openFile("", argv[2], "rb");
 fout = openFile("", argv[3], "wb");

 cosAng=cos(angle*PI/180.0);
 sinAng=sin(angle*PI/180.0);
        			
 x0 = (int)p.xdim/2;
 y0 = (int)p.ydim/2;
 
 if((angle <=  90 + ANGLE_TOL) &&  (angle >=  90 - ANGLE_TOL)) 
  rotate90(fin,fout, &p);
 else if((angle <= 180 + ANGLE_TOL) &&  (angle >= 180 - ANGLE_TOL)) 
  rotate180(fin,fout, &p);
 else if((angle <= 270 + ANGLE_TOL) &&  (angle >= 270 - ANGLE_TOL)) 
  rotate270(fin,fout, &p);
 else{
  calcOutputDimsRotate(x0, y0, cosAng, sinAng, &w, &h, &i0, &j0);
  mapImg(cosAng, sinAng, p.xdim, p.ydim, w, h, fin, fout, i0, j0, x0, y0, p.bpp);
 }


 fclose(fin);
 fclose(fout);
 	
 return (EXIT_SUCCESS);
	
}

int rotate90(FILE *fin, FILE *fout, metaData *p){

 unsigned char *inImg, *outImg;
 int x, y, i, j;
 
 inImg  = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 outImg = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 fread(inImg, p->bpp, p->xdim*p->ydim, fin);
 
 for (j = 0; j < p->channels; j++){
  for (y = 0; y < p->ydim; y++)
   for (x = 0; x < p->xdim; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + (j * p->ydim * p->xdim * p->bpp) + y * p->bpp + (p->xdim - x - 1) * p->ydim * p->bpp + i) 
     = *(inImg + (j * p->ydim * p->xdim * p->bpp) + x * p->bpp + y * p->xdim * p->bpp + i);
  
   fwrite(outImg, p->bpp, p->xdim*p->ydim, fout);
  }

 free(inImg);
 free(outImg);
 return EXIT_SUCCESS;
}

int rotate180(FILE *fin, FILE *fout, metaData *p){

 unsigned char *inImg, *outImg;
 int x, y, i, j;
 
 inImg  = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 outImg = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 fread(inImg, p->bpp, p->xdim*p->ydim, fin);
 
 for (j = 0; j < p->channels; j++){
  for (y = 0; y < p->ydim; y++)
   for (x = 0; x < p->xdim; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + (j * p->ydim * p->xdim * p->bpp) + (p->xdim - x - 1) * p->bpp +  (p->ydim - y - 1) * p->ydim * p->bpp + i) 
     = *(inImg + (j * p->ydim * p->xdim * p->bpp) + x * p->bpp + y * p->xdim * p->bpp + i);
  
  fwrite(outImg, p->bpp, p->xdim*p->ydim, fout);
 } 


 free(inImg);
 free(outImg);
 return EXIT_SUCCESS;
}


int rotate270(FILE *fin, FILE *fout, metaData *p){

 unsigned char *inImg, *outImg;
 int x, y, i, j;
 
 inImg  = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 outImg = (unsigned char *) malloc(p->xdim * p->ydim * p->bpp);
 fread(inImg, p->bpp, p->xdim*p->ydim, fin);

 for (j = 0; j < p->channels; j++){
  for (y = 0; y < p->ydim; y++)
   for (x = 0; x < p->xdim; x++) 
    for (i=0;i<p->bpp;i++)
     *(outImg + (j * p->ydim * p->xdim * p->bpp) + (p->ydim - y - 1) * p->bpp + x * p->ydim * p->bpp + i) 
     = *(inImg + (j * p->ydim * p->xdim * p->bpp) + x * p->bpp + y * p->xdim * p->bpp + i);
  
  fwrite(outImg, p->bpp, p->xdim*p->ydim, fout);
 }

 free(inImg);
 free(outImg);
 return EXIT_SUCCESS;
}

int mapImg(float cosAng, float sinAng, int xdim, int ydim, int w, int h, FILE *fin, FILE *fout, int i0, int j0, int x0, int y0, int bpp){
 
 int i,j,ip,jp,x,y,k;
 unsigned char *inImg, *outImg;
 
 inImg  = (unsigned char *) malloc(xdim * ydim * bpp);
 outImg = (unsigned char *) malloc(w * h * bpp);
	
 for (i=0;i<w*h;i++)
  *(outImg + i) = 0;
	
 fread(inImg, bpp, xdim*ydim, fin);

 for (i = 0; i < w; i++){
  for (j = 0; j < h; j++){

   ip=i-i0; 
   jp=j0-j;             

   x = (int)round((cosAng * (ip) + sinAng * (jp)));
   y = (int)round((cosAng * (jp) - sinAng * (ip)));

   x=x+x0;
   y=y0-y;

 /*  printf("%d %d %d %d\n",x,y,i,j); */
   if (y>=0 && x>=0 && y<ydim && x<xdim)
    for(k=0;k<bpp;k++)          
    *(outImg + i + j * w + k) = *(inImg + x + y * xdim + k); 
  }   			
 }
		
 fwrite(outImg, bpp, w * h, fout);
 	
 free(inImg);
 free(outImg);

 return EXIT_SUCCESS;
}


int calcOutputDimsRotate(int x0, int y0, float cosAng, float sinAng, int *w, int *h, int *i0, int *j0){

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
  xp[i]=(int)round(cosAng * cx[i] - sinAng * cy[i]);
  yp[i]=(int)round(cosAng * cx[i] + sinAng * cy[i]);
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
 
 fprintf(stdout,"OutputImageWidth: %d\n",*w); 
 fprintf(stdout,"OutputImageHeight: %d\n\n",*h); 

 return EXIT_SUCCESS;

}

void rotateUsage(){
 fprintf(stderr,"Usage: earth -rotate infile outfile xdim [angle] [bpp] [channels]\n\n");
 fprintf(stderr, "   infile          input image 1\n");
 fprintf(stderr, "   outfile         output image\n");
 fprintf(stderr, "   angle           angle of rotation\n");	   		
 fprintf(stderr, "   bpp             Bytes per pixel\n");
 fprintf(stderr, "   channels        Number of channels\n\n");
 exit(EXIT_FAILURE);
}

