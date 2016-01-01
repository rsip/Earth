/*
NAME:		confusion.c 
DESCRIPTION: 	Calculates the classification confusion matrix
AUTHOR:	 	Will Grey
VERSION:	2015-11-15	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"


int confusion(int argc, char *argv[]){
 
 conf p;
 int i,j, remainderPixels;
 struct stat size, size1;
 FILE *fgt, *fcls, *fout;
 unsigned char *cls, *gt; 
 float nominator=0.0, denominator=0.0;
 
 if(argc != 5) confusionUsage();

 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 if (stat(argv[3], &size1) == -1) fileReadError(argv[3]);
 if (size.st_size != size1.st_size)fileSizeErr(argv[2],argv[3]);

 p.pixels = size.st_size;
	
 fgt=openFile("",argv[2],"rb");
 fcls=openFile("",argv[3],"rb");
 fout=openFile("",argv[4],"w");	

 if((cls  = (unsigned char *) calloc(p.pixels,sizeof(char)))== NULL) memoryCheck();	
 if((gt  = (unsigned char *) calloc(p.pixels,sizeof(char)))== NULL) memoryCheck();

 for(i=0; i<NUM_CLASSES; i++)
  for(j=0; j<NUM_CLASSES; j++)
   p.matrix[i][j]=0;	

 fread(gt,sizeof(char),p.pixels,fgt);			
 fread(cls,sizeof(char),p.pixels,fcls);
 
 p.nClasses=0;

 while ((remainderPixels=fread(gt,sizeof(char),PIXELS,fgt)) == PIXELS){
  fread(cls, sizeof(char), PIXELS, fcls);
  
  for(i = 0; i < PIXELS; i++){
   p.matrix[*(gt+i)][*(cls+i)]++;
   if(*(gt+i) > p.nClasses) p.nClasses = *(gt+i); 
  }						
 						
 }

 for (i=0;i<remainderPixels;i++){
  p.matrix[*(gt+i)][*(cls+i)]++;
  if(*(gt+i) > p.nClasses) p.nClasses = *(gt+i); 
 }				
  	
 for(j=0; j<p.nClasses; j++){
  p.colTotal[j] = 0;
  p.rowTotal[j] = 0;
  for(i=0; i<p.nClasses; i++){
   p.colTotal[j] = p.matrix[i][j] + p.colTotal[j];
   p.rowTotal[j] = p.matrix[j][i] + p.rowTotal[j];
  }
 }
		
 p.totalCorrect = 0;
	
 for(i=0; i<p.nClasses; i++){
  p.correct[i] = p.matrix[i][i];
  p.totalCorrect = p.correct[i] + p.totalCorrect;
 }
	
 for(j=0; j<p.nClasses; j++)
  for(i=0; i<p.nClasses; i++) 
   p.matrixPercent[j][i] = (float)p.matrix[j][i] / (float)p.rowTotal[j] * 100;	
	
	
 for(i=0; i<p.nClasses; i++){
  p.comErr[i] = (((float)p.rowTotal[i] - (float)p.correct[i]) / (float)p.rowTotal[i]) * 100;
  p.omErr[i] =  (((float)p.colTotal[i] - (float)p.correct[i]) / (float)p.rowTotal[i]) * 100;
  p.userAcc[i] = ((float)p.correct[i] / (float)p.rowTotal[i]) * 100;
  p.prodAcc[i] = ((float)p.correct[i] / (float)p.colTotal[i]) * 100; 
 }
 
 p.accuracy = ((float)p.totalCorrect / (float)p.pixels) * 100;
 for(i=0; i<p.nClasses; i++)
  nominator = ((float)p.rowTotal[i] * (float)p.colTotal[i]) + nominator;
	
 for(j=0; j<p.nClasses; j++)
  for(i=0; i<=p.nClasses; i++)
   denominator = ((float)p.rowTotal[i] * (float)p.colTotal[j]) + denominator;
	  
 p.expected = nominator / denominator;
 p.observed = ((float)p.totalCorrect / ((float)p.pixels));
 p.kappa = (p.observed - p.expected) / (1 - p.expected);

 printConfusion(fout, &p, argv[3]);
 
 free(gt);
 free(cls);
	
 fclose(fout);		
 fclose(fgt);		
 fclose(fcls);
 
 return(EXIT_SUCCESS);		

}


int printConfusion(FILE *fout, conf *p, char *clsImg){
 int i,j;

 fprintf(fout,"\nConfusion Matrix: %s\n", clsImg);	
 fprintf(fout,"\nOverall Accuracy = (%ld / %d) %f %%",p->totalCorrect, p->pixels, p->accuracy);
 fprintf(fout,"\nKappa Coefficient = %f\n", p->kappa);
	
 fprintf(fout,"\nGround Truth (Pixels)");
	
 fprintf(fout,"\nClass");
 for(i=0; i < p->nClasses; i++)fprintf(fout,"\t%d", i);	
 fprintf(fout,"\tTotal");
	
 for(i=0; i<p->nClasses; i++){
  fprintf(fout,"\n%d", i);
  for(j=0; j< p->nClasses; j++)fprintf(fout,"\t%ld", p->matrix[j][i]);
  fprintf(fout,"\t%ld", p->colTotal[i]);
 } 
	
 fprintf(fout,"\nTotal");
 for(j=0; j < p->nClasses; j++)fprintf(fout,"\t%ld", p->rowTotal[j]);
 fprintf(fout,"\t%d", p->pixels);

 fprintf(fout,"\n\nGround Truth (Percent)");
	
 fprintf(fout,"\nClass");
 for(i=0; i < p->nClasses; i++)fprintf(fout,"\t%d", i);	
 fprintf(fout,"\tTotal");		
        
 for(i=0; i<p->nClasses; i++){
  fprintf(fout,"\n%d", i);
  for(j=0; j< p->nClasses; j++)fprintf(fout,"\t%4.2f", p->matrixPercent[j][i]);
  fprintf(fout,"\t%4.2f", (float)p->colTotal[i] /  ((float)p->pixels) * 100 );	
 } 

 fprintf(fout,"\nTotal");
 for(j=0; j < p->nClasses; j++)fprintf(fout,"\t%f", (float)p->rowTotal[j] / ((float)p->pixels) * 100);
 fprintf(fout,"\t%d\n", p->pixels);
	
 fprintf(fout,"\nClass \t Commission \t Omission \t Commission \t Omission\n");  
 fprintf(fout,"           (Percent)  \t (Percent)\t (Pixels)   \t (Pixels)\n");  	
   
 for(i=0; i < p->nClasses; i++){
  fprintf(fout,"%d", i);
  fprintf(fout,"\t%4.2f \t%4.2f \t%ld/%ld \t%ld/%ld\n", p->omErr[i], p->comErr[i], p->colTotal[i] - p->correct[i], p->rowTotal[i], p->rowTotal[i] - p->correct[i], p->rowTotal[i]);
 }		
	
 fprintf(fout,"\nClass \t Prod. Acc.\t User Acc. \t Prod. Acc. \t User Acc.\n");  
 fprintf(fout,"          (Percent) \t (Percent) \t (Pixels)   \t (Pixels)\n");
 
 for(i=0; i < p->nClasses; i++){
  fprintf(fout,"%d", i);
  fprintf(fout,"\t%4.2f \t%4.2f \t%ld/%ld \t%ld/%ld\n", p->userAcc[i], p->prodAcc[i], p->correct[i], p->rowTotal[i], p->correct[i], p->colTotal[i]);
 }
	
 fprintf(fout,"\n");

 return(EXIT_SUCCESS);

}

int confusionUsage(){
 
 fprintf(stderr,"Usage: leaf -confusion groundTruthImage classifiedImage outputTextFile \n\n");		
 fprintf(stderr, "   groundTruthImage	Input ground truth image\n");
 fprintf(stderr, "   classifiedImage	Input classified image\n");
 fprintf(stderr, "   outputTextFile	Output confusion matrix\n\n");	 	   
/* fprintf(stderr, "   flag		0: include unclassified (default)\n");
 fprintf(stderr, "      		1: exclude unclassified\n\n"); */
 exit(EXIT_FAILURE);
}
