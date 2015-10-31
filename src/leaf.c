/*
NAME:		leaf.c 
DESCRIPTION: 	Basic image processing tool for
                Earth observation data
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int main(int argc, char **argv)
{

  clparse clinput; 
  readClinput(argc, argv, &clinput);    
  return(EXIT_SUCCESS);
}


void readClinput(int argc, char **argv, clparse *clinput){

 int i, t=0;
   
 clinput->flag=1;
 clinput->bpp=2;
 clinput->xdim=0;
 strcpy(clinput->routine, "");
 strcpy(clinput->infile, "");
 strcpy(clinput->outfile, OUTPUT_FILENAME);
 
 if (argc <= 1) {
  fprintf(stderr,"Usage: %s [options]\n",argv[0]);
  fprintf(stderr,"options:\n\n");
  fprintf(stderr," -flip -infile -xdim [-outfile -flag (left/right flip: 0 (default), up/down flip:1 ) -bpp]\n");  	
  fprintf(stderr," -swap infile [-outfile -bpp]\n");    
  exit(EXIT_FAILURE);
 }  
 
 for( i = 1; i < argc; i++ ){
  if(!strncasecmp(argv[ i ], "-infile",2) || !strncasecmp(argv[ i ], "--infile",3)){  
    checkOption(argv[ i ],"infile");     
   strcpy(clinput->infile, argv[++i]);
   if(!strcasecmp(clinput->outfile,OUTPUT_FILENAME)){ 
    strcpy(clinput->outfile, clinput->infile); 
    strcat(clinput->outfile,".out");
   } 
  }
  else if( !strncasecmp(argv[ i ], "-outfile",2) || !strncasecmp(argv[ i ], "--outfile",3)) 
   strcpy(clinput->outfile, argv[++i]);
  else if( !strncasecmp(argv[ i ], "-bpp",2) || !strncasecmp(argv[ i ], "--bpp",3))
   clinput->bpp= atoi(argv[++i]);
  else if( !strncasecmp(argv[ i ], "-xdim",2) || !strncasecmp(argv[ i ], "--xdim",3))
   clinput->xdim= atoi(argv[++i]);
  else if((!strncasecmp(argv[ i ], "-swap",2) || !strncasecmp(argv[ i ], "--swap",3)) && (t==0)){
   strcpy(clinput->routine, "swap"); 
   t=1;
  }
  else if((!strncasecmp(argv[ i ], "-flip",2) || !strncasecmp(argv[ i ], "--flip",3)) && (t==0)){
   strcpy(clinput->routine, "flip"); 
   t=1;
  }	       
 } 

 if (!strcasecmp(clinput->routine,"swap")) swap(clinput);
 if (!strcasecmp(clinput->routine,"flip")) flipImg(clinput);

 printf("%s\n", clinput->routine);
 printf("%s\n", clinput->infile);
 printf("%s\n", clinput->outfile);
 printf("%d\n", clinput->bpp);
 printf("%d\n", clinput->flag);
 printf("%d\n", clinput->xdim); 
}

int checkOption(char *arg, char *option){
 
 printf("%s",strcat("-",option));
 return 0;
/* return !strncasecmp(arg, strcat("-",option),2) || !strncasecmp(arg, strcat("--",option),3); */

}



