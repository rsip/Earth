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
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#include <dirent.h> 

#define MAX_FILE_NAME_SIZE 1000 
#define PIXELS 1000
#define MAX_PATH_NAME_LENGTH 1000
#define OUTPUT_FILENAME "output.img"

typedef struct {
 char infile[MAX_FILE_NAME_SIZE];
 char outfile[MAX_FILE_NAME_SIZE]; 
 int bpp;
 int xdim;
 int flag;
 char routine[MAX_FILE_NAME_SIZE]; 
} clparse ;

typedef union data
{
   char  *c;
   short *i;
   float *f;
   double *d;
   void   *s;
} data_t;

/* utility.c */
float * convertShort2Float(unsigned short int *, int);
float * convertLong2Float(unsigned long int *, int);
float * convertDouble2Float(double *, int);
float * convertByte2Float(unsigned char *, int);
int counter(unsigned int, unsigned int);
int createEnviHeader(char *, char *, int, int, int, int);
int dimap(char *);
FILE *openFile(char *, char *, char *);
int memoryCheck(void);
double timer(void);
float *readFloatData(char *, char *, int);

/* leaf.c */
void readClinput(int, char **, clparse *);
int checkOption(char *, char *);

/* swap.c */
int swap(clparse *clinput);
int byteSwap(void *, int, int);

/* flip.c */
int xFlip(unsigned char *, unsigned char *, int, int, int);
int yFlip(unsigned char *, unsigned char *, int, int, int);
int flip(FILE *, FILE *, int, int, int, int);
int flipImg(clparse *);
int xFlip8(data_t *, data_t *, int, int, int);
int xFlip16(data_t *, data_t *, int, int, int);
int xFlip32(data_t *, data_t *, int, int, int);
int xFlip64(data_t *, data_t *, int, int, int);
int yFlip8(data_t *, data_t *, int, int, int);
int yFlip16(data_t *, data_t *, int, int, int);
int yFlip32(data_t *, data_t *, int, int, int);
int yFlip64(data_t *, data_t *, int, int, int);

