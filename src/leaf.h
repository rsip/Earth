/*
NAME:		leaf.h 
DESCRIPTION: 	Header file
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h> 

#include <numerical.h>

#define MAGIC_NUM_LEN 2
#define MAX_LINE_LEN 20000
#define MAX_NUM_FILES 1000
#define MAX_NUM_COLS 200
#define MAX_NUM_LINES 1000
#define MAX_FILE_LINES 10000
#define MAX_FILE_NAME_SIZE 1000 
#define PIXELS 1000
#define MAX_PATH_NAME_LENGTH 1000
#define ENVI_HEADER_LINE_LEN 1000
#define HEADER ".hdr"
#define OUTPUT_FILENAME "output.img"
#define MAX_COLOURS 27
#define TEXT_LINE_LEN 1000
#define NUM_CLASSES 256
#define MAX_DIR_NAME_SIZE 1000
#define MAX_NUM_GCPS 2000
#define MAX_NUM_CHANNELS 100
#define ANGLE_TOL 0.5
#define PPM_FACTOR 12

#define SPEED_OF_LIGHT 2.997925e8
#define PLANCK_CONSTANT 6.626068e-34
#define BOLTZMANN_CONSTANT 1.38066e-23
#define TEMPERATURE_SUN 6000

#define SPECTRAL_RESOLUTION 2400
#define SOLAR_SPEC_MIN 100
#define SOLAR_SPEC_MAX 2500

typedef struct {
 char infile[MAX_FILE_NAME_SIZE];
 char infile2[MAX_FILE_NAME_SIZE];
 char outfile[MAX_FILE_NAME_SIZE];
 char inhdr[MAX_FILE_NAME_SIZE]; 
 char outhdr[MAX_FILE_NAME_SIZE];  
 int bpp;
 int xdim;
 int ydim;
 int xdimOut;
 int ydimOut;
 int xdim2;
 int ydim2;
 int flag;
 int byteOrder;
 int channels;
 int dataType;
 int xoffset;
 int yoffset;
 int xscale;
 int yscale;
 int xoffset2;
 int yoffset2;
 int xsize;
 int ysize;
 int xpos;
 int ypos;
 int pixels;
 float gain;
 float offset;
 float ignoreZeroValue;
 int ignoreValue;
 int nullValue;
 int classes;
 int lines; 
} metaData ;



typedef union data
{
   char  *c;
   short *i;
   float *f;
   double *d;
   void   *s;
} data_t;

typedef struct {
 int pixels;
 unsigned char nClasses;
 unsigned long matrix[NUM_CLASSES][NUM_CLASSES];
 unsigned long rowTotal[NUM_CLASSES];
 unsigned long colTotal[NUM_CLASSES];
 unsigned long correct[NUM_CLASSES];
 unsigned long totalCorrect;
 float matrixPercent[NUM_CLASSES][NUM_CLASSES];
 float observed;
 float expected;
 float kappa;
 float accuracy;
 float comErr[NUM_CLASSES];
 float omErr[NUM_CLASSES];
 float userAcc[NUM_CLASSES];
 float prodAcc[NUM_CLASSES];  
} conf ;

typedef struct {
 float startVal;
 float interval;
 float endVal;
 int cols;
 int skip; 
 int lines;
} interp ;

/* utility.c */
int dataType2bpp(int);
float * convertShort2Float(unsigned short int *, int);
float * convertLong2Float(unsigned long int *, int);
float * convertDouble2Float(double *, int);
float * convertByte2Float(unsigned char *, int);
int counter(unsigned int, unsigned int);
int createEnviHeader(char *, char *, metaData *);
int readEnviHeader(char *, char *, metaData *);
FILE *openFile(char *, char *, char *);
int memoryCheck(void);
double timer(void);
float *readFloatData(char *, char *, int);
int checkFileExists(char *f);
int fileReadError(char *);
int fileSizeErr(char *, char *);
int compareFileSize(char *, char *);
char * itoa(int);
int getYdim(char *, metaData *);
int getYdim2(char *, metaData *);
int getPixels(char *, metaData *);
int diagnosticTest(metaData *);

/* leaf.c */
void readHdrData(int , char **);
void usageLeaf();
int initialiseHdrData(metaData *hdrData);
int readArg(char *, char *);

/* header.c */
int runHeader(int, char **);
void hdrUsage();

