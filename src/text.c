/*
NAME:		text.c 
DESCRIPTION: 	Basic processing on text files
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int ar(int argc, char **argv)
{
 
 char *buffer;
 FILE *ftext1, *ftext2, *fout;
 int samples=0, halfSamples, i;
 float *c1, *c2;
 
 if (argc != 5) 
  sideCatUsage("-ar");	
 
 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();

 ftext1  = openFile("",argv[2],  "r");  
 ftext2  = openFile("",argv[3],  "r");  
 fout  = openFile("",argv[4],  "w");  

 while(fgets(buffer, TEXT_LINE_LEN, ftext1) !=NULL)
  if (!isspace(*buffer))
   samples++;
  
 fclose(ftext1);
 ftext1  = openFile("",argv[2],  "r");  

 if((c1  = (float *) calloc(samples, sizeof(float)))== NULL) memoryCheck();
 if((c2   = (float *) calloc(samples, sizeof(float)))== NULL) memoryCheck();
 
 i=0;
 while(fgets(buffer, TEXT_LINE_LEN, ftext1) !=NULL){
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",c1+i);
   i++;
  }
 } 

 i=0;
 while(fgets(buffer, TEXT_LINE_LEN, ftext2) !=NULL){
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",c2+i);
   i++;
  }
 } 

 if (i != samples){
  fprintf(stderr,"Files need to be the same length");
  exit(EXIT_FAILURE);
 }

 halfSamples=samples/2;

 for (i=0;i<halfSamples;i++)
  fprintf(fout, "%f\n", correlation (c1+i, c2, samples-i));
 
 free(buffer);
 fclose(ftext1);
 fclose(ftext2);
 fclose(fout);
 return (EXIT_SUCCESS);

}



int sideCat(int argc, char **argv){

 char *buffer1, *buffer2;
 FILE *ftext1, *ftext2, *fout;
 int i;

  if (argc != 5) {
  sideCatUsage("-sideCat");	
 } 
 
 ftext1  = openFile("",argv[2],  "r");  
 ftext2  = openFile("",argv[3],  "r");  
 fout  = openFile("",argv[4],  "w");  

 if((buffer1 = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck(); 
 if((buffer2 = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer1, TEXT_LINE_LEN, ftext1) !=NULL){
  
  if (!isspace(*buffer1)){
   if (fgets(buffer2, TEXT_LINE_LEN, ftext2)!=NULL){ 
    i=0;
    while (!isspace(buffer1[i])){
     fprintf(fout,"%c",buffer1[i]);
     i++;
    }
    fprintf(fout,"\t%s",buffer2);
   
   }
   else{
    fprintf(fout,"%s",buffer1);
   }
  }
 } 

 free(buffer1);
 free(buffer2);
 
 fclose(ftext1);
 fclose(ftext2);
 fclose(fout);
 return (EXIT_SUCCESS);

}


int meanWindow(int argc, char **argv){

 int row=0, winlen=3, i, j;
 char *buffer;
 float val[MAX_COL_LEN], sum=0.0; 
 FILE *ftext, *fout;

 if (argc < 4) meanWindowUsage("-meanWindow");	
 ftext  = openFile("",argv[2],  "r");  
 fout  = openFile("",argv[3],  "w");

 if (argc == 5) winlen=atoi(argv[4]);
  
 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext) !=NULL){
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",val+row);
   row++;
  }
 } 

 for(i=0;i<row-winlen;i++){
  sum=0;
  for (j=0;i<winlen;j++)
   sum=sum+val[row];
  fprintf(fout,"%f\n",sum/(float)winlen);
 }

 fclose(ftext);
 fclose(fout);
 free(buffer);
 
 return (EXIT_SUCCESS);

}

int calcTotalMean(int argc, char **argv){

 int row=0;
 char *buffer;
 float val=0.0, sum=0.0; 
 FILE *ftext;

 if (argc != 3) textUsage("-calcTotalMean");	
 ftext  = openFile("",argv[2],  "r");  

 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext) !=NULL){
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",&val);
   sum=sum+val;
   row++;
  }
 } 

 fprintf(stdout,"Total: \t%f \n",sum);
 fprintf(stdout,"Mean: \t%f \n",sum/row);
 fprintf(stdout,"Num: \t%d \n",row);
 
 fclose(ftext);
 free(buffer);
 
 return (EXIT_SUCCESS);

}

int getNumLines(int argc, char **argv){

 int row=0;
 char *buffer, *p;
 FILE *ftext;

 if (argc != 3) textUsage("-getNumLines");	
 
 ftext  = openFile("",argv[2],  "r"); 
 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext)!=NULL){
  
 /* if (strcmp(buffer,"\n")!=0) row++; */

  p=buffer;
  while(*p==' ' || *p=='\t' || *p=='\r') p++;
  if(*p!='\n') row++;

/* if (!isspace(*buffer))
  row++; */ 
 } 
   
 fprintf(stdout,"NumRows %d \n",row);
 
 free(buffer);
 fclose(ftext);
 return (EXIT_SUCCESS);
}

int getNumLinesAll(int argc, char **argv)
{

 int row=0;
 char *buffer;
 FILE *ftext;

 if (argc != 3) textUsage("-getNumLinesAll");	 

 ftext  = openFile("",argv[2],  "r"); 
 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext)!=NULL)
  row++; 
  
 fprintf(stdout,"NumRows %d \n",row);
 
 free(buffer);
 fclose(ftext);
 return (EXIT_SUCCESS);

}

void sideCatUsage(char *tool){
 fprintf(stderr,"Usage: earth %s inputtextfile1 inputtextfile2 outputtextfile\n\n",tool);
 fprintf(stderr, "   inputtextfile1  Input text file 1\n"); 
 fprintf(stderr, "   inputtextfile2  Input text file 2\n");
 fprintf(stderr, "   outputtextfile  Output text file\n\n");	 
 exit(EXIT_FAILURE); 
}


void textUsage(char *tool){
 fprintf(stderr,"Usage: earth %s inputtextfile\n\n",tool);
 fprintf(stderr, "   inputtextfile  Input text file\n\n"); 	 
 exit(EXIT_FAILURE); 
}

void meanWindowUsage(char *tool){
 fprintf(stderr,"Usage: earth %s inputtextfile outputtextfile [winlen]\n\n",tool);
 fprintf(stderr, "   inputtextfile  Input text file\n"); 
 fprintf(stderr, "   outputtextfile  Output text file\n");
 fprintf(stderr, "   winlen Window size\n\n");	 
 exit(EXIT_FAILURE); 
}

