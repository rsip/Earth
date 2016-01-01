/*
NAME:		reassign.c 
DESCRIPTION: 	Reassign values within byte image
AUTHOR:	 	Will Grey
VERSION:	2015-11-15	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int reassign(int argc, char **argv){
 
 FILE *fin, *fout, *ftext;
 int currentPixVal[NUM_CLASSES], reassignedPixVal[NUM_CLASSES];
 int row;
 
 if (argc != 5) {
  reassignUsage();	
 } 
	
 fin=openFile("",argv[2],"rb");
 fout=openFile("",argv[3],"wb");
 ftext=openFile("",argv[4],"r");	
 
 row=reassignVal(ftext, currentPixVal, reassignedPixVal);
 reassignImage(fin, fout, currentPixVal, reassignedPixVal, row);
		
 fclose(fin);
 fclose(fout);
 fclose(ftext);	
 return (EXIT_SUCCESS);
	
}

int reassignVal(FILE *ftext, int *currentPixVal, int *reassignedPixVal){
 
 char buffer[TEXT_LINE_LEN];
 int row=0,j;
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext) !=NULL){
  
  if (!isspace(*buffer)){
   sscanf(buffer,"%d",&currentPixVal[row]);
  
   for(j=0; j<TEXT_LINE_LEN; j++) 
    if( buffer[j] != '\n' && isspace(buffer[j]))
     sscanf(buffer+j,"%d",&reassignedPixVal[row]); 			
   row++; 
  }
 }    	

 return row;
}

int reassignImage(FILE *fin, FILE *fout, int *currentPixVal, int *reassignedPixVal, int row){	
 
 unsigned int i, x, remainderPixels;
 unsigned char *inImg, *outImg;
	
 if((inImg  = (unsigned char *) calloc(PIXELS, sizeof(char))) == NULL) memoryCheck();
 if((outImg = (unsigned char *) calloc(PIXELS, sizeof(char))) == NULL) memoryCheck();
	
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
  for(x = 0; x < PIXELS; x++){
   outImg[x]=inImg[x];
   for(i = 0; i < row ; i++){
    if(inImg[x] == currentPixVal[i]){
     outImg[x] = reassignedPixVal[i];	
     break;
    }
   }
  }
  fwrite(outImg, sizeof(char), PIXELS, fout);
 }

 for(x = 0; x < remainderPixels; x++){
  outImg[x]=inImg[x];
  for(i = 0; i < row ; i++){
   if(inImg[x] == currentPixVal[i]){
    outImg[x] = reassignedPixVal[i];	
    break;
   }
  }
 }
 fwrite(outImg, sizeof(char), remainderPixels, fout);
	
 free(inImg);
 free(outImg);
	
 return(EXIT_SUCCESS);

}

void reassignUsage(){
 fprintf(stderr,"Usage: leaf -reassign inImg inImg inputTextFile\n\n");
 fprintf(stderr, "   inImg           Input image (byte)\n");
 fprintf(stderr, "   outImg          Output image (byte)\n");
 fprintf(stderr, "   inputTextFile  Input two columns of ascii\n\n"); 	 
 exit(EXIT_FAILURE); 
}