/* convertType.c */
int runTypeConvert(int, char **, int (*f)(metaData *));
void usageType(char *);
int byte2short(metaData *);
int byte2float(metaData *);
int byte2long(metaData *);
int float2byte(metaData *);
int long2float(metaData *);
int long2byte(metaData *);
int short2byte(metaData *);
int short2float(metaData *);
int short2long(metaData *);
int long2short(metaData *);
int byte2ubyte(metaData *);
int ubyte2byte(metaData *);
int short2ushort(metaData *);
int ushort2short(metaData *);
int long2ulong(metaData *);
int ulong2long(metaData *);
int ushort2float(metaData *);
int ubyte2ushort(metaData *);
int ubyte2float(metaData *);
int ushort2ubyte(metaData *);
int float2ubyte(metaData *);



/* copy.c */
int runCopy(int, char **);
int copy(metaData *);
void copyUsage();

/* swap.c */
int swap(metaData *);
int byteSwap(void *, int, int);
int runSwap(int, char **);
void swapUsage();

/* flip.c */
int yflip(FILE *, FILE *,  metaData *);
int xflip(FILE *, FILE *,  metaData *);
void flipUsage(char *);
int flip(int, char **, int (*f)(FILE *, FILE *, metaData *));

/* diffImg.c */
int diffDouble (FILE *fin1, FILE *fin2, FILE *fout);
int diffFloat (FILE *fin1, FILE *fin2, FILE *fout);
int diffShort (FILE *fin1, FILE *fin2, FILE *fout);
int diffLong(FILE *fin1, FILE *fin2, FILE *fout);
int diffByte (FILE *fin1, FILE *fin2, FILE *fout);
int diff(int, char **);

/* add.c */
int addDouble (FILE *fin1, FILE *fin2, FILE *fout);
int addFloat (FILE *fin1, FILE *fin2, FILE *fout);
int addShort (FILE *fin1, FILE *fin2, FILE *fout);
int addLong(FILE *fin1, FILE *fin2, FILE *fout);
int addByte (FILE *fin1, FILE *fin2, FILE *fout);
void arithmaticUsage(char *);
int add(int, char **);

/* ratioImg.c */
int ratioDouble (FILE *fin1, FILE *fin2, FILE *fout);
int ratioFloat (FILE *fin1, FILE *fin2, FILE *fout);
int ratioShort (FILE *fin1, FILE *fin2, FILE *fout);
int ratioLong(FILE *fin1, FILE *fin2, FILE *fout);
int ratioByte (FILE *fin1, FILE *fin2, FILE *fout);
int ratio(int, char **);

/* modImg.c */
int modDouble (FILE *fin, FILE *fout);
int modFloat (FILE *fin, FILE *fout);
int modShort (FILE *fin, FILE *fout);
int modLong(FILE *fin, FILE *fout);
int modByte (FILE *fin, FILE *fout);
void modUsage();
int modulus(int, char **);

/* mask.c */
int maskDouble (FILE *fin1, FILE *fin2, FILE *fout);
int maskFloat (FILE *fin1, FILE *fin2, FILE *fout);
int maskShort (FILE *fin1, FILE *fin2, FILE *fout);
int maskLong (FILE *fin1, FILE *fin2, FILE *fout);
int maskByte (FILE *fin1, FILE *fin2, FILE *fout);
void maskUsage();
int mask(int , char **);

/* thresh.c */
int threshDouble (FILE *fin, FILE *fout, float, float);
int threshFloat (FILE *fin, FILE *fout, float, float);
int threshShort (FILE *fin, FILE *fout, float, float);
int threshLong(FILE *fin, FILE *fout, float, float);
int threshByte (FILE *fin, FILE *fout, float, float);
void threshUsage();
int thresh(int, char **);

/* calibrate.c */
int calibrateByte(FILE *, FILE *, metaData *, float *, float *);
int calibrateShort(FILE *, FILE *, metaData *, float *, float *);
int calibrateLong(FILE *, FILE *, metaData *, float *, float *);
int calibrateFloat(FILE *, FILE *, metaData *, float *, float *);
int calibrateDouble(FILE *, FILE *, metaData *, float *, float *);
void calibrateUsage();
int calibrate(int, char **);
int readGainOffset(FILE *, float *, float *);

/* interleave.c */
int bil2bip(FILE *fin, FILE *fout, metaData *hdrData);
int bip2bsq(FILE *fin, FILE *fout, metaData *hdrData);
int bip2bil(FILE *fin, FILE *fout, metaData *hdrData);
int bil2bsq(FILE *fin, FILE *fout, metaData *hdrData);
void interleaveUsage(char *tool);
int interleave(int argc, char **argv, int (*f)(FILE *, FILE *, metaData *));

