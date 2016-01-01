
/*
NAME:		noise.c 
DESCRIPTION: 	Box Muller transform to add Gaussian noise to text file
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int addNoise(int argc, char **argv){

 char *buffer;
 float val;
 double sigma; 
 FILE *fin, *fout;

 if (argc != 5) noiseUsage();	
 fin  = openFile("",argv[2],  "r");
 fout = openFile("",argv[3],  "w");
 sigma = atof(argv[4]);  

 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, fin) !=NULL){
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",&val);
   fprintf(fout,"%f\n", generateGaussianNoise((double)val,sigma));
   
  }
 }  
 
 fclose(fin);
 fclose(fout);
 free(buffer);
 
 return (EXIT_SUCCESS);

}


void noiseUsage(){
 fprintf(stderr,"Usage: leaf -addNoise inputTextfile outputTextfile sigma\n\n");
 fprintf(stderr, "   inputTextfile  Input text file\n");
 fprintf(stderr, "   outputTextfile Output text file\n");
 fprintf(stderr, "   sigma          Standard deviation of error\n\n");	 
 exit(EXIT_FAILURE); 
}

double generateGaussianNoise(double mean, double sigma){

 double u1, u2, s;
 
 do {
  u1 = rand() * (1.0 / RAND_MAX);
  u2 = rand() * (1.0 / RAND_MAX);
  u1 = (2.0 * u1) - 1.0;
  u2 = (2.0 * u2) - 1.0;
  s=u1*u1+u2*u2;
 } 
 while (s >= 1.0);
 
 s=sqrt((-2.0 * log(s)) / s) * u1;

 return s * sigma + mean;

}

