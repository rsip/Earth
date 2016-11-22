/*
NAME:		interpText.c 
DESCRIPTION: 	Perform linear interpolation on column on a text file
AUTHOR:	 	Will Grey
VERSION:	2015-12-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int interpText(int argc, char **argv){
 
 interp p;
 int cols;
 float fd[MAX_NUM_COLS][MAX_FILE_LINES];
 
 if (argc != 9) interpUsage();	

 p.startVal=atof(argv[4]);
 p.interval=atof(argv[5]);
 p.endVal=atof(argv[6]);
 p.cols=atoi(argv[7]);
 p.skip=atoi(argv[8]);
 
 readTextFile(&p.lines, &cols, fd, p.skip, argv[2]);
 
 fprintf(stdout,"cols: %d\n", cols);
 fprintf(stdout,"lines: %d\n", p.lines);

 interpolCol(&p, fd, argv[3]); 
 
 return (EXIT_SUCCESS); 
	
}


int interpolCol(interp *p, float fd[][MAX_FILE_LINES], char *outfile){

 int i,j,k;
 float val;
 FILE *ftext;

 ftext=openFile("",outfile,"w");	
 val=p->startVal;

 while (val<=p->endVal){
  fprintf(ftext,"%f ", val);

  k=-1;
  for (i=0;i<p->lines;i++){
   if ((val >= fd[0][i]) && (val < fd[0][i+1] )){
    k=i;
    break;
   }   
  }

  if (k>1)
   for (j=1;j<p->cols;j++)
    fprintf(ftext,"%f ",(val-fd[0][k])/(fd[0][k+1]-fd[0][k])*(fd[j][k+1]-fd[j][k])+fd[j][k]); 
 
  fprintf(ftext,"\n");
  val+=p->interval; 
 } 
  
 fclose(ftext);
 return (EXIT_SUCCESS);

}

int readTextFile(int *lines, int *cols, float fd[][MAX_FILE_LINES], int skip, char *infile){
 
 char buffer[MAX_LINE_LEN];
 char *p;
 int row=0, columns, i;
 FILE *f; 
 
 f=openFile("",infile,"r");	
 
 for (i=0;i<skip;i++) 
  fgets(buffer, MAX_LINE_LEN, f);

 while(fgets(buffer, MAX_LINE_LEN, f) !=NULL){
 
  columns=0;
  
   p = strtok(buffer," \t");
   
  while (p!=NULL){
   fd[columns][row]=atof(p);
  
   p = strtok (NULL, "  \t");
   columns++; 
   
  } 
  row++;  
 }   
 
 *lines=row;
 *cols=columns;
 
 fclose(f);
 return (EXIT_SUCCESS);
}



void interpUsage(){
 fprintf(stderr,"Usage: earth -interpText inFile outFile startVal interval endVal col skip\n\n");
 fprintf(stderr, "   inFile     Input text file\n");
 fprintf(stderr, "   outFile    Output text file\n");
 fprintf(stderr, "   startVal   Start Value\n");
 fprintf(stderr, "   interval   Interval \n");
 fprintf(stderr, "   endVal     End value\n");
 fprintf(stderr, "   cols       Number of columns to process\n");
 fprintf(stderr, "   skip       Skip lines at start of file\n\n");

 exit(EXIT_FAILURE); 
}