/* bin2text.c */
int float2txtRow(metaData *);
int float2txt(metaData *);
int float2txtSN(metaData *);
int short2txt(metaData *);
int byte2txt(metaData *);
int runTextConvert(int, char **, int (*f)(metaData *));
void usageTextConvert(char *);

/* shiftMeridian.c */
int meridian(FILE *, FILE *,  metaData *);
int shiftMeridian(int, char **);

/* degConv.c */
void degUsage();
int degConv(int argc, char *argv[]);

/* byte2pgm.c byte2ppm.c ppm2byte.c pgm2byte.c */ 
int byte2pgm(int argc, char *argv[]);
int byte2ppm(int argc, char *argv[]);
int ppm2byte(int argc, char *argv[]);
int pgm2byte(int argc, char *argv[]);
int byte2ppm3(int argc, char *argv[]);

/* linear2dB.c */
void linear2dBUsage(char *);
int dB2linear(FILE *, FILE *, float *, float *, metaData *, float);
int linear2dB(FILE *, FILE *, float *, float *, metaData *, float);
int linear2dBImg(metaData *, float , int (*f)(FILE *, FILE *, float *, float *, metaData *, float));
int runLinear2dB(int , char **, int (*f)(FILE *, FILE *, float *, float *, metaData *, float));

/* mkimg.c */
int mkimgDouble (FILE *, metaData *, double);
int mkimgFloat (FILE *, metaData *, float);
int mkimgLong (FILE *, metaData *, long);
int mkimgShort (FILE *, metaData *, short);
int mkimgByte (FILE *, metaData *, char);
void mkimgUsage();
int mkimg(int, char **);

/* complex.c */
void complexUsage(char *);
int complex2RealImag(FILE *, FILE *, FILE *);
int complex2PwrPhase(FILE *, FILE *, FILE *);
int complex(int, char **,int (*f)(FILE *, FILE *, FILE *));

/* crop.c */
void cropUsage();
int crop(FILE *, FILE *, metaData *);
int runCrop(int, char **);

/* getPixel.c */
void getPixelUsage();
int getPixel(FILE *, metaData *);
int getPixelValue(int, char **);

/* mosaic.c */
void mosaicUsage();
int mosaic(FILE *, FILE *, metaData *);
int runMosaic(int, char **);

/* text.c */
int getNumLines(int, char **);
int getNumLinesAll(int, char **);
int calcTotalMean(int, char **);
void textUsage(char *);
void sideCatUsage(char *);
int sideCat(int,  char **);

/* areaCounter.c */
int areaCounter(int, char **);
void areaUsage();

/* reassign.c */
void reassignUsage();
int reassignImage(FILE *, FILE *, int *, int *, int);
int reassignVal(FILE *, int *, int *);
int reassign(int, char **);

/* confusion.c */
int confusionUsage();
int printConfusion(FILE *, conf *, char *);
int confusion(int, char **);

/* modeFilter.c */
int modeUsage();
void mode(FILE *, FILE *, int, int, int);
int modeFilter(int, char **);

/* meanFilter.c */
int meanFiltUsage();
void meanDouble(FILE *, FILE *, int, int, int);
void meanFloat(FILE *, FILE *, int, int, int);
void meanLong(FILE *, FILE *, int, int, int);
void meanShort(FILE *, FILE *, int, int, int);
void meanByte(FILE *, FILE *, int, int, int);
int meanFilter(int, char **);

/* mean.c */
int meanImgDouble(FILE **, FILE *, metaData *, int);
int meanImgFloat(FILE **, FILE *, metaData *, int);
int meanImgLong(FILE **, FILE *, metaData *, int);
int meanImgShort(FILE **, FILE *, metaData *, int);
int meanImgByte(FILE **, FILE *, metaData *, int);
void meanUsage();
FILE ** openMultipleFiles(FILE *, int *);
int mean(int, char **);

/* stdev.c */
int stdevImgDouble(FILE **, FILE *, metaData *, int);
int stdevImgFloat(FILE **, FILE *, metaData *, int);
int stdevImgLong(FILE **, FILE *, metaData *, int);
int stdevImgShort(FILE **, FILE *, metaData *, int);
int stdevImgByte(FILE **, FILE *, metaData *, int);
void stdevUsage();
int stdv(int, char **);

