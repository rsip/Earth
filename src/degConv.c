/*
NAME:		degConv.c 
DESCRIPTION: 	Convert between decimal degrees and degrees, minuts and seconds.
AUTHOR:	 	Will Grey
VERSION:	2015-11-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int degConv(int argc, char *argv[]){
 int deg, min, sec=0;
 float dec;
 if(argc < 3) degUsage();
	
 if (argc > 3) {
  
  deg = atoi(argv[2]);
  min = atoi(argv[3]);
  if (argc == 5) sec = atoi(argv[4]);
  if (deg > 0)
   fprintf(stdout,"%6.2f\n",(float)deg + (float)min / 60 + (float)sec / 3600 );
  else
   fprintf(stdout,"-%3.2f\n",((float)deg*-1.0) + (float)min / 60 + (float)sec / 3600 );	
 }
	
 if (argc == 3){ 
  dec = atof(argv[2]);
  deg = (int)dec;
  min = (int)((fabs(dec) - (int)fabs(dec)) * 60);
  sec = (int)((fabs(dec) - (int)fabs(dec)) * 3600) % 60;
  fprintf(stdout,"%d:%d:%d\n", deg, min, sec);
 }
 return (EXIT_SUCCESS);
}

void degUsage(){
 fprintf(stderr,"Usage: leaf -degConv <degrees> [minutes] [seconds]\n\n");
 exit(EXIT_FAILURE);
}


