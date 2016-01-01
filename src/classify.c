/*
NAME:		classify.c 
DESCRIPTION: 	Classiy images using basic box classifier.
AUTHOR:	 	Will Grey
VERSION:	2015-11-28	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int classify(int argc, char **argv){
 
 FILE *fin, *fout, *ftext;
 metaData p;
 float class[2][NUM_CLASSES][MAX_NUM_CHANNELS];
 int classes, channels;
 
 if (argc != 7) classifyUsage();	
 	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");
 ftext=openFile("",argv[4],"wb");	
 p.channels=atoi(argv[5]);
 p.classes=atoi(argv[6]);
 p.dataType=atoi(argv[7]);
 
 getPixels(argv[2],&p);
 p.bpp=dataType2bpp(p.dataType);
	
 readClassFile(fin,&classes,&channels,class); 
 
 if (classes !=p.classes || p.channels !=channels){
  fprintf(stderr, "Incorrect number of classes or channels in classification text file.\n");  	 
  exit(EXIT_FAILURE);
 }

 if (p.dataType == 1) classifyByte (fin,fout,&p,class);		
 if (p.dataType == 2) classifyShort (fin,fout,&p,class);	
 if (p.dataType == 3) classifyLong (fin,fout,&p,class);	
 if (p.dataType == 4) classifyFloat (fin,fout,&p,class);	
 if (p.dataType == 5) classifyDouble (fin,fout,&p,class);	
		
 fclose(fin);
 fclose(fout);
 fclose(ftext);	
 return (EXIT_SUCCESS);
	
}


int classifyFloat(FILE *fin, FILE *fout, metaData *p, float class[][NUM_CLASSES][MAX_NUM_CHANNELS]){	
 
 unsigned int i,j,k,l;
 float *inImg;
 unsigned char *outImg;
	
 if((inImg  = (float *) calloc(p->pixels*p->channels, sizeof(float))) == NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(p->pixels, sizeof(char))) == NULL) memoryCheck();

 fread(inImg,p->bpp,p->pixels*p->channels,fin);
 
  for (j=0;j<p->pixels;j++){ 
   for (i=0;i<p->classes;i++){
     l=0;
     for (k=0;k<p->channels;k++){
      if (*(inImg + p->pixels * k + j) >= class[0][i][k] && *(inImg + p->pixels * k + j) < class[1][i][k]) l++;
    }
    if (l==p->channels) *(outImg + j) = i;
   }
  }
 
 fwrite(outImg, sizeof(char), p->pixels, fout);
	
 free(inImg);
 free(outImg);
	
 return(EXIT_SUCCESS);

}


int classifyByte(FILE *fin, FILE *fout, metaData *p, float class[][NUM_CLASSES][MAX_NUM_CHANNELS]){	
 
 unsigned int i,j,k,l;
 unsigned char *inImg;
 unsigned char *outImg;
	
 if((inImg  = (unsigned char *) calloc(p->pixels*p->channels, sizeof(char))) == NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(p->pixels, sizeof(char))) == NULL) memoryCheck();

 fread(inImg,p->bpp,p->pixels*p->channels,fin);
 
  for (j=0;j<p->pixels;j++){ 
   for (i=0;i<p->classes;i++){
     l=0;
     for (k=0;k<p->channels;k++){
      if ((float)*(inImg + p->pixels * k + j) >= class[0][i][k] && (float)*(inImg + p->pixels * k + j) < class[1][i][k]) l++;
    }
    if (l==p->channels) *(outImg + j) = i;
   }
  }
 
 fwrite(outImg, sizeof(char), p->pixels, fout);
	
 free(inImg);
 free(outImg);
	
 return(EXIT_SUCCESS);

}


int classifyShort(FILE *fin, FILE *fout, metaData *p, float class[][NUM_CLASSES][MAX_NUM_CHANNELS]){	
 
 unsigned int i,j,k,l;
 short *inImg;
 unsigned char *outImg;
	
 if((inImg  = (short *) calloc(p->pixels*p->channels, sizeof(short))) == NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(p->pixels, sizeof(char))) == NULL) memoryCheck();

 fread(inImg,p->bpp,p->pixels*p->channels,fin);
 
  for (j=0;j<p->pixels;j++){ 
   for (i=0;i<p->classes;i++){
     l=0;
     for (k=0;k<p->channels;k++){
      if ((float)*(inImg + p->pixels * k + j) >= class[0][i][k] && (float)*(inImg + p->pixels * k + j) < class[1][i][k]) l++;
    }
    if (l==p->channels) *(outImg + j) = i;
   }
  }
 
 fwrite(outImg, sizeof(char), p->pixels, fout);
	
 free(inImg);
 free(outImg);
	
 return(EXIT_SUCCESS);

}

int classifyLong(FILE *fin, FILE *fout, metaData *p, float class[][NUM_CLASSES][MAX_NUM_CHANNELS]){	
 
 unsigned int i,j,k,l;
 long *inImg;
 unsigned char *outImg;
	
 if((inImg  = (long *) calloc(p->pixels*p->channels, sizeof(long))) == NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(p->pixels, sizeof(char))) == NULL) memoryCheck();

 fread(inImg,p->bpp,p->pixels*p->channels,fin);
 
  for (j=0;j<p->pixels;j++){ 
   for (i=0;i<p->classes;i++){
     l=0;
     for (k=0;k<p->channels;k++){
      if ((float)*(inImg + p->pixels * k + j) >= class[0][i][k] && (float)*(inImg + p->pixels * k + j) < class[1][i][k]) l++;
    }
    if (l==p->channels) *(outImg + j) = i;
   }
  }
 
 fwrite(outImg, sizeof(char), p->pixels, fout);
	
 free(inImg);
 free(outImg);
	
 return(EXIT_SUCCESS);

}

int classifyDouble(FILE *fin, FILE *fout, metaData *p, float class[][NUM_CLASSES][MAX_NUM_CHANNELS]){	
 
 unsigned int i,j,k,l;
 double *inImg;
 unsigned char *outImg;
	
 if((inImg  = (double *) calloc(p->pixels*p->channels, sizeof(double))) == NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(p->pixels, sizeof(char))) == NULL) memoryCheck();

 fread(inImg,p->bpp,p->pixels*p->channels,fin);
 
  for (j=0;j<p->pixels;j++){ 
   for (i=0;i<p->classes;i++){
     l=0;
     for (k=0;k<p->channels;k++){
      if (*(inImg + p->pixels * k + j) >= class[0][i][k] && *(inImg + p->pixels * k + j) < class[1][i][k]) l++;
    }
    if (l==p->channels) *(outImg + j) = i;
   }
  }
 
 fwrite(outImg, sizeof(char), p->pixels, fout);
	
 free(inImg);
 free(outImg);
	
 return(EXIT_SUCCESS);

}



void classifyUsage(){
 fprintf(stderr,"Usage: leaf -classify inImg outImg inputTextFile channels classes\n\n");
 fprintf(stderr, "   inImg           Input image\n");
 fprintf(stderr, "   outImg          Output image (byte)\n");
 fprintf(stderr, "   inputTextFile   Input class file\n");
 fprintf(stderr, "   dataType        1: byte (default), 2: short, 3: long, 4: float, 8: Double \n");
 fprintf(stderr, "   channels        Number of channels\n");
 fprintf(stderr, "   classes         Number of classes\n\n");  	 
 exit(EXIT_FAILURE); 
}

int readClassFile(FILE *f, int *classes2, int *channels2, float class[][NUM_CLASSES][MAX_NUM_CHANNELS]){
 
 char buffer[2000];
 int i;
 char *p;
 int classes, channels; 
 
 channels=0;

 while(fgets(buffer, 2000, f) !=NULL){
 
  classes=0;
  
  if (buffer[0] != '\n'){
 
   p = strtok(buffer," \t");
   i=0;
   
  while (p!=NULL){
  class[i][classes][channels]=atof(p);
  
   p = strtok (NULL, "  \t"); 
   
   if (i==0)i=1;
   else if (i==1) i=0;
   if (i==0) classes++; 
  } 

  channels++; 
 } 
  
 }   
 
 *classes2=classes;
 *channels2=channels;

 return (EXIT_SUCCESS);
}

