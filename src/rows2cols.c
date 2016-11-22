/*
NAME:		rows2cols.c 
DESCRIPTION: 	Converts rows to columns in text files
AUTHOR:	 	Will Grey
VERSION:	2015-12-20	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int rows2cols(int argc, char *argv[]){
 
 int cols=0, rows=0, i, j;
 float rc[MAX_NUM_LINES][MAX_NUM_COLS]; 
 FILE *fin, *fout;   			 
 char buffer[MAX_LINE_LEN];
 char *p;

 if (argc != 4) {
  fprintf(stderr,"Usage: earth -rows2cols inImg outImg\n\n");
  fprintf(stderr, "  inImg           input text image\n");
  fprintf(stderr, "  outImg          output text image\n\n"); 
  exit(EXIT_FAILURE);
 } 
 		
 fin  = openFile("", argv[2], "r");
 fout = openFile("", argv[3], "w");
  
 while(fgets(buffer, MAX_LINE_LEN, fin) !=NULL){
  
  if (buffer[0] != '\n'){ 
   cols=0;
   p = strtok(buffer," \t");
   
   while (p!=NULL){
    rc[rows][cols]=atof(p); 
    p = strtok (NULL, "  \t");
    cols++; 
   } 
   rows++;
   } 
  }  
  
  for (i=0;i<cols;i++){ 
   for (j=0;j<rows;j++) 
    fprintf(fout, "%f\t", rc[j][i]);
   fprintf(fout,"\n");
 } 


 fclose(fin);
 fclose(fout); 
 
 return (EXIT_SUCCESS);
 	 
}			



