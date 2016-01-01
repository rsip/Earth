/*
NAME:		convertType.c 
DESCRIPTION: 	Convert between different data types
AUTHOR:	 	Will Grey
VERSION:	2015-11-09	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int runTypeConvert(int argc, char **argv, int (*f)(metaData *)){
 
 metaData hdrData;
 
 if (argc <=2)
  usageType(argv[1]);
 strcpy(hdrData.infile,argv[ 2 ]); 
 if (argc ==4){ 
  strcpy(hdrData.outfile,argv[ 3 ]); 
 }
 else{
  strcpy(hdrData.outfile, hdrData.infile); 
  strcat(hdrData.outfile,".out");
 }
 f(&hdrData); 
 return (EXIT_SUCCESS);
 
}

void usageType(char *tool){
 fprintf(stderr,"\nUsage: leaf %s infile [outfile] \n\n", tool);
 fprintf(stderr, "   infile        Input image\n"); 	   
 fprintf(stderr, "   outfile       Output image\n\n");
 exit(EXIT_FAILURE);
}

int ubyte2ushort(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned char *inImg;
 unsigned short *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 if((outImg  = (unsigned short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(unsigned short)*(inImg + i);
    
  fwrite(outImg,sizeof(short),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(short)*(inImg + i);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}


int byte2short(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 char *inImg;
 short *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 if((outImg  = (short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(short)*(inImg + i);
    
  fwrite(outImg,sizeof(short),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(short)*(inImg + i);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int ubyte2float(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned char *inImg;
 float *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(float)*(inImg + i);
    
  fwrite(outImg,sizeof(float),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(float)*(inImg + i);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int byte2float(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 char *inImg;
 float *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(float)*(inImg + i);
    
  fwrite(outImg,sizeof(float),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(float)*(inImg + i);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int byte2long(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 char *inImg;
 long *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 if((outImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(long)*(inImg + i);
    
  fwrite(outImg,sizeof(long),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(long)*(inImg + i);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int float2byte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 float *inImg;
 char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();	
 if((outImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(char)*(inImg + i);
    
  fwrite(outImg,sizeof(char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(char)*(inImg + i);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int float2ubyte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 float *inImg;
 unsigned char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();	
 if((outImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(unsigned char)*(inImg + i);
    
  fwrite(outImg,sizeof(unsigned char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(unsigned char)*(inImg + i);
  
 fwrite(outImg,sizeof(unsigned char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int long2float(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 long *inImg;
 float *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(float)*(inImg + i);
    
  fwrite(outImg,sizeof(float),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(float)*(inImg + i);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int long2byte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 long *inImg;
 char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();	
 if((outImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(char)*(inImg + i);
    
  fwrite(outImg,sizeof(char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(char)*(inImg + i);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int short2byte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 short *inImg;
 char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();	
 if((outImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(char)*(inImg + i);
    
  fwrite(outImg,sizeof(char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(char)*(inImg + i);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int ushort2ubyte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned short *inImg;
 unsigned char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (unsigned short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();	
 if((outImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(unsigned char)*(inImg + i);
    
  fwrite(outImg,sizeof(unsigned char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(unsigned char)*(inImg + i);
  
 fwrite(outImg,sizeof(unsigned char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int ushort2float(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned short *inImg;
 float *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (unsigned short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(float)*(inImg + i);
    
  fwrite(outImg,sizeof(float),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(float)*(inImg + i);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int short2float(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 short *inImg;
 float *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();
 if((outImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(float)*(inImg + i);
    
  fwrite(outImg,sizeof(float),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(float)*(inImg + i);
  
 fwrite(outImg,sizeof(float),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int short2long(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 short *inImg;
 long *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((inImg  = (short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();
 if((outImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();

 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(long)*(inImg + i);
    
  fwrite(outImg,sizeof(long),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(long)*(inImg + i);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int long2short(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 long *inImg;
 short *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();	
 if((outImg  = (short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(short)*(inImg + i);
    
  fwrite(outImg,sizeof(short),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(short)*(inImg + i);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}


int ulong2long(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned long *inImg;
 long *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (unsigned long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();	
 if((outImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(long)*(inImg + i);
    
  fwrite(outImg,sizeof(long),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(long)*(inImg + i);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int long2ulong(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 long *inImg;
 unsigned long *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();	
 if((outImg  = (unsigned long *) calloc(PIXELS, sizeof(long)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(long),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(unsigned long)*(inImg + i);
    
  fwrite(outImg,sizeof(long),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(unsigned long)*(inImg + i);
  
 fwrite(outImg,sizeof(long),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int byte2ubyte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 char *inImg;
 unsigned char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();	
 if((outImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(unsigned char)*(inImg + i);
    
  fwrite(outImg,sizeof(char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(unsigned char)*(inImg + i);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int ubyte2byte(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned char *inImg;
 char *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (unsigned char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();	
 if((outImg  = (char *) calloc(PIXELS, sizeof(char)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(char),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(char)*(inImg + i);
    
  fwrite(outImg,sizeof(char),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(char)*(inImg + i);
  
 fwrite(outImg,sizeof(char),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int ushort2short(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 unsigned short *inImg;
 short *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = (unsigned short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();	
 if((outImg  = ( short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(short)*(inImg + i);
    
  fwrite(outImg,sizeof(short),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(short)*(inImg + i);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}

int short2ushort(metaData *hdrData){
 
 FILE *fin, *fout;
 int remainderPixels, i;
 short *inImg;
 unsigned short *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 
 if((inImg  = ( short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();	
 if((outImg  = ( unsigned short *) calloc(PIXELS, sizeof(short)))== NULL) memoryCheck();
 
 while ((remainderPixels=fread(inImg,sizeof(short),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++)
   *(outImg + i)=(unsigned short)*(inImg + i);
    
  fwrite(outImg,sizeof(short),PIXELS,fout);
 }		
 
 for (i=0;i<remainderPixels;i++)
  *(outImg + i)=(unsigned short)*(inImg + i);
  
 fwrite(outImg,sizeof(short),remainderPixels,fout);
 
 free(inImg);
 free(outImg);

 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);
}


