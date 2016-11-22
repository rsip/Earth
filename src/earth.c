/*
NAME:		earth.c 
DESCRIPTION: 	Basic image processing tool for
                Earth observation data
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int main(int argc, char **argv)
{
 
 if (argc <= 1) usageEarth();
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
 else if (readArg(argv[ 1 ],"demShade")) demShade(argc, argv);
 else if (readArg(argv[ 1 ],"ndvi")) ndvi(argc, argv);
 else if (readArg(argv[ 1 ],"meanWindow")) meanWindow(argc, argv);
 else if (readArg(argv[ 1 ],"ar")) ar(argc, argv);
 else if (readArg(argv[ 1 ],"autoregressive")) autoregressive(argc, argv);
 else if (readArg(argv[ 1 ],"demVolume")) demVolume(argc, argv);
 else if (readArg(argv[ 1 ],"areaCalc")) areaCalc(argc, argv);
 else if (readArg(argv[ 1 ],"solpos")) zenith(argc, argv);
 else if (readArg(argv[ 1 ],"trainCA")) trainCA(argc, argv);
 else if (readArg(argv[ 1 ],"automata")) automata(argc, argv);
 else if (readArg(argv[ 1 ],"tsspec")) tsspec(argc, argv);
 else if (readArg(argv[ 1 ],"crosspec")) crosspec(argc, argv);
 else if (readArg(argv[ 1 ],"colocate")) colocate(argc, argv);
 else if (readArg(argv[ 1 ],"kriging")) kriging(argc, argv);
 else if (readArg(argv[ 1 ],"kriging_point")) kriging_point(argc, argv);
 else if (readArg(argv[ 1 ],"byte2bits")) runBitConvert(argc, argv, byte2bit);
 else if (readArg(argv[ 1 ],"bits2byte")) runBitConvert(argc, argv, bit2byte);
 else if (readArg(argv[ 1 ],"eval_clusters")) run_eval_clusters(argc, argv);
 else if (readArg(argv[ 1 ],"remove_small_clusters_byte")) run_clusters(argc, argv, remove_small_clusters_byte);
 else if (readArg(argv[ 1 ],"remove_small_clusters_int")) run_clusters(argc, argv, remove_small_clusters_int);
 else if (readArg(argv[ 1 ],"remove_big_clusters_byte")) run_clusters(argc, argv, remove_big_clusters_byte); 
 else if (readArg(argv[ 1 ],"remove_big_clusters_int")) run_clusters(argc, argv, remove_big_clusters_int);
 else if (readArg(argv[ 1 ],"count_clusters_byte")) run_count_clusters(argc, argv, count_clusters_byte); 
 else if (readArg(argv[ 1 ],"count_clusters_int")) run_count_clusters(argc, argv, count_clusters_int);
 else if (readArg(argv[ 1 ],"bivariate")) bivariate_stats(argc, argv);
 else if (readArg(argv[ 1 ],"univariate")) univariate(argc, argv);
 else if (readArg(argv[ 1 ],"histText")) histText(argc, argv);
 else if (readArg(argv[ 1 ],"maxImg")) maxImg(argc, argv);
 else if (readArg(argv[ 1 ],"minImg")) minImg(argc, argv);
 else usageEarth();
}



void usageEarth(){
 
 char *help={
   "   Earth - Basic image processing utility for Earth observation data\n\
   This is free and unencumbered software released into the public domain\n\
   Will Grey, 2015\n\n\
   Usage: earth [options ....]\n\
   options:\n\n\
   Image manipulation tools:\n\
   -xflip                        Flips images left to right\n\
   -yflip                        Flips images up to down\n\
   -swap                         Byte swapping from little endian to big endian and vice versa\n\
   -crop                         Extract sub area of an image\n\
   -rotate                       Rotate images\n\
   -resample                     Resamples raw binary image data using nearest-neighbour interpolation\n\
   -linear2Dinterp               Perform 2D linear interpolation to upscale image \n\
   -shiftMeridian                In global datasets shift meridian from middle to edge\n\
   -georeference                 Georeference Earth observation images\n\
   -colocate                     Find offset between pair of images \n\
   -mkimg                        Create a single value raw binary image file\n\
   -mosaic                       Mosaic images\n\
   -getPixel                     Extract pixel value from image\n\
   -transect                     Extract pixel values along a transect between two points\n\
   -diff                         Calculate the difference between two images\n\
   -add                          Add two images\n\
   -ratio                        Divide pixels values in image 1 by values in image 2 \n\
   -ndvi                         Calculate normalised difference vegetation index \n\
   -regression                   Calculate regression between 2 images\n\
   -modulus                      Make all pixel values positive\n\
   -mask                         Apply mask to image\n\
   -thresh                       Apply threshold to image\n\
   -calibrate                    Apply gain and offset to image pixels \n\
   -rad2ref                      Convert from radiance values to reflectance \n\n\
   Statistical analysis tools:\n\
   -covariance                   Calculate covariance and correlation matrix between channels\n\
   -stats                        Calculate univariate statistics of image channels\n\
   -hist                         Calculates histogram of multi channel input data file\n\
   -histoArea                    Calculates histogram of multi-channel input data file for each region\n\
   -anomalies                    Subtract image mean from pixel values\n\
   -standardise                  Subtract image mean from pixel values and divide by standard deviation\n\
   -addNoiseImg                  Box Muller transform to add Gaussian noise to image\n\
   -areaCounter                  Count pixels in 1/0 binary value byte image\n\
   -meanArea                     Calculates the statistics with regions\n\
   -mean                         Calculate mean pixel value of sequence of input images\n\
   -maxImg                       Calculate maximum pixel value of sequence of input images\n\
   -minImg                       Calculate minimum pixel value of sequence of input images\n\
   -stdev                        Calculate standard deviation of sequence of input images\n\
   -areaCalc                     Calculate area \n\
   -kriging                      Kriging interpolation \n\
   -kriging_point                get Kriged estimate of a point \n\
   -autoregressive               AR over sequence of images\n\n\
   Filter tools:\n\
   -modeFilter                   Apply mode (majority) filter to byte image data\n\
   -meanFilter                   Apply mean filter\n\
   -texture                      Apply texture filter\n\n\
   Text processing tools:\n\
   -getNumLines                  Get number of lines in a file excluding blank lines\n\
   -getNumLinesAll               Get number of lines in a file including blank lines\n\
   -calcTotalMean                Calculate total and mean of a text file\n\
   -univariate                   Calculate univariate statistics of a 1 column text file \n\
   -histText                     Calculate histogram of a 1 column text file \n\
   -bivariate                    Calculate bivariate statistics of a 2 column text file \n\
   -sideCat                      Concatonate 2 text files side by side\n\
   -rows2cols                    Converts rows to columns in text files \n\
   -addNoise                     Box Muller transform to add Gaussian noise to text file \n\
   -interpText                   Perform linear interpolation on column in a text file\n\
   -ar                           Calculate AR between 2 columns of data \n\
   -meanWindow                   Perform smoothing using mean filter\n\
   -tsspec                       Calculate time series spectra\n\
   -crosspec                     Calculate cross spectra of time series data\n\n\
   Classification tools:\n\
   -confusion                    Calculate confusion matrix for classified image\n\
   -classify                     Classify images using basic box classifier\n\
   -separability                 Calculate separability between classes for any number of channels\n\
   -trainCA                      Train transition rules for cellular automata \n\
   -automata                     Run Cellular Automata Markov simulation \n\
   -reassign                     Reassign values within byte image\n\
   -eval_clusters                Evaluate accuracy of change images\n\
   -remove_big_clusters_int      Remove big clusters (Integer) \n\
   -remove_small_clusters_int    Remove small clusters (Integer) \n\
   -remove_small_clusters_byte   Remove small clusters (char) \n\
   -remove_big_clusters_byte     Remove small clusters (char) \n\
   -count_clusters_byte          Counts clusters in a 1 / 0 binary image \n\
   -count_clusters_int           Counts clusters in a 1 / 0 binary image \n\n\
   Type conversion tools:\n\
   -byte2short                   Convert from signed char to signed short integer\n\
   -byte2float                   Convert from signed char to float\n\
   -byte2long                    Convert from signed char to signed long integer\n\
   -float2byte                   Convert from float to signed char\n\
   -long2float                   Convert from signed long integer to float\n\
   -long2byte                    Convert from signed long integer to signed char\n\
   -short2byte                   Convert from signed short integer to signed char\n\
   -short2float                  Convert from signed short integer to float\n\
   -short2long                   Convert from signed short integer to signed long integer\n\
   -long2short                   Convert from signed long integer to signed short integer\n\
   -ushort2float                 Convert from unsigned short integer to float\n\
   -ubyte2float                  Convert from unsigned char to float\n\
   -ubyte2ushort                 Convert from unsigned char to unsigned short integer\n\
   -ushort2ubyte                 Convert from unsigned short integer to unsigned char\n\
   -float2ubyte                  Convert from float to unsigned char\n\
   -long2ulong                   Convert from long to unsigned long\n\
   -ulong2long                   Convert from unsigned long to long\n\
   -short2ushort                 Convert from short to unsigned short\n\
   -ushout2short                 Convert from unsigned short to short\n\
   -ubyte2byte                   Convert from unsigned char to char\n\
   -byte2ubyte                   Convert from char to unsigned char\n\
   -byte2bits                    Convert from bits to bytes\n\
   -bits2byte                    Convert from bytes to bits\n\n\
   Format conversion tools:\n\
   -bsq2dimap                    Convert from band sequential image to dimap\n\
   -dimap2bsq                    Convert from dimap to band sequential image\n\
   -bip2bsq                      Convert from byte interleave by pixel to band sequence\n\
   -bil2bsq                      Convert from byte interleave by line to band sequence\n\
   -bil2bip                      Convert from byte interleave by line to byte interleave by pixel\n\
   -bip2bil                      Convert from byte interleave by pixel to byte interleave by line\n\
   -byte2text                    Convert from char to ASCII text\n\
   -short2text                   Convert from short int to ASCII text\n\
   -float2text                   Convert from float to ASCII text\n\
   -float2textRow                Convert from float to ASCII text as row\n\
   -float2textSN                 Convert from float to ASCII text in scientific notation\n\
   -text2float                   Convert from ASCII text to float\n\
   -byte2pgm                     Converts from binary byte data to pgm\n\
   -byte2ppm                     Converts from binary byte data to ppm\n\
   -byte2ppm3                    Converts from 3 channel byte data to ppm\n\
   -ppm2byte                     Converts ppm to binary byte data\n\
   -pgm2byte                     Converts pgm to binary byte data\n\n\
   Radar tools:\n\
   -linear2dB                    Convert radar data from linear to dB values\n\
   -dB2linear                    Convert radar data from dB to linear values\n\
   -complex2RealImag             Convert complex radar data to real and imaginary\n\
   -complex2PwrPhase             Convert complex radar data to power and phase\n\n\
   Digital Elevation Model tools:\n\
   -demSlope                     Calculates the slope and aspect from an input DEM float image\n\
   -demShade                     Creates shaded relief map from DEM\n\
   -demVolume                    Calculate volume of a DEM difference \n\n\
   Miscellaneous tools:\n\
   -copy                         Copy binary data file\n\
   -header                       Create ENVI header file\n\
   -spectralResponse             Calculate broad band spectral response given irriadiance and spectral response function\n\
   -degConv                      Convert between decimal degrees and degrees, minutes and seconds and vice versa\n\
   -solpos                       Calculate solar azimuth and zenith angles\n\n\
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

