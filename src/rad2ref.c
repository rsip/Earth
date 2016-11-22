/*
NAME:		rad2ref.c 
DESCRIPTION: 	Convert from radiance values to reflectance
AUTHOR:	 	Will Grey
VERSION:	2015-12-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int rad2ref(int argc, char **argv){
 
 metaData p;
 FILE *fin, *fout, *fsza, *ftext;
 float *irrad, scale=1.0;
 
 if (argc < 6) rad2refUsage();	
	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[4],"wb");
 fsza=openFile("",argv[3],"wb");	
 ftext=openFile("",argv[5], "r");

 p.dataType=4;
 p.channels=1;

 if (argc >=7) p.dataType = atoi(argv[6]);
 if (argc >=8) p.channels = atoi(argv[7]);
 if (argc ==9) scale=atof(argv[8]);
 
 getPixels(argv[2], &p);
 
 if((irrad = (float *) calloc(p.channels, sizeof(float))) == NULL) memoryCheck(); 
 readIrradianceFile(ftext,irrad,p.channels);	

 if (p.dataType == 1) rad2refByte(fin,fout, fsza, &p,irrad,scale);
 if (p.dataType == 2) rad2refShort(fin,fout, fsza, &p,irrad,scale);
 if (p.dataType == 3) rad2refLong(fin,fout, fsza, &p,irrad,scale);
 if (p.dataType == 4) rad2refFloat(fin,fout, fsza, &p,irrad,scale);
 if (p.dataType == 8) rad2refDouble(fin,fout, fsza, &p,irrad,scale);
	
 fclose(fin);
 fclose(fout);
 fclose(ftext);
 fclose(fsza);
	
 return (EXIT_SUCCESS);
	
}

void rad2refUsage(){
 fprintf(stderr,"Usage: earth -rad2ref inImg outImg szaImg irradianceFile [dataType] [channels] [scale]\n\n");
 fprintf(stderr, "   inImg          input radiance image \n");
 fprintf(stderr, "   szaImg         input solar zenith angle image for each pixel\n");
 fprintf(stderr, "   outImg         output reflectance image \n");
 fprintf(stderr, "   irradianceFile Text file of solar irrandiance values for each band \n");	   		
 fprintf(stderr, "   dataType       1: byte (default), 2: short, 3: long, 4: float, 8: Double\n");
 fprintf(stderr, "   channels       Number of channels  \n");
 fprintf(stderr, "   scale          Scale value if required default=1.0   \n\n");
 exit(EXIT_FAILURE);
}

int readIrradianceFile(FILE *ftext, float *irrad, int channels){

 int row=0;
 char *buffer;

 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext) !=NULL){
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",&irrad[row]);
   row++;
  }
 } 

 if (row !=channels){
  fprintf(stderr, "rad2ref: Incorrect number of bands in file\n");
  exit(EXIT_FAILURE);
 }
 
 free(buffer);
 
 return (EXIT_SUCCESS);

}

int rad2refByte(FILE *fin, FILE *fout, FILE *fsza, metaData *p, float *irrad, float scale){

 unsigned char *inImg;
 float *outImg;
 float *szaImg;
 int x,i;
	
 if((inImg  = (unsigned char *) calloc(p->pixels,sizeof(char)))== NULL) memoryCheck();
 if((szaImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 
 for (i=0;i<p->channels;i++){
  fread(inImg,sizeof(char),p->pixels,fin);
  fread(szaImg,sizeof(float),p->pixels,fin);
  
  for(x = 0; x < p->pixels; x++)
   *(outImg + x) = irrad[i] * (float)*(inImg + x) * scale * cos(*(szaImg + x)) / PI;

 }
						 
 fwrite(outImg,sizeof(float),p->pixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}


int rad2refShort(FILE *fin, FILE *fout, FILE *fsza, metaData *p, float *irrad, float scale){

 short *inImg;
 float *outImg;
 float *szaImg;
 int x,i;
	
 if((inImg  = (short *) calloc(p->pixels,sizeof(short)))== NULL) memoryCheck();
 if((szaImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 
 for (i=0;i<p->channels;i++){
  fread(inImg,sizeof(short),p->pixels,fin);
  fread(szaImg,sizeof(float),p->pixels,fin);
  
  for(x = 0; x < p->pixels; x++)
   *(outImg + x) = irrad[i] * (float)*(inImg + x) * scale * cos(*(szaImg + x)) / PI;

 }
						 
 fwrite(outImg,sizeof(float),p->pixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int rad2refLong(FILE *fin, FILE *fout, FILE *fsza, metaData *p, float *irrad, float scale){

 long *inImg;
 float *outImg;
 float *szaImg;
 int x,i;
	
 if((inImg  = (long *) calloc(p->pixels,sizeof(long)))== NULL) memoryCheck();
 if((szaImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 
 for (i=0;i<p->channels;i++){
  fread(inImg,sizeof(long),p->pixels,fin);
  fread(szaImg,sizeof(float),p->pixels,fin);
  
  for(x = 0; x < p->pixels; x++)
   *(outImg + x) = irrad[i] * (float)*(inImg + x) * scale * cos(*(szaImg + x)) / PI;

 }
						 
 fwrite(outImg,sizeof(float),p->pixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}


int rad2refDouble(FILE *fin, FILE *fout, FILE *fsza, metaData *p, float *irrad, float scale){

 double *inImg;
 float *outImg;
 float *szaImg;
 int x,i;
	
 if((inImg  = (double *) calloc(p->pixels,sizeof(double)))== NULL) memoryCheck();
 if((szaImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 
 for (i=0;i<p->channels;i++){
  fread(inImg,sizeof(double),p->pixels,fin);
  fread(szaImg,sizeof(float),p->pixels,fin);
  
  for(x = 0; x < p->pixels; x++)
   *(outImg + x) = irrad[i] * (float)*(inImg + x) * scale * cos(*(szaImg + x)) / PI;

 }
						 
 fwrite(outImg,sizeof(float),p->pixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

int rad2refFloat(FILE *fin, FILE *fout, FILE *fsza, metaData *p, float *irrad, float scale){

 float *inImg;
 float *outImg;
 float *szaImg;
 int x,i;
	
 if((inImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();
 if((szaImg  = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 if((outImg = (float *) calloc(p->pixels,sizeof(float)))== NULL) memoryCheck();	
 
 for (i=0;i<p->channels;i++){
  fread(inImg,sizeof(float),p->pixels,fin);
  fread(szaImg,sizeof(float),p->pixels,fin);
  
  for(x = 0; x < p->pixels; x++)
   *(outImg + x) = irrad[i] * *(inImg + x) * scale * cos(*(szaImg + x)) / PI;

 }
						 
 fwrite(outImg,sizeof(float),p->pixels,fout);
	
 free(inImg);
 free(outImg);
	
 return (EXIT_SUCCESS);

}

