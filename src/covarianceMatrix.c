/*
NAME:		covarianceMatrix.c 
DESCRIPTION: 	calculates the correlation and  
                covariance matrix between channels.
AUTHOR:	 	Will Grey
VERSION:	2015-11-22	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int covarianceMatrix(int argc, char **argv){
 
 metaData p;
 FILE *fin;
 
 if (argc < 3) covarianceUsage();	
 
 p.dataType = 1;
 p.channels = 1; 

 fin=openFile("",argv[2],"rb");
 if (argc >= 4) p.channels = atoi(argv[3]);
 if (argc == 5) p.dataType = atoi(argv[4]);
 p.bpp=dataType2bpp(p.dataType);
	
 getPixels(argv[2], &p);

 if (p.dataType == 1) covarianceByte (fin,&p);		
 if (p.dataType == 2) covarianceShort (fin,&p);	
 if (p.dataType == 3) covarianceLong (fin,&p);	
 if (p.dataType == 4) covarianceFloat (fin,&p);	
 if (p.dataType == 5) covarianceDouble (fin,&p);		
 
 fclose(fin);
 	
 return (EXIT_SUCCESS);
	
}

void covarianceUsage(){
 fprintf(stderr,"Usage: leaf -covariance inImg [channels] [bytesPerPixel]\n\n");
 fprintf(stderr, "   inImg           Input image                    \n");
 fprintf(stderr, "   channels        Number of channels             \n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n\n");
 exit(EXIT_FAILURE);
}

int covarianceByte (FILE *fin, metaData *p)
{

 unsigned char **inImg;
 int i, j;
 double **corr, **cov;

 inImg=allocateCharMatrix(p->pixels, p->channels);
 corr=allocateDoubleMatrix(p->channels, p->channels);
 cov=allocateDoubleMatrix(p->channels, p->channels);
 
 fread(inImg, p->bpp, p->pixels*p->channels, fin);
 
 for (j=0;j<p->channels;j++){
  for (i=0;i<p->channels;i++){ 
   if (j!=i){
    corr[i][j]=correlation((float *) inImg[i], (float *) inImg[j], p->channels);
    cov[i][j]=covariance((float *) inImg[i], (float *) inImg[j], p->channels);
   }
   else{
   corr[i][j]=1.0;
   cov[i][j]=1.0;
   }
  }
 }
 
 fprintf(stdout,"Correlation matrix\n");
 printCovCorr(corr,p->channels);
	
 fprintf(stdout,"Variance-covariance matrix\n");
 printCovCorr(cov,p->channels);	
 
 freeCharMatrix(inImg,p->channels);
 freeDoubleMatrix(corr,p->channels);
 freeDoubleMatrix(cov,p->channels);
 
 return (EXIT_SUCCESS);
}

int covarianceShort (FILE *fin, metaData *p)
{

 short **inImg;
 int i, j;
 double **corr, **cov;

 inImg=allocateShortMatrix(p->pixels, p->channels);
 corr=allocateDoubleMatrix(p->channels, p->channels);
 cov=allocateDoubleMatrix(p->channels, p->channels);

 fread(inImg, p->bpp, p->pixels*p->channels, fin);

 for (j=0;j<p->channels;j++){
  for (i=0;i<p->channels;i++){ 
   if (j!=i){
    corr[i][j]=correlation((float *)inImg[i], (float *)inImg[j], p->channels);
    cov[i][j]=covariance((float *)inImg[i], (float *)inImg[j], p->channels);
   }
   else{
   corr[i][j]=1.0;
   cov[i][j]=1.0;
   }
  }
 }
 
 fprintf(stdout,"Correlation matrix\n");
 printCovCorr(corr,p->channels);
	
 fprintf(stdout,"Variance-covariance matrix\n");
 printCovCorr(cov,p->channels);	
 
 freeShortMatrix(inImg,p->channels);
 freeDoubleMatrix(corr,p->channels);
 freeDoubleMatrix(cov,p->channels);
 
 return (EXIT_SUCCESS);
}

int covarianceLong (FILE *fin, metaData *p)
{

 long **inImg;
 int i, j;
 double **corr, **cov;

 inImg=allocateLongMatrix(p->pixels, p->channels);
 corr=allocateDoubleMatrix(p->channels, p->channels);
 cov=allocateDoubleMatrix(p->channels, p->channels);

 fread(inImg, p->bpp, p->pixels*p->channels, fin);

 for (j=0;j<p->channels;j++){
  for (i=0;i<p->channels;i++){ 
   if (j!=i){
    corr[i][j]=correlation((float *)inImg[i], (float *)inImg[j], p->channels);
    cov[i][j]=covariance((float *)inImg[i], (float *)inImg[j], p->channels);
   }
   else{
   corr[i][j]=1.0;
   cov[i][j]=1.0;
   }
  }
 }
 
 fprintf(stdout,"Correlation matrix\n");
 printCovCorr(corr,p->channels);
	
 fprintf(stdout,"Variance-covariance matrix\n");
 printCovCorr(cov,p->channels);	
 
 freeLongMatrix(inImg,p->channels);
 freeDoubleMatrix(corr,p->channels);
 freeDoubleMatrix(cov,p->channels);
 
 return (EXIT_SUCCESS);
}

int covarianceFloat (FILE *fin, metaData *p)
{

 float **inImg;
 int i, j;
 double **corr, **cov;

 inImg=allocateFloatMatrix(p->pixels, p->channels);
 corr=allocateDoubleMatrix(p->channels, p->channels);
 cov=allocateDoubleMatrix(p->channels, p->channels);

 fread(inImg, p->bpp, p->pixels*p->channels, fin);

 for (j=0;j<p->channels;j++){
  for (i=0;i<p->channels;i++){ 
   if (j!=i){
    corr[i][j]=correlation((float *)inImg[i], (float *)inImg[j], p->channels);
    cov[i][j]=covariance((float *)inImg[i], (float *)inImg[j], p->channels);
   }
   else{
   corr[i][j]=1.0;
   cov[i][j]=1.0;
   }
  }
 }
 
 fprintf(stdout,"Correlation matrix\n");
 printCovCorr(corr,p->channels);
	
 fprintf(stdout,"Variance-covariance matrix\n");
 printCovCorr(cov,p->channels);	
 
 freeFloatMatrix(inImg,p->channels);
 freeDoubleMatrix(corr,p->channels);
 freeDoubleMatrix(cov,p->channels);
 
 return (EXIT_SUCCESS);
}

int covarianceDouble(FILE *fin, metaData *p)
{

 double **inImg;
 int i, j;
 double **corr, **cov;

 inImg=allocateDoubleMatrix(p->pixels, p->channels);
 corr=allocateDoubleMatrix(p->channels, p->channels);
 cov=allocateDoubleMatrix(p->channels, p->channels);

 fread(inImg, p->bpp, p->pixels*p->channels, fin);

 for (j=0;j<p->channels;j++){
  for (i=0;i<p->channels;i++){ 
   if (j!=i){
    corr[i][j]=correlation((float *)inImg[i], (float *)inImg[j], p->channels);
    cov[i][j]=covariance((float *)inImg[i], (float *)inImg[j], p->channels);
   }
   else{
   corr[i][j]=1.0;
   cov[i][j]=1.0;
   }
  }
 }
 
 fprintf(stdout,"Correlation matrix\n");
 printCovCorr(corr,p->channels);
	
 fprintf(stdout,"Variance-covariance matrix\n");
 printCovCorr(cov,p->channels);	
 
 freeDoubleMatrix(inImg,p->channels);
 freeDoubleMatrix(corr,p->channels);
 freeDoubleMatrix(cov,p->channels);
 
 return (EXIT_SUCCESS);
}

int printCovCorr(double **c, int channels){

 int i,j; 

 for(j = 0; j < channels; j++)
  fprintf(stdout,"%d ",j );
 fprintf(stdout,"\n");
	
 for(i = 0; i < channels; i++){
  fprintf(stdout,"%d ",i );	
  for(j = 0; j < channels; j++)
   fprintf(stdout,"%f ",c[i][j]);	
  fprintf(stdout,"\n");					
 }

 return (EXIT_SUCCESS);
}

