/*
NAME:		bitConv.c 
DESCRIPTION: 	Convert between bytes and bits to 
                save space for binary 0 / 1 images
AUTHOR:	 	Will Grey
VERSION:	2016-08-18	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"
#define BITS 8


int runBitConvert(int argc, char **argv, int (*f)(metaData *, int)){
 
 metaData hdrData;
 int ZeroPad=0;
 
 if (argc <=3)
  usageBitConv(argv[1]);
  
 strcpy(hdrData.infile,argv[ 2 ]);
 strcpy(hdrData.outfile,argv[ 3 ]); 
 
 if (argc == 5) 
   ZeroPad=atoi(argv[4]);
 
 f(&hdrData, ZeroPad); 
 return (EXIT_SUCCESS);
 
}

void usageBitConv(char *tool){
 fprintf(stderr,"\nUsage: earth %s infile outfile Zero_Padding \n\n", tool);
 fprintf(stderr, "   infile        Input image\n"); 	   
 fprintf(stderr, "   outfile       Output image\n");
 fprintf(stderr, "   zero_padding  Default=0, value between 0-7\n\n");
 exit(EXIT_FAILURE);
}

int byte2bit(metaData *hdrData, int ZeroPad){
 
 FILE *fin, *fout;
 int remainderPixels, i, j;
 unsigned char *inImg;
 unsigned char *outImg;
 unsigned char val[BITS]; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (unsigned char *) calloc(PIXELS*BITS, sizeof(char)))== NULL) memoryCheck();	
 if((outImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS*BITS,fin)) == PIXELS*BITS){
   
  for (i=0;i<PIXELS;i++){
   for (j=0;j<BITS;j++)
    val[j]=*(inImg + i * BITS + j); 
   *(outImg + i)=byte2bitsConv(val);
  }
 
  fwrite(outImg,sizeof(char),PIXELS,fout);
 }		
 
  for (i=0;i<remainderPixels-1;i++){
   for (j=0;j<BITS;j++)
    val[j]=*(inImg + i * BITS + j); 
   *(outImg + i)=byte2bitsConv(val);
  }
   
  for (j=0;j<BITS;j++)
   val[j]=0;   

  for (j=0;j<(BITS-(remainderPixels % BITS));j++)
   val[j]=*(inImg + i * BITS + j);  
   
  *(outImg + i)=byte2bitsConv(val);

 fwrite(outImg,sizeof(char),remainderPixels,fout);
 fprintf(stdout,"zero_padding: %d",remainderPixels % BITS);


 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int bit2byte(metaData *hdrData, int ZeroPad){
 
 FILE *fin, *fout;
 int remainderPixels, i,j;
 unsigned char *inImg;
 unsigned char *outImg; 
 unsigned char *val; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();	
 if((outImg  = (unsigned char *) calloc(PIXELS*BITS, sizeof(char)))== NULL) memoryCheck();
 if((val  = (unsigned char *) calloc(BITS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS*BITS){
   
  for (i=0;i<PIXELS;i++){
   val=bits2byteConv(*(inImg + i));
    for (j=0;j<BITS;j++)
     *(outImg + i * BITS + j)=val[j]; 
  }
 
  fwrite(outImg,sizeof(char),PIXELS*BITS,fout);
 }		
 
  for (i=0;i<remainderPixels;i++){
   val=bits2byteConv(*(inImg + i));
    for (j=0;j<BITS;j++)
     *(outImg + i * BITS + j)=val[j]; 
  }
  
 fwrite(outImg,sizeof(char),remainderPixels-ZeroPad,fout);
 fprintf(stdout,"zero_padding: %d",remainderPixels % BITS);


 free(inImg);
 free(outImg);
 free(val);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}


unsigned char byte2bitsConv(unsigned char *val){

 unsigned char a=0;
 int i;
 
 for (i=0;i<BITS;i++){
  a=a|val[i];
  if (i!=BITS-1) a=a<<1;
 }

 return a;
}


unsigned char * bits2byteConv(unsigned char a){

 int i;
 unsigned char mask;
 unsigned char *val;

 val  = (unsigned char *) calloc(BITS, sizeof(char));

 for (i=BITS-1;i>=0;i--){
  mask=pow(2,i);
  val[i]= mask & a;
  val[i]=val[i]>>i;
 }

 return val;

}
