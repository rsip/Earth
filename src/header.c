/*
NAME:		header.c 
DESCRIPTION: 	Create ENVI header file
AUTHOR:	 	Will Grey
VERSION:	2015-10-29	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
COMPILE:        gcc flip.c utility.c -o flip -Wall
*/


#include "earth.h"


int runHeader(int argc, char **argv){
 
 metaData hdrData;
 initialiseHdrData(&hdrData);

 hdrData.byteOrder=1;
 
 if (argc < 7)
  hdrUsage();

 strcpy(hdrData.outhdr,argv[ 2 ]);
 hdrData.xdim=atoi(argv[ 3 ]);
 hdrData.ydim=atoi(argv[ 4 ]);
 hdrData.channels=atoi(argv[ 5 ]);
 hdrData.dataType=atoi(argv[ 6 ]);
 if (argc==8) hdrData.byteOrder=atoi(argv[ 7 ]);

 createEnviHeader("",hdrData.outhdr,&hdrData);
 return (EXIT_SUCCESS);
}

void hdrUsage(){

 fprintf(stderr,"\nUsage: earth -header filename xdim ydim channels dataType [byteOrder] \n\n");
 fprintf(stderr, "    filename      Name of header file to create\n");
 fprintf(stderr, "    xdim          Number of pixels in x\n");
 fprintf(stderr, "    ydim          Number of pixels in y\n");	   
 fprintf(stderr, "    channels      Number of channels\n"); 
 fprintf(stderr, "    dataType      1: char, 2: short, 3: long, 4: float, 8: double \n");
 fprintf(stderr, "    [byteOrder]   0: Little endian 1: Big endian\n\n");
 exit(EXIT_FAILURE);

}
