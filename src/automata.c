/*
NAME:		automata.c 
DESCRIPTION: 	For carrying out cellular automata uses 
                Markov for probability.
AUTHOR:	 	Will Grey
VERSION:	2016-03-28	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

#define WINSIZE 3


int automata(int argc, char *argv[]){
 
 metaData p;
 int i,j,x,y,t,timesteps,edge;
 struct stat size, size1;
 FILE *fin, *fout;
 unsigned char cls[WINSIZE*WINSIZE]; 
 float matrix[MAX_NUM_CLASSES][MAX_NUM_CLASSES],r;
 float prob[WINSIZE*WINSIZE], cumP[WINSIZE*WINSIZE+1];
 double sumP;
 unsigned char *img, **imgPtr, *swap;

 if(argc != 7) automataUsage();

 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 if (stat(argv[3], &size1) == -1) fileReadError(argv[3]);
 if (size.st_size != size1.st_size)fileSizeErr(argv[2],argv[3]);
	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"rb");
 
 p.xdim=atoi(argv[5]);
 timesteps=atoi(argv[6]);

 readTransitionMatrix(argv[4],matrix);
 
 p.ydim = size.st_size / p.xdim;
 edge=WINSIZE/2;
 
 if((img  = (unsigned char *) calloc(p.ydim*p.xdim*2,sizeof(char)))== NULL) memoryCheck();
 if((imgPtr     = (unsigned char **) calloc(2, sizeof(char))) == NULL) memoryCheck();

 *(imgPtr) = img;
 *(imgPtr + 1) = img + p.ydim * p.xdim;

 fread(*(imgPtr),sizeof(char),p.ydim*p.xdim,fin);			
 


 for (t=0;t<timesteps;t++){
  for(y = edge; y < p.ydim-edge; y++){
   for(x = edge; x < p.xdim-edge; x++){
   
    sumP=0;
    for(i = 0; i < WINSIZE; i++){ 
     for(j = 0; j < WINSIZE; j++){
      prob[i * WINSIZE + j] = matrix[*(*(imgPtr) + (p.xdim * y + x))][*(*(imgPtr) + (p.xdim * (y + i - edge)) + (x + j - edge))];
      cls[i]=*(*(imgPtr) + (p.xdim * (y + i - edge)) + (x + j - edge));
      sumP=prob[i * WINSIZE + j]+sumP;    
     }
    }

    r = rand()/(RAND_MAX+1.0);
    cumP[0]=0.0;

    for (i=0;i<=WINSIZE*WINSIZE;i++)
     cumP[i+1]=(prob[i]/sumP)+cumP[i];

     for (i=0;i<=WINSIZE*WINSIZE;i++){
      if (r>=cumP[i] && r<cumP[i+1]){
       *(*(imgPtr + 1) + (p.xdim * y + x)) = cls[i];
       break;
      }
     }
   
   }
  }

  fwrite(*(imgPtr+1),sizeof(char),p.ydim*p.xdim,fout);
  swap = *(imgPtr);
  *(imgPtr) = *(imgPtr + 1);	
  *(imgPtr) = swap;   
  
 }


 
 
 free(img);
 fclose(fout);		
 fclose(fin);		

 return(EXIT_SUCCESS);		

}


int readTransitionMatrix(char *infile, float matrix[MAX_NUM_CLASSES][MAX_NUM_CLASSES]){

 FILE *fin;
 char *inImg; 
 char *p;
 int cols=0, rows=0;   			 

 fin  = openFile("", infile, "r");
 if((inImg  = (char *) calloc(MAX_LINE_LEN, sizeof(char)))== NULL) memoryCheck();
 fgets(inImg, MAX_LINE_LEN, fin);

 while(fgets(inImg, MAX_LINE_LEN, fin) !=NULL){
  
  if (inImg[0] != '\n'){ 
   cols=0;
   p = strtok(inImg," \t");
   
   while (p!=NULL){
    if (cols!=0){
     matrix[cols-1][rows]=atof(p);
    } 
    p = strtok (NULL, "  \t");
    cols++; 
   } 
   rows++;
   }    
  
 } 
 
 free(inImg); 
 fclose(fin);

 return (EXIT_SUCCESS);
 	
}

int automataUsage(){
 
 fprintf(stderr,"Usage: earth -automata inImg outImg transitionMatrixFile xdim timesteps \n\n");		
 fprintf(stderr, "   inImg			Input classified image \n");
 fprintf(stderr, "   outImg			Output classified image 2\n");
 fprintf(stderr, "   transitionMatrixFile	Transition Matrix file from trainCA\n");
 fprintf(stderr, "   xdim	        	Number of pixels\n");
 fprintf(stderr, "   timeSteps	        	Number of timesteps to run simulation\n\n");		 	   
 exit(EXIT_FAILURE);

}

