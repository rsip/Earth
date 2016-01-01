/*
NAME:		bsq2dimap.c 
DESCRIPTION: 	Convert from bsq to dimap format
AUTHOR:	 	Will Grey
VERSION:	2015-11-19	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int bsq2dimap(int argc, char **argv){
 
 metaData hdrData;
 FILE *fin, **fout;
 struct stat size;
 struct stat st = {0};    

 hdrData.channels = 3;

 if (argc < 4)  bsq2dimapUsage();	

 fin=openFile("",argv[2],"rb");
 
 if (stat(argv[3], &st) == -1)
  mkdir(argv[3], 0700);
 
 if (argc==5) hdrData.channels = atoi(argv[4]);
	
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 hdrData.pixels = size.st_size / hdrData.channels;

 fout=openMultipleWriteFiles(hdrData.channels, argv[3], argv[2]);
 splitFile(fin, fout, &hdrData);	

 return (EXIT_SUCCESS);

}

FILE ** openMultipleWriteFiles(int channels, char *path, char *name){

 FILE **f;
 int i; 
 char filename[TEXT_LINE_LEN];	
 strcat(path,"/");

 if((f = malloc (sizeof(FILE *) * channels)) == NULL) memoryCheck();
 
 for (i=0;i<channels;i++){
  strcpy(filename,name);
  strcat(filename,"-channel-");
  strcat(filename,itoa(i+1));
  f[i]  = openFile(path, filename,  "wb");

 }
 return f;
}

void bsq2dimapUsage(){
 fprintf(stderr,"Usage: leaf -bsq2dimap infile outdir [channels] \n\n");
 fprintf(stderr, "   infile          input image\n");
 fprintf(stderr, "   outdir          output directory \n");   		
 fprintf(stderr, "   [channels]      default = 3\n\n");
 exit(EXIT_FAILURE);
}

int splitFile(FILE *fin, FILE **fout, metaData *hdrData){

 char *img;
 int i;
 
 if((img  = (char *) calloc(hdrData->pixels,sizeof(char)))== NULL) memoryCheck();	
 
 for (i=0;i<hdrData->channels;i++){
  fread(img,sizeof(char),hdrData->pixels,fin);
  fwrite(img,sizeof(char),hdrData->pixels,fout[i]);
 }

 free(img);

 return (EXIT_SUCCESS);

}

