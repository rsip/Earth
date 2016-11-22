/*
NAME:		spectralResponse.c 
DESCRIPTION: 	Calculate broad band spectral response given 
                irriadiance and spectral response function
AUTHOR:	 	Will Grey
VERSION:	2015-12-13	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int spectralResponse(int argc, char **argv){
 
 FILE *firrad, *fsrf;
 float wl[SPECTRAL_RESOLUTION], wl2[SPECTRAL_RESOLUTION];
 double srf[SPECTRAL_RESOLUTION];
 double irrad[SPECTRAL_RESOLUTION];
 float broadBandIrrad;
 int row, row2;
 
 if (argc < 3) spectralUsage();	
 
 #ifdef TEST
 
 planck(irrad);
 for (i=SOLAR_SPEC_MIN;i<SOLAR_SPEC_MAX;i++)
  fprintf (stdout,"%d %e\n", i, irrad[i-SOLAR_SPEC_MIN]); 

 #endif 

 fsrf=openFile("",argv[2],"r");	
 row=spectralVal(fsrf, wl, srf);
 fclose(fsrf);

 if (argc==3){
   planck(irrad);
  }
  else{
   firrad=openFile("",argv[3],"r");
   row2=spectralVal(firrad, wl2, irrad);
   fclose(firrad);
  } 
 
 if (row2 > row){
  fprintf(stdout, "spectralResponse: Broadband too large\n"); 
  exit(EXIT_FAILURE);
 }

 broadBandIrrad=convolve(wl,wl2,(float *)srf,irrad,row);
 
 fprintf(stdout, "Broadband irradiance: %f\n", broadBandIrrad);

 return (EXIT_SUCCESS); 
	
}

int planck(double *L){

/* Need to fix function */

 int wl;
 
 double c1, c2, wv;

 double h=PLANCK_CONSTANT;
 double c=SPEED_OF_LIGHT;
 double T=TEMPERATURE_SUN;
 double k=BOLTZMANN_CONSTANT;

 c1=(2 * h * c * c);
 c2= (h * c / k);

 c1=3.741832e-4;
 c2=1.4387862e+4;


 #ifdef TEST

 wv=5e-7;
 t1=5855;

 L[0]=(c1 / pow(wv,5))/(exp(c2 / ( wv * t1))-1) * 1e12;

 fprintf(stderr,"%e\n",L[0]);

 #endif


 for (wl=SOLAR_SPEC_MIN;wl<SOLAR_SPEC_MAX;wl++){
  wv=(double)wl*1e-9;
  L[wl-SOLAR_SPEC_MIN]=(c1 / pow(wv,5)) / (exp (c2 / (wv * T)) - 1);
 }

 return (EXIT_SUCCESS);
}

float convolve (float *wl, float *wl2, float *srf, double *irrad, int row){

 int i,j;
 float broadBandIrrad=0.0;

 for (i=0; i<SPECTRAL_RESOLUTION; i++)
  for (j=0; j<SPECTRAL_RESOLUTION; j++)
  if(wl[i]==wl2[j])
   broadBandIrrad += srf[i] * irrad[j];

 return broadBandIrrad;

}

int spectralVal(FILE *ftext, float *currentPixVal, double *reassignedPixVal){
 
 char buffer[TEXT_LINE_LEN];
 int row=0,j;
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext) !=NULL){
  
  if (!isspace(*buffer)){
   sscanf(buffer,"%f",&currentPixVal[row]);
  
   for(j=0; j<TEXT_LINE_LEN; j++) 
    if( buffer[j] != '\n' && isspace(buffer[j]))
     sscanf(buffer+j,"%lf",&reassignedPixVal[row]); 			
   row++; 
  }
 }    	

 return row;
}

void spectralUsage(){
 fprintf(stderr,"Usage: earth -spectralResponse srfFile [spectraFile/planck]\n\n");
 fprintf(stderr, "   srfFile        Spectral response function file\n");
 fprintf(stderr, "   spectraFile    For surface or atmospheric spectra / planck model\n\n");
 exit(EXIT_FAILURE); 
}

