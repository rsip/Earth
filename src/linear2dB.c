/*
NAME:		linear2dB.c 
DESCRIPTION: 	Converting radar data from linear to dB values and vice versa
AUTHOR:	 	Will Grey
VERSION:	2015-11-14	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int runLinear2dB(int argc, char **argv, int (*f)(FILE *, FILE*, float *, float *, metaData *, float)){
 
 float nullValue=0.0;
 metaData hdrData;

 initialiseHdrData(&hdrData);

 if (argc <=2)
  linear2dBUsage(argv[ 1 ]);
 strcpy(hdrData.infile,argv[ 2 ]); 
 if (argc >=4){ 
  strcpy(hdrData.outfile,argv[ 3 ]); 
 }
 else{
  strcpy(hdrData.outfile, hdrData.infile); 
  strcat(hdrData.outfile,".out");
 }
 if (argc==5) nullValue=atof(argv[ 4 ]);

 linear2dBImg(&hdrData,nullValue,f); 
 return (EXIT_SUCCESS);
}


int linear2dBImg(metaData *hdrData, float nullValue, int (*f)(FILE *, FILE *, float *, float *, metaData *, float)){

 FILE *fin, *fout;
 float *inImg, *outImg; 

 fin=openFile("",hdrData->infile,"rb");
 fout=openFile("",hdrData->outfile,"wb");
 	
 if((outImg  = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();
 if((inImg   = (float *) calloc(PIXELS, sizeof(float)))== NULL) memoryCheck();

 f(fin, fout, outImg, inImg, hdrData, nullValue);

 free(inImg);
 free(outImg);
 fclose(fin);
 fclose(fout);

 return (EXIT_SUCCESS);


}

int linear2dB(FILE *fin, FILE *fout, float *inImg, float *outImg, metaData *hdrData, float nullValue){
 
 int remainderPixels, i;
 	
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
   
   for (i=0;i<PIXELS;i++){
    if(*(inImg + i) > 0.0)
    *(outImg + i) = 10 * log10(*(inImg + i));
    else *(outImg + i) = nullValue;
   }
			
   fwrite(outImg,sizeof(float),PIXELS,fout);
 }

 for (i=0;i<remainderPixels;i++){
    if(*(inImg + i) > 0.0)
    *(outImg + i) = 10 * log10(*(inImg + i));
    else *(outImg + i) = nullValue;
   }
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 return (EXIT_SUCCESS);
}

int dB2linear(FILE *fin, FILE *fout, float *inImg, float *outImg, metaData *hdrData, float nullValue){
 
 int remainderPixels, i;
 	
 while ((remainderPixels=fread(inImg,sizeof(float),PIXELS,fin)) == PIXELS){
   
  for (i=0;i<PIXELS;i++){
   if(*(inImg + i) != nullValue)
    *(outImg + i) = pow(10,*(inImg + i)/10);
   else *(outImg + i) = 0.0;
  }			
  fwrite(outImg,sizeof(float),PIXELS,fout);
 }

 for (i=0;i<remainderPixels;i++){
  if(*(inImg + i) != nullValue)
    *(outImg + i) = pow(10,*(inImg + i)/10);
   else *(outImg + i) = 0.0;
 }
 
 fwrite(outImg,sizeof(float),remainderPixels,fout);

 return (EXIT_SUCCESS);
}

void linear2dBUsage(char *tool){
 fprintf(stderr,"Usage: earth %s inImg outImg [null value]\n\n",tool);		
 fprintf(stderr, "   inImg           input image (float)\n");
 fprintf(stderr, "   outImg          output image (float)\n");	   
 fprintf(stderr, "   null value      default: 0.0\n\n");		
 exit(EXIT_FAILURE);
}
