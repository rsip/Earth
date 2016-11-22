/*
NAME:		earth.h 
DESCRIPTION: 	header file for function prototypes	
AUTHOR:	 	Will Grey
VERSION:	2015-05-05	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#define MAXIMUM(x,y) ((x) > (y) ? (x) : (y) )
#define MINIMUM(x,y) ((x) < (y) ? (x) : (y) )
#define SQUARE(x) ((x) * (x))
#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof((x)[0]))
#define ABS(x) ((x) >= 0 ? (x) : (-x))
#define DTOR(x)(x*M_PI/180.0) 
#define RTOD(x)(x*180.0/M_PI) 

#define PI 3.1415926535897932
#define E 2.7182818284590452
#define MAX_PATH_NAME_LENGTH 1000 
#define NUM_DISTRIBUTION_BINS 100

#define ERR_TOL    1e-6
#define MAX_ITERS  200
#define TRIALS     1e5
#define SEED       1e3  
#define GOLDEN_RATIO (SQRT(5)-1)/2

#define T_TABLE_PROBABILITY 4
#define T_TABLE_DOF 36
#define CHI_TABLE_DOF 10
#define CHI_TABLE_PRBABILITY 3

#define MAX_DIR_NAME_SIZE 1000
#define MAX_NUM_GCPS 2000
#define MAX_LINE_LEN 20000

/* univariateStats.c */

typedef struct {
 double ave;
 double median;
 unsigned char majority;
 double max;
 double min;
 double range;
 double stdDev;
 double variance;
 double skewness;
 double kurtosis;
 double upperQuartile;
 double lowerQuartile;
 double interQuartileRange;
 double bestEstimateOfStDev;
 double StandardErrorOfStDev;
 double StandardErrorOfMean;
} univariateStats;

typedef struct {
 double fx;
 double x;
} pdf;

typedef struct  {
 double m;
 double c;
} regressionCoefficients;


/* univariateStats.c */
int sort(float *, int);
double ave(float  *, int);
unsigned char majority (unsigned char *, int);
long * histogram (unsigned char *, int);
double max(float  *, int);
double min(float  *, int);
double range(float  *, int);
double stdDev(float  *, int);
double skewness(float  *, int);
double kurtosis(float  *, int);
double lowerQuartile(float  *, int);
double upperQuartile(float  *, int);
double interQuartileRange(float  *, int);
double median(float  *, int);
double variance (float  *data, int n);
double bestEstimateOfStDev(float  *, int);
double StandardErrorOfStDev(float  *, int);
double StandardErrorOfMean(float  *, int);
int univStats(float  *, int, univariateStats *);
int univStatsByte(unsigned char *, int, univariateStats *);
double sum (float *, int);
int plotHisto(float *, int, float *, float *, float *, int, long *);

/* bivariateStats.c */
regressionCoefficients regression(float *, float *, int);
double correlation (float *, float *, int);
double covariance (float *, float *, int);
double rmse (float *, float *, int);
double bias (float *, float *, int);

/* simplex.c */
int repositionSimplex(short int *, double **, int);
int sortSimplex(double *, int, short int *);
int calcCentroid(double **, int, double *);
double simplexFit (double **, int , float *, float *, int, int);

/* golden.c */
float merit_function_golden(double *, float *, float *, int, int);
double goldenFit (double, double, float *, float *, int, int);
double * fit_variogram_model_golden(float *, float *, int, int);

/* matrix.c */
void freeDoubleVector(double * );
void freeFloatVector(float * );
void freeCharVector(unsigned char * );
void freeLongVector(long int * );
void freeShortVector(short int * );
double ** allocateDoubleMatrix(int, int);
float ** allocateFloatMatrix(int, int);
unsigned char ** allocateCharMatrix(int, int);
short int ** allocateShortMatrix(int, int);
long int ** allocateLongMatrix(int, int);
void freeDoubleMatrix(double **, int);
void freeFloatMatrix(float **, int);
void freeLongMatrix(long int **, int);
void freeShortMatrix(short int **, int);
void freeCharMatrix(unsigned char **, int);
double * allocateDoubleVector(int);
float * allocateFloatVector(int);
short int * allocateShortVector(int);
long int * allocateLongVector(int);
unsigned char * allocateCharVector(int);

double ** multiplyMatrix(double **, double **, int, int, int);
double ** trasposeMatrix(double **, int, int);
double * matrixToVector(double **, int, int);
double ** vectorToMatrix(double *, int, int);
double vectorLength(double *, int);
double ** addMatrix(double **, double **, int, int);
double ** subtractMatrix(double **, double **, int, int);
double ** mergeVector(double *, double *, int);
double ** createIdentityMatrix(int);
double ** scalarMultiplyMatrix(double **, double, int, int);
double ** diagonalMatrix(double **, int );
double * vectorInnerProduct(double *, double *, int);
double * vectorAddition(double *, double *, int);
double * vectorSubtract(double *, double *, int);
double * vectorDivision(double *, double *, int);
double * scalarMultiplyVector(double *, double, int);
double *  normalVector(double *, int);
double ** copyMatrix(double **, int, int);
double * copyVector(double *, int);
int printMatrix(double **, int, int);
int printVector(double *, int);
int resetMartixDoubleZero(double **, int, int);
int resetVectorDoubleZero(double *, int);

double matrixTrace(double **, int);
double * gaussianElimination (int, double **, double *);
double * backSubstitution (int, double **, double *);
double * forwardSubstitution (int, double **, double *);
double matrixDeterminant(double **, int);
double ** matrixInverse(double **, int);
double ** minorMatrix(double **, int, int, int);
double ** cofactorMatrix(double **, int);
int LUFactotisation (int, double **, double **, double **);
double * LUSolver(double **, double *, int);
double multipleCorrelation(double **, double *, int, int, double *);
double * multipleLinearRegression(double **, double *, int, int);
double * multiplyMatrixVector(double **, double *,  int, int);

