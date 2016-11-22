/*
NAME:		separability.c 
DESCRIPTION: 	Calculate separability between classes for any number of channels
AUTHOR:	 	Will Grey
VERSION:	2015-12-02	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"


int i[MAX_NUM_CHANNELS];
int channels;
double fd[MAX_NUM_LINES][MAX_NUM_CHANNELS];
double jm=0; 
int lines; 


int separability(int argc, char **argv){

 FILE *ftext;
 int lines2, channels2;
 
 if (argc != 5) separabilityUsage();	
 
 ftext=openFile("",argv[2],"wb");	
 lines=atoi(argv[3]);
 channels=atoi(argv[4]);
 	
 readHistFile(ftext,&lines2,&channels2); 
 
 if (channels !=channels2 || lines !=lines2){
  fprintf(stderr, "Incorrect number of lines or channels in text file.\n");  	 
  exit(EXIT_FAILURE);
 }

 recursion(--channels2,i,calcJM);

 fprintf(stdout,"Separablity: %f\n",jm); 
 fclose(ftext);	
 return (EXIT_SUCCESS);

}


int readHistFile(FILE *f, int *row2, int *band2){
 
 char buffer[MAX_LINE_LEN];
 char *p;
 int row=0, band; 
 
 while(fgets(buffer, MAX_LINE_LEN, f) !=NULL){
 
  band=0;
  
  if (buffer[0] != '\n'){
 
   p = strtok(buffer," \t");
   
  while (p!=NULL){
   fd[row][band]=atof(p);
  
   p = strtok (NULL, "  \t");
   band++; 
   
  } 

  row++; 
  } 
  
 }   
 
 *row2=row;
 *band2=band;

 return (EXIT_SUCCESS);
}



void separabilityUsage(){
 fprintf(stderr,"Usage: earth -separability inputtextfile <lines> <channels>\n\n");
 fprintf(stderr, "  inputtextfile  text file of histograms (class i band 1,2,3....class j band 1,2,3\n"); 
 fprintf(stderr, "  lines           \n");
 fprintf(stderr, "  channels \n\n");	 
 exit(EXIT_FAILURE); 
}


int recursion(int index, int *i, int (*f)(int *)){

  if (index<0){
   f(i);
  }

  else{
   for (i[index]=0;i[index]<lines;i[index]++){
    recursion(index-1,i,f);
   }
 }

 return (EXIT_SUCCESS);
}


int calcJM(int *i){

 int c;
 double p1=0, p2=0;

 for (c=0;c<channels;c++){
   p1*=fd[i[c]][c];
   p2*=fd[i[c]][c+channels];
   jm+=pow(sqrt(p1)-sqrt(p2),2);
 }

 return (EXIT_SUCCESS);
}

