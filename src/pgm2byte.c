/*
NAME:		pgm2byte.c 
DESCRIPTION: 	Converts from pgm to binary data
AUTHOR:	 	Will Grey
VERSION:	2015-11-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int pgm2byte(int argc, char *argv[]){
 
 int xdim, ydim, i, x;
 char magicNumber[MAGIC_NUM_LEN];
 FILE *fin, *fout;
 char *row;   			 
 char buffer[MAX_LINE_LEN];
 char *p;

 if (argc != 4) {
  fprintf(stderr,"Usage: earth -pgm2byte inImg outImg\n\n");
  fprintf(stderr, "  inImg           input pgm image\n");
  fprintf(stderr, "  outImg          output byte image\n\n"); 
  exit(EXIT_FAILURE);
 } 
 		
 fin  = openFile("", argv[2], "r");
 fout = openFile("", argv[3], "wb");
 fgets(magicNumber, MAX_LINE_LEN, fin);
 
  fgets(buffer, MAX_LINE_LEN, fin);

 sscanf(buffer,"%d %d",&xdim,&ydim);
 row = (char *) calloc(xdim,sizeof(char)); 
/* printf("%d %d\n",xdim,ydim); */
 
 if(strncmp(magicNumber,"P2",2)==0)   
  fgets(buffer, MAX_LINE_LEN, fin);   

 for (i=0;i<ydim;i++){
   
  fgets(buffer, MAX_LINE_LEN, fin);  
  x=0;
/*  if (i==120) printf("%s\n", buffer); */
  
  p = strtok(buffer," \t");
   
  while (p!=NULL){
   row[x]=atoi(p);
  /* if (i==120 && x<600) printf("%d %d\n",row[x],x); */
   p = strtok (NULL, "  \t");
   x++; 
   
  } 

  fwrite(row, sizeof(char), xdim, fout);  
 }

 fclose(fin);
 fclose(fout);
 
 return (EXIT_SUCCESS);
 	 
}			