/* anomalies.c */
int anomaliesByte(FILE *, FILE *, metaData *);
int anomaliesShort(FILE *, FILE *, metaData *);
int anomaliesLong(FILE *, FILE *, metaData *);
int anomaliesFloat(FILE *, FILE *, metaData *);
int anomaliesDouble(FILE *, FILE *, metaData *);
void anomaliesUsage(char *);
int anomalies(int argc, char **argv);

/* bsq2dimap.c */
int splitFile(FILE *, FILE **, metaData *);
void bsq2dimapUsage();
FILE ** openMultipleWriteFiles(int, char *, char *);
int bsq2dimap(int , char **);

/* dimap2bsq.c */
int checkFileDir(char *);
int getNumFiles(char *);
FILE ** openMultipleReadFiles(char *, int);
int catFile(FILE **, FILE *, metaData *);
void dimap2bsqUsage();
int dimap2bsq(int argc, char **argv);

/* standardise.c */
int standardiseByte(FILE *, FILE *, metaData *);
int standardiseShort(FILE *, FILE *, metaData *);
int standardiseLong(FILE *, FILE *, metaData *);
int standardiseFloat(FILE *, FILE *, metaData *);
int standardiseDouble(FILE *, FILE *, metaData *);
int standardise(int argc, char **argv);

/* georeference.c */
int calcOutputDims(int, int, double *, double *, int *, int *, int *, int *);
int mapImgByte(double **, int, int, int, int, char *, char *, int, int, int, int);
int mapImgShort(double **, int, int, int, int, char *, char *, int, int, int, int);
int mapImgLong(double **, int, int, int, int, char *, char *, int, int, int, int);
int mapImgFloat(double **, int, int, int, int, char *, char *, int, int, int, int);
int mapImgDouble(double **, int, int, int, int, char *, char *, int, int, int, int);
double *calcLeastSquaresGCP(double **, double *, int);
int readGCPFile(char *, double **, double *, double *);
double **runMatrixInverse(double *, double *, int);
int georeference(int, char **);
void georeferenceUsage();

/* resample.c */
int resampleNearestNeighbour (FILE *, FILE *, double, metaData *);
void resampleUsage();
int resample(int, char **);

/* texture.c */
int textureFiltUsage();
void textureDouble(FILE *, FILE *, int, int, int);
void textureFloat(FILE *, FILE *, int, int, int);
void textureLong(FILE *, FILE *, int, int, int);
void textureShort(FILE *, FILE *, int, int, int);
void textureByte(FILE *, FILE *, int, int, int);
int textureFilter(int, char **);

/* regression.c */
int regressionDouble (FILE *, FILE *, FILE *, int);
int regressionFloat (FILE *, FILE *, FILE *, int);
int regressionLong (FILE *, FILE *, FILE *, int);
int regressionShort (FILE *, FILE *, FILE *, int);
int regressionByte (FILE *, FILE *, FILE *, int);
void regressionUsage();
int regress(int, char **);

/* rotate.c */
void rotateUsage();
int calcOutputDimsRotate(int, int, float, float, int *, int *, int *, int *);
int mapImg(float, float, int, int, int, int, FILE *, FILE *, int, int, int, int, int);
int rotate270(FILE *, FILE *, metaData *);
int rotate180(FILE *, FILE *, metaData *);
int rotate90(FILE *, FILE *, metaData *);
int rotate(int, char **);

/* covarianceMatrix.c */
int printCovCorr(double **, int);
int covarianceDouble(FILE *, metaData *);
int covarianceFloat (FILE *, metaData *);
int covarianceLong (FILE *, metaData *p);
int covarianceShort (FILE *, metaData *p);
int covarianceByte (FILE *, metaData *p);
void covarianceUsage();
int covarianceMatrix(int, char **);

/* meanArea.c */
int meanAreaByte (FILE *, FILE *, metaData *);
int meanAreaDouble (FILE *, FILE *, metaData *);
int meanAreaFloat (FILE *, FILE *, metaData *);
int meanAreaLong (FILE *, FILE *, metaData *);
int meanAreaShort (FILE *, FILE *, metaData *);
void meanAreaUsage();
int meanArea(int, char **);

/* transect.c */
void getTransectUsage();
int getTransectDouble(FILE *, metaData *, int *, int *, int);
int getTransectLong(FILE *, metaData *, int *, int *, int);
int getTransectShort(FILE *, metaData *, int *, int *, int );
int getTransectByte(FILE *, metaData *, int *, int *, int);
int getTransectFloat(FILE *, metaData *, int *, int *, int);
int getTransect(metaData *, int *, int *);
int transect(int, char **);

