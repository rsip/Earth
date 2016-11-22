/*
NAME:		regression.c 
DESCRIPTION: 	Calculates the regression of two images
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int regress(int argc, char **argv)
{
  
 FILE *fin1, *fin2, *fout;
 struct stat size1, size2; 
 metaData p;

 p.dataType=1;
 if (argc < 4) regressionUsage();	 

 strcpy(p.infile, argv[2]);
 strcpy(p.infile2, argv[3]);
 strcpy(p.outfile, argv[4]);

 if (argc >=6){ 
  strcpy(p.outfile,argv[ 5 ]); 
 }
 else{
  strcpy(p.outfile, p.infile);
  strcat(p.outfile, "-"); 
  strcat(p.outfile, p.infile2); 
  strcat(p.outfile,".out");
 }

 if(argc == 6) p.dataType = atoi(argv[5]);
	
 fin1=openFile("",p.infile,"rb");
 fin2=openFile("",p.infile2,"rb");
 fout=openFile("",p.outfile,"wb");	

 if (stat(argv[2], &size1) == -1) fileReadError(argv[2]);
 if (stat(argv[3], &size2) == -1) fileReadError(argv[3]);
 if (size1.st_size != size2.st_size)fileSizeErr(argv[2],argv[3]);

 p.bpp=dataType2bpp(p.dataType);

 p.pixels = size1.st_size / p.bpp;
 		
 if (p.dataType == 1) regressionByte(fin1,fin2,fout,p.pixels);
 if (p.dataType == 2) regressionShort(fin1,fin2,fout,p.pixels);
 if (p.dataType == 3) regressionLong(fin1,fin2,fout,p.pixels);
 if (p.dataType == 4) regressionFloat(fin1,fin2,fout,p.pixels);
 if (p.dataType == 8) regressionDouble(fin1,fin2,fout,p.pixels);
	
 fclose(fin1);
 fclose(fin2);
 fclose(fout);
	
 return (EXIT_SUCCESS);
	
}

void regressionUsage(){
 fprintf(stderr,"Usage: earth -regression infile1 infile2 [outfile] [dataType] \n\n");
 fprintf(stderr, "   infile1          input image 1\n");
 fprintf(stderr, "   infile2          input image 2\n");
 fprintf(stderr, "   outfile          output image\n");	   		
 fprintf(stderr, "   data_type        1: byte (default), 2: short, 3: long, 4: float, 8: Double\n\n");
 exit(EXIT_FAILURE);
}

int regressionByte (FILE *fin1, FILE *fin2, FILE *fout, int pixels)
{	
 unsigned char *inImg1, *inImg2;
 float *outImg;
 int j;
 float Ey, Ay;
 regressionCoefficients coeffs;	
 
 if((inImg1  = (unsigned char *) calloc(pixels,sizeof(char)))== NULL) memoryCheck();	
 if((inImg2  = (unsigned char *) calloc(pixels,sizeof(char)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(pixels,sizeof(float)))== NULL) memoryCheck();	
 
 fread(inImg1,sizeof(char),pixels,fin1);
 fread(inImg2,sizeof(char),pixels,fin2);

 coeffs=regression((float *)inImg1,(float *)inImg2, pixels);

 fprintf(stdout, "\n intercept:    %f", coeffs.c);
 fprintf(stdout, "\n gradient:     %f\n", coeffs.m); 

 for(j=0; j<pixels; j++){											
  Ey = coeffs.m * (float)inImg1[j] + coeffs.c;
  Ay = (float)inImg2[j];
  outImg[j] = Ay - Ey;
 }	
	
 fwrite(outImg,sizeof(float),pixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int regressionShort (FILE *fin1, FILE *fin2, FILE *fout, int pixels)
{	
 short *inImg1, *inImg2;
 float *outImg;
 int j;
 float Ey, Ay;
 regressionCoefficients coeffs;	
 
 if((inImg1  = (short *) calloc(pixels,sizeof(short)))== NULL) memoryCheck();	
 if((inImg2  = (short *) calloc(pixels,sizeof(short)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(pixels,sizeof(float)))== NULL) memoryCheck();	
 
 fread(inImg1,sizeof(short),pixels,fin1);
 fread(inImg2,sizeof(short),pixels,fin2);

 coeffs=regression((float *)inImg1,(float *)inImg2, pixels);

 fprintf(stdout, "\n intercept:    %f", coeffs.c);
 fprintf(stdout, "\n gradient:     %f\n", coeffs.m); 

 for(j=0; j<pixels; j++){											
  Ey = coeffs.m * (float)inImg1[j] + coeffs.c;
  Ay = (float)inImg2[j];
  outImg[j] = Ay - Ey;
 }	
	
 fwrite(outImg,sizeof(float),pixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int regressionLong (FILE *fin1, FILE *fin2, FILE *fout, int pixels)
{	
 long *inImg1, *inImg2;
 float *outImg;
 int j;
 float Ey, Ay;
 regressionCoefficients coeffs;	
 
 if((inImg1  = (long *) calloc(pixels,sizeof(long)))== NULL) memoryCheck();	
 if((inImg2  = (long *) calloc(pixels,sizeof(long)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(pixels,sizeof(float)))== NULL) memoryCheck();	
 
 fread(inImg1,sizeof(long),pixels,fin1);
 fread(inImg2,sizeof(long),pixels,fin2);

 coeffs=regression((float *)inImg1,(float *)inImg2, pixels);

 fprintf(stdout, "\n intercept:    %f", coeffs.c);
 fprintf(stdout, "\n gradient:     %f\n", coeffs.m); 

 for(j=0; j<pixels; j++){											
  Ey = coeffs.m * (float)inImg1[j] + coeffs.c;
  Ay = (float)inImg2[j];
  outImg[j] = Ay - Ey;
 }	
	
 fwrite(outImg,sizeof(float),pixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int regressionFloat (FILE *fin1, FILE *fin2, FILE *fout, int pixels){	
 float *inImg1, *inImg2, *outImg;
 int j;
 float Ey, Ay;
 regressionCoefficients coeffs;	
 
 if((inImg1  = (float *) calloc(pixels,sizeof(float)))== NULL) memoryCheck();	
 if((inImg2  = (float *) calloc(pixels,sizeof(float)))== NULL) memoryCheck();
 if((outImg = (float *) calloc(pixels,sizeof(float)))== NULL) memoryCheck();	
 
 fread(inImg1,sizeof(float),pixels,fin1);
 fread(inImg2,sizeof(float),pixels,fin2);

 coeffs=regression((float *)inImg1,(float *)inImg2, pixels);

 fprintf(stdout, "\n intercept:    %f", coeffs.c);
 fprintf(stdout, "\n gradient:     %f\n", coeffs.m); 

 for(j=0; j<pixels; j++){											
  Ey = coeffs.m * (float)inImg1[j] + coeffs.c;
  Ay = (float)inImg2[j];
  outImg[j] = Ay - Ey;
 }	
	
 fwrite(outImg,sizeof(float),pixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

int regressionDouble (FILE *fin1, FILE *fin2, FILE *fout, int pixels){	
 
 double *inImg1, *inImg2, *outImg;
 int j;
 double Ey, Ay;
 regressionCoefficients coeffs;	
 
 if((inImg1  = (double *) calloc(pixels,sizeof(double)))== NULL) memoryCheck();	
 if((inImg2  = (double *) calloc(pixels,sizeof(double)))== NULL) memoryCheck();
 if((outImg = (double *) calloc(pixels,sizeof(double)))== NULL) memoryCheck();	
 
 fread(inImg1,sizeof(double),pixels,fin1);
 fread(inImg2,sizeof(double),pixels,fin2);

 coeffs=regression((float *)inImg1,(float *)inImg2, pixels);

 fprintf(stdout, "\n intercept:    %f", coeffs.c);
 fprintf(stdout, "\n gradient:     %f\n", coeffs.m); 

 for(j=0; j<pixels; j++){											
  Ey = coeffs.m * inImg1[j] + coeffs.c;
  Ay = inImg2[j];
  outImg[j] = Ay - Ey;
 }	
	
 fwrite(outImg,sizeof(double),pixels,fout);
	
 free(inImg1);
 free(inImg2);
 free(outImg);
	
 return (EXIT_SUCCESS);
}

