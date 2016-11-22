/*
NAME:		trainCA.c 
DESCRIPTION: 	For training probability matrix for
                cellular automata
AUTHOR:	 	Will Grey
VERSION:	2016-03-28	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"


int trainCA(int argc, char *argv[]){
 
 conf p;
 int i,j;
 struct stat size, size1;
 FILE *fgt, *fcls, *fout;
 unsigned char *cls, *gt; 

 if(argc != 7) trainCAUsage();

 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 if (stat(argv[3], &size1) == -1) fileReadError(argv[3]);
 if (size.st_size != size1.st_size)fileSizeErr(argv[2],argv[3]);

 p.pixels = size.st_size;
	
 fgt=openFile("",argv[2],"rb");
 fcls=openFile("",argv[3],"rb");
 fout=openFile("",argv[4],"w");	

 p.nClasses=atoi(argv[5]);
 p.timesteps=atoi(argv[6]);

 if((cls  = (unsigned char *) calloc(p.pixels,sizeof(char)))== NULL) memoryCheck();	
 if((gt  = (unsigned char *) calloc(p.pixels,sizeof(char)))== NULL) memoryCheck();

 for(i=0; i<NUM_CLASSES; i++)
  for(j=0; j<NUM_CLASSES; j++)
   p.matrix[i][j]=0;	

 fread(gt,sizeof(char),p.pixels,fgt);			
 fread(cls,sizeof(char),p.pixels,fcls);
 
  for(i = 0; i < p.pixels; i++)
   p.matrix[*(gt+i)][*(cls+i)]++;
  						
  for(j=0; j<p.nClasses; j++){
  p.colTotal[j] = 0;
  p.rowTotal[j] = 0;
  for(i=0; i<p.nClasses; i++){
   p.colTotal[j] = p.matrix[i][j] + p.colTotal[j];
   p.rowTotal[j] = p.matrix[j][i] + p.rowTotal[j];
  }
 }

 for(j=0; j<p.nClasses; j++){
  for(i=0; i<p.nClasses; i++){ 
   p.matrixPercent[j][i] = (float)p.matrix[j][i] / (float)p.rowTotal[j];

   /* divide by timeteps because probability is per timestep for transition */
	
   if (i !=j) p.matrixPercent[j][i] = p.matrixPercent[j][i] / p.timesteps;
  }
 }

 printTrainCA(fout, &p);
 
 /*********/

 free(gt);
 free(cls);
	
 fclose(fout);		
 fclose(fgt);		
 fclose(fcls);
 
 return(EXIT_SUCCESS);		

}


int trainCAUsage(){
 
 fprintf(stderr,"Usage: earth -trainCA classifiedImage1 classifiedImage2 outputTextFile nClasses timesteps\n\n");		
 fprintf(stderr, "   classifiedImage1	Input classified image 1\n");
 fprintf(stderr, "   classifiedImage2	Input classified image 2\n");
 fprintf(stderr, "   outputTextFile	Output probability matrix\n");
 fprintf(stderr, "   nClasses	        Number of classes\n");
 fprintf(stderr, "   timesteps	        Number oftimesteps between images (typically 1 per year)\n\n");		 	   
 exit(EXIT_FAILURE);

}


int printTrainCA(FILE *fout, conf *p){
 int i,j;

 for(i=0; i < p->nClasses; i++)fprintf(fout,"\t%d", i);	
 	       
 for(i=0; i<p->nClasses; i++){
  fprintf(fout,"\n%d", i);
  for(j=0; j< p->nClasses; j++)
   fprintf(fout,"\t%4.2f", p->matrixPercent[j][i]);
 } 

 fprintf(fout,"\n");

 return(EXIT_SUCCESS);

}