/* stats.c */
int statsDouble (FILE *, metaData *);
int statsLong (FILE *, metaData *);
int statsShort (FILE *, metaData *);
int statsFloat (FILE *, metaData *);
int statsByte (FILE *, metaData *);
void statsUsage();
int printStats(univariateStats);
int stats(int, char **);

/* histogram.c */
int histoLong(FILE *, metaData *, int);
int histoShort(FILE *, metaData *, int);
int histoDouble(FILE *, metaData *, int);
int histoFloat (FILE *, metaData *, int);
int histoByte (FILE *, metaData *);
void histogramUsage();
int hist(int, char **);
int printHisto(int, float, float, float, int, int, long *);
int plotHisto(float *, int, float *, float *, float *, int, long *);

/* histoArea.c */
int histoCls (int, unsigned char *, float *, float *, metaData *, int);
int histoAreaFloat (FILE *, FILE *, metaData *, int);
int histoAreaShort (FILE *, FILE *, metaData *, int);
int histoAreaLong (FILE *, FILE *, metaData *, int);
int histoAreaDouble (FILE *, FILE *, metaData *, int);
int histogramByte(unsigned char *, int);
int histoAreaByte (FILE *, FILE *, metaData *);
void histoAreaUsage();
int histoArea(int, char **);

/* classify.c */
int readClassFile(FILE *, int *, int *, float [][NUM_CLASSES][MAX_NUM_CHANNELS]);
void classifyUsage();
int classifyDouble(FILE *, FILE *, metaData *, float [][NUM_CLASSES][MAX_NUM_CHANNELS]);
int classifyLong(FILE *, FILE *, metaData *, float [][NUM_CLASSES][MAX_NUM_CHANNELS]);
int classifyShort(FILE *, FILE *, metaData *, float [][NUM_CLASSES][MAX_NUM_CHANNELS]);
int classifyByte(FILE *, FILE *, metaData *, float [][NUM_CLASSES][MAX_NUM_CHANNELS]);
int classifyFloat(FILE *, FILE *, metaData *, float [][NUM_CLASSES][MAX_NUM_CHANNELS]);
int classify(int, char **);

/* separability.c */
int calcJM(int *);
void separabilityUsage();
int recursion(int, int *, int (*f)(int *));
int readHistFile(FILE *f, int *, int *);
int separability(int, char **);

/* interpText.c */
void interpUsage();
int readTextFile(int *, int *, float [][MAX_FILE_LINES], int, char *);
int interpolCol(interp *, float [][MAX_FILE_LINES], char *);
int interpText(int, char **);

/* spectralResponse.c */
void spectralUsage();
int spectralVal(FILE *, float *, double *);
int planck(double *);
int spectralResponse(int, char **);
float convolve (float *, float *, float *, double *, int);

/* linear2Dinterp.c */
int interpolReg2DGrid(metaData *);
void linear2DinterpUsage();
int linear2Dinterp(int, char **);

/* rad2ref.c */
int rad2refFloat(FILE *, FILE *, FILE *, metaData *, float *, float);
int rad2refDouble(FILE *, FILE *, FILE *, metaData *, float *, float);
int rad2refLong(FILE *, FILE *, FILE *, metaData *, float *, float);
int rad2refShort(FILE *, FILE *, FILE *, metaData *, float *, float);
int rad2refByte(FILE *, FILE *, FILE *, metaData *, float *, float);
int readIrradianceFile(FILE *, float *, int);
void rad2refUsage();
int rad2ref(int, char **);

/* rows2cols.c */
int rows2cols(int, char **);

/* txt2float.c */
int txt2float(metaData *);
void usageTxt2float(char *);
int runTxt2float(int, char **);

/* noise.c */
double generateGaussianNoise(double, double);
void noiseUsage();
int addNoise(int, char **);

/* noiseImg.c */
int addNoiseImgDouble(FILE *, FILE *, double);
int addNoiseImgLong(FILE *, FILE *, double);
int addNoiseImgShort(FILE *, FILE *, double);
int addNoiseImgByte(FILE *, FILE *, double);
int addNoiseImgFloat(FILE *, FILE *, double);
void addNoiseImgUsage();
int addNoiseImg(int, char **);

/* demSlope */
int demSlopeFloat(FILE *, FILE *, FILE *, metaData *, float);
void demSlopeUsage();
int demSlope(int, char **);
