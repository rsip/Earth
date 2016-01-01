/*
NAME:		leaf.c 
DESCRIPTION: 	Basic image processing tool for
                Earth observation data
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "leaf.h"

int main(int argc, char **argv)
{
 
 if (argc <= 1) usageLeaf();
 readHdrData(argc, argv);
   
 return(EXIT_SUCCESS);
}


int readArg(char *arg1, char *arg2){

 char a1[MAX_LINE_LEN];
 char a2[MAX_LINE_LEN];

 strcpy(a1,"-");
 strcpy(a2,"--");

 strcat(a1,arg2);
 strcat(a2,arg2); 

 return (!strcasecmp(arg1, a1) || !strcasecmp(arg1, a2));
}


void readHdrData(int argc, char **argv){

 if(readArg(argv[ 1 ],"copy")) runCopy(argc,argv);
 else if (readArg(argv[ 1 ],"swap")) runSwap(argc,argv);
 else if (readArg(argv[ 1 ],"shiftMeridian")) shiftMeridian(argc,argv);
 else if (readArg(argv[ 1 ],"xflip")) flip(argc,argv,xflip);
 else if (readArg(argv[ 1 ],"yflip")) flip(argc,argv,yflip);
 else if (readArg(argv[ 1 ],"header")) runHeader(argc,argv);
 else if (readArg(argv[ 1 ],"diff")) diff(argc,argv);
 else if (readArg(argv[ 1 ],"add")) add(argc,argv);
 else if (readArg(argv[ 1 ],"ratio")) ratio(argc,argv);
 else if (readArg(argv[ 1 ],"modulus")) modulus(argc,argv);
 else if (readArg(argv[ 1 ],"mask")) mask(argc,argv);
 else if (readArg(argv[ 1 ],"thresh")) thresh(argc,argv);
 else if (readArg(argv[ 1 ],"degConv")) degConv(argc,argv);
 else if (readArg(argv[ 1 ],"byte2short")) runTypeConvert(argc,argv, byte2short);
 else if (readArg(argv[ 1 ],"byte2float")) runTypeConvert(argc,argv, byte2float);
 else if (readArg(argv[ 1 ],"byte2long")) runTypeConvert(argc,argv, byte2long);
 else if (readArg(argv[ 1 ],"float2byte")) runTypeConvert(argc,argv, float2byte);
 else if (readArg(argv[ 1 ],"long2float")) runTypeConvert(argc,argv, long2float);
 else if (readArg(argv[ 1 ],"long2byte")) runTypeConvert(argc,argv, long2byte);
 else if (readArg(argv[ 1 ],"short2byte")) runTypeConvert(argc,argv, short2byte);
 else if (readArg(argv[ 1 ],"short2float")) runTypeConvert(argc,argv, short2float);
 else if (readArg(argv[ 1 ],"short2long")) runTypeConvert(argc,argv, short2long);
 else if (readArg(argv[ 1 ],"short2ushort")) runTypeConvert(argc,argv, short2ushort);
 else if (readArg(argv[ 1 ],"ushort2short")) runTypeConvert(argc,argv, ushort2short);
 else if (readArg(argv[ 1 ],"ulong2long")) runTypeConvert(argc,argv, ulong2long);
 else if (readArg(argv[ 1 ],"long2ulong")) runTypeConvert(argc,argv, long2ulong);
 else if (readArg(argv[ 1 ],"byte2ubyte")) runTypeConvert(argc,argv, byte2ubyte);
 else if (readArg(argv[ 1 ],"ubyte2byte")) runTypeConvert(argc,argv, short2long);
 else if (readArg(argv[ 1 ],"long2short")) runTypeConvert(argc,argv, long2short); 
 else if (readArg(argv[ 1 ],"ushort2float")) runTypeConvert(argc,argv, ushort2float);
 else if (readArg(argv[ 1 ],"ubyte2ushort")) runTypeConvert(argc,argv, ubyte2ushort);
 else if (readArg(argv[ 1 ],"ubyte2float")) runTypeConvert(argc,argv, ubyte2float);
 else if (readArg(argv[ 1 ],"ushort2ubyte")) runTypeConvert(argc,argv, ushort2ubyte);
 else if (readArg(argv[ 1 ],"float2ubyte")) runTypeConvert(argc,argv, float2ubyte);
 else if (readArg(argv[ 1 ],"calibrate")) calibrate(argc,argv); 
 else if (readArg(argv[ 1 ],"bip2bil")) interleave(argc,argv,bip2bil);
 else if (readArg(argv[ 1 ],"bil2bsq")) interleave(argc,argv,bil2bsq);
 else if (readArg(argv[ 1 ],"bip2bsq"))  interleave(argc,argv,bip2bsq);
 else if (readArg(argv[ 1 ],"bil2bip")) interleave(argc,argv,bil2bip); 
 else if (readArg(argv[ 1 ],"byte2text")) runTextConvert(argc,argv,byte2txt);
 else if (readArg(argv[ 1 ],"short2text")) runTextConvert(argc,argv,short2txt);
 else if (readArg(argv[ 1 ],"float2textSN")) runTextConvert(argc,argv,float2txtSN);
 else if (readArg(argv[ 1 ],"float2textRow")) runTextConvert(argc,argv,float2txtRow);
 else if (readArg(argv[ 1 ],"float2text")) runTextConvert(argc,argv,float2txt);
 else if (readArg(argv[ 1 ],"text2float")) runTxt2float(argc,argv); 
 else if (readArg(argv[ 1 ],"byte2ppm")) byte2ppm(argc,argv);
 else if (readArg(argv[ 1 ],"byte2ppm3")) byte2ppm3(argc,argv);
 else if (readArg(argv[ 1 ],"byte2pgm")) byte2pgm(argc,argv);
 else if (readArg(argv[ 1 ],"pgm2byte")) pgm2byte(argc,argv);
 else if (readArg(argv[ 1 ],"ppm2byte")) ppm2byte(argc,argv);
 else if (readArg(argv[ 1 ],"linear2dB")) runLinear2dB(argc, argv,  linear2dB);
 else if (readArg(argv[ 1 ],"dB2linear")) runLinear2dB(argc, argv,  dB2linear);
 else if (readArg(argv[ 1 ],"mkimg")) mkimg(argc, argv);
 else if (readArg(argv[ 1 ],"complex2RealImag")) complex(argc, argv, complex2RealImag);
 else if (readArg(argv[ 1 ],"complex2PwrPhase")) complex(argc, argv, complex2PwrPhase);
 else if (readArg(argv[ 1 ],"crop")) runCrop(argc, argv);
 else if (readArg(argv[ 1 ],"getPixelValue")) getPixelValue(argc, argv);
 else if (readArg(argv[ 1 ],"mosaic")) runMosaic(argc, argv);
 else if (readArg(argv[ 1 ],"getNumLines")) getNumLines(argc, argv);
 else if (readArg(argv[ 1 ],"getNumLinesAll")) getNumLinesAll(argc, argv);
 else if (readArg(argv[ 1 ],"calcTotalMean")) calcTotalMean(argc, argv);
 else if (readArg(argv[ 1 ],"sideCat")) sideCat(argc, argv);
 else if (readArg(argv[ 1 ],"areaCounter")) areaCounter(argc, argv);
 else if (readArg(argv[ 1 ],"reassign")) reassign(argc, argv);
 else if (readArg(argv[ 1 ],"confusion")) confusion(argc, argv);
 else if (readArg(argv[ 1 ],"modeFilter")) modeFilter(argc, argv);
 else if (readArg(argv[ 1 ],"meanFilter")) meanFilter(argc, argv);
 else if (readArg(argv[ 1 ],"mean")) mean(argc, argv);
 else if (readArg(argv[ 1 ],"bsq2dimap")) bsq2dimap(argc, argv);
 else if (readArg(argv[ 1 ],"dimap2bsq")) dimap2bsq(argc, argv);
 else if (readArg(argv[ 1 ],"standardise")) standardise(argc, argv);
 else if (readArg(argv[ 1 ],"anomalies")) anomalies(argc, argv);
 else if (readArg(argv[ 1 ],"georeference")) georeference(argc, argv);
 else if (readArg(argv[ 1 ],"resample")) resample(argc, argv);
 else if (readArg(argv[ 1 ],"texture"))  textureFilter(argc, argv);
 else if (readArg(argv[ 1 ],"regression")) regress(argc, argv);
 else if (readArg(argv[ 1 ],"rotate")) rotate(argc, argv);
 else if (readArg(argv[ 1 ],"covariance")) covarianceMatrix(argc, argv);
 else if (readArg(argv[ 1 ],"meanArea")) meanArea(argc, argv);
 else if (readArg(argv[ 1 ],"transect")) transect(argc, argv);
 else if (readArg(argv[ 1 ],"stats")) stats(argc, argv);
 else if (readArg(argv[ 1 ],"hist")) hist(argc, argv);
 else if (readArg(argv[ 1 ],"histoArea")) histoArea(argc, argv);
 else if (readArg(argv[ 1 ],"separability")) separability(argc, argv);
 else if (readArg(argv[ 1 ],"interpText")) interpText(argc, argv);
 else if (readArg(argv[ 1 ],"spectralResponse")) spectralResponse(argc, argv);
 else if (readArg(argv[ 1 ],"linear2Dinterp")) linear2Dinterp(argc, argv);
 else if (readArg(argv[ 1 ],"rad2ref")) rad2ref(argc, argv);
 else if (readArg(argv[ 1 ],"classify")) classify(argc, argv);
 else if (readArg(argv[ 1 ],"rows2cols")) rows2cols(argc, argv);
 else if (readArg(argv[ 1 ],"addNoise")) addNoise(argc, argv);
 else if (readArg(argv[ 1 ],"addNoiseImg")) addNoiseImg(argc, argv);
 else if (readArg(argv[ 1 ],"stdev")) stdv(argc, argv);
 else if (readArg(argv[ 1 ],"demSlope")) demSlope(argc, argv);
 else usageLeaf();
}



void usageLeaf(){
 
 char *help={
   "   Leaf - Basic image processing utility for Earth observation data\n\
   This is free and unencumbered software released into the public domain\n\
   Will Grey, 2015\n\n\
   Usage: leaf [options ....]\n\
   options:\n\n\
   Image manipulation tools:\n\
   -xflip \t \t Flips images left to right\n\
   -yflip \t \t Flips images up to down\n\
   -swap \t \t Byte swapping from little endian to big endian and vice versa\n\
   -crop    \t\t Extract sub area of an image\n\
   -rotate    \t\t Rotate images\n\
   -resample  \t\t Resamples raw binary image data using nearest-neighbour interpolation\n\
   -linear2Dinterp \t Perform 2D linear interpolation to upscale image \n\
   -shiftMeridian  \t In global datasets shift meridian from middle to edge\n\
   -georeference \t Georeference Earth observation images\n\
   -mkimg   \t\t Create a single value raw binary image file\n\
   -mosaic    \t\t Mosaic images\n\
   -getPixel    \t Extract pixel value from image\n\
   -transect    \t Extract pixel values along a transect between two points\n\
   -diff    \t\t Calculate the difference between two images\n\
   -add    \t \t Add two images\n\
   -ratio   \t\t Divide pixels values in image 1 by values in image 2 \n\
   -regression   \t Calculate regression between 2 images\n\
   -modulus   \t\t Make all pixel values positive\n\
   -mask   \t\t Apply mask to image\n\
   -thresh   \t\t Apply threshold to image\n\
   -calibrate   \t Apply gain and offset to image pixels \n\
   -rad2ref   \t\t Convert from radiance values to reflectance \n\n\
   Statistical analysis tools:\n\
   -covariance   \t Calculate covariance and correlation matrix between channels\n\
   -stats      \t\t Calculate univariate statistics of image channels\n\
   -hist    \t\t Calculates histogram of multi channel input data file\n\
   -histoArea   \t Calculates histogram of multi-channel input data file for each region\n\
   -anomalies \t \t Subtract image mean from pixel values\n\
   -standardise  \t Subtract image mean from pixel values and divide by standard deviation\n\
   -addNoiseImg  \t Box Muller transform to add Gaussian noise to image\n\
   -areaCounter  \t Count pixels in 1/0 binary value byte image\n\
   -meanArea  \t\t Calculates the statistics with regions\n\
   -mean    \t\t Calculate mean of sequence of input images\n\
   -stdev    \t\t Calculate standard deviation of sequence of input images\n\n\
   Filter tools:\n\
   -modeFilter \t \t Apply mode (majority) filter to byte image data\n\
   -meanFilter \t \t Apply mean filter\n\
   -texture \t \t Apply texture filter\n\n\
   Text processing tools:\n\
   -getNumLines   \t Get number of lines in a file excluding blank lines\n\
   -getNumLinesAll   \t Get number of lines in a file including blank lines\n\
   -calcTotalMean   \t Calculate total and mean of a text file\n\
   -sideCat   \t\t Concatonate 2 text files side by side\n\
   -rows2cols \t \t Converts rows to columns in text files \n\
   -addNoise \t \t Box Muller transform to add Gaussian noise to text file \n\
   -interpText   \t Perform linear interpolation on column in a text file\n\n\
   Classification tools:\n\
   -confusion \t \t Calculate confusion matrix for classified image\n\
   -classify     \t Classify images using basic box classifier\n\
   -separability   \t Calculate separability between classes for any number of channels\n\
   -reassign       \t Reassign values within byte image\n\n\
   Type conversion tools:\n\
   -byte2short  \t Convert from signed char to signed short integer\n\
   -byte2float  \t Convert from signed char to float\n\
   -byte2long  \t\t Convert from signed char to signed long integer\n\
   -float2byte  \t Convert from float to signed char\n\
   -long2float  \t Convert from signed long integer to float\n\
   -long2byte  \t\t Convert from signed long integer to signed char\n\
   -short2byte  \t Convert from signed short integer to signed char\n\
   -short2float  \t Convert from signed short integer to float\n\
   -short2long  \t Convert from signed short integer to signed long integer\n\
   -long2short  \t Convert from signed long integer to signed short integer\n\
   -ushort2float \t Convert from unsigned short integer to float\n\
   -ubyte2float \t Convert from unsigned char to float\n\
   -ubyte2ushort \t Convert from unsigned char to unsigned short integer\n\
   -ushort2ubyte \t Convert from unsigned short integer to unsigned char\n\
   -float2ubyte \t Convert from float to unsigned char\n\
   -long2ulong  \t Convert from long to unsigned long\n\
   -ulong2long  \t Convert from unsigned long to long\n\
   -short2ushort  \t Convert from short to unsigned short\n\
   -ushout2short  \t Convert from unsigned short to short\n\
   -ubyte2byte  \t Convert from unsigned char to char\n\
   -byte2ubyte  \t Convert from char to unsigned char\n\n\
   Format conversion tools:\n\
   -bsq2dimap  \t\t Convert from band sequential image to dimap\n\
   -dimap2bsq  \t\t Convert from dimap to band sequential image\n\
   -bip2bsq   \t\t Convert from byte interleave by pixel to band sequence\n\
   -bil2bsq   \t\t Convert from byte interleave by line to band sequence\n\
   -bil2bip   \t\t Convert from byte interleave by line to byte interleave by pixel\n\
   -bip2bil   \t\t Convert from byte interleave by pixel to byte interleave by line\n\
   -byte2text   \t Convert from char to ASCII text\n\
   -short2text   \t Convert from short int to ASCII text\n\
   -float2text   \t Convert from float to ASCII text\n\
   -float2textRow   \t Convert from float to ASCII text as row\n\
   -float2textSN   \t Convert from float to ASCII text in scientific notation\n\
   -text2float   \t Convert from ASCII text to float\n\
   -byte2pgm   \t\t Converts from binary byte data to pgm\n\
   -byte2ppm   \t\t Converts from binary byte data to ppm\n\
   -byte2ppm3   \t Converts from 3 channel byte data to ppm\n\
   -ppm2byte   \t\t Converts ppm to binary byte data\n\
   -pgm2byte  \t\t Converts pgm to binary byte data\n\n\
   Radar tools:\n\
   -linear2dB   \t Convert radar data from linear to dB values\n\
   -dB2linear   \t Convert radar data from dB to linear values\n\
   -complex2RealImag   \t Convert complex radar data to real and imaginary\n\
   -complex2PwrPhase   \t Convert complex radar data to power and phase\n\n\
   Miscellaneous tools:\n\
   -copy \t \t Copy binary data file\n\
   -header  \t\t Create ENVI header file\n\
   -spectralResponse  \t Calculate broad band spectral response given irriadiance and spectral response function\n\
   -demSlope \t\t Calculates the slope and aspect from an input DEM float image\n\
   -degConv  \t\t Convert between decimal degrees and degrees, minutes and seconds and vice versa\n\n\
"};

 fprintf(stderr,"%s\n",help);
 exit(EXIT_FAILURE);

}

int initialiseHdrData(metaData *hdrData){

 hdrData->flag=1;
 hdrData->bpp=2;
 hdrData->xdim=0;
 strcpy(hdrData->infile, "");
 strcpy(hdrData->outfile, OUTPUT_FILENAME);

 return(EXIT_SUCCESS);
}

