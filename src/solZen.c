/*
NAME:		SolZen.c 
DESCRIPTION: 	Calculate solar zenith and azimuth angle
AUTHOR:	 	Will Grey
VERSION:	2016-03-27	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int zenith(int argc, char **argv){
 
 int month, day, hour, minute, doy;
 double latitude;
 double decimal_hours, hour_angle, declination, cos_zenith, sza, az;

 if (argc != 7) zenithUsage();	
 
 month=atoi(argv[2]); 
 day=atoi(argv[3]); 
 hour=atoi(argv[4]);
 minute=atoi(argv[5]);
 latitude=DTOR(atof(argv[6]));
 doy=dayOfYear(month,day);
 
 decimal_hours=(double)hour+((double)minute/60);
 hour_angle=DTOR(15.0*(12.0-(double)decimal_hours));
 declination=(DTOR(-23.4))*cos(DTOR(360.0*((double)doy+10.0)/365.0));
 cos_zenith=sin(latitude)*sin(declination)+cos(latitude)*cos(declination)*cos(hour_angle);
 sza=RTOD(acos(cos_zenith)); 


 az=(-1.0*(sin(latitude)*cos_zenith-sin(declination)))/(cos(latitude)*sin(acos(cos_zenith)));


 fprintf(stdout,"Solar_Zenith_Angle: %f\n",sza); 
 fprintf(stdout,"Solar_Azimuth_Angle: %f\n",RTOD(acos(PI-az))); 	
 return (EXIT_SUCCESS);
	
}

int dayOfYear(int month, int day){
 
 int doy;

 if (month > 12 || month < 1 || day < 1 || day > 31){
  fprintf(stderr,"Please enter correct month and/or day");
  exit(EXIT_FAILURE);
 }

 if (month == 2 && day > 29){
  fprintf(stderr,"Please enter correct month and/or day");
  exit(EXIT_FAILURE);
 }

 if ((day >30) && (month == 4 || month==6 || month==9 || month==11)){
  fprintf(stderr,"Please enter correct month and/or day");
  exit(EXIT_FAILURE);
 }

 switch(month){
  case 1:
   doy=day; 
   break;
  case 2:
   doy=31+day;
   break;
  case 3:
   doy=59+day;
   break;
  case 4:
   doy=90+day; 
   break;
  case 5:
  doy=120+day;
   break;
  case 6:
   doy=151+day; 
   break;
  case 7:
   doy=181+day; 
   break;
  case 8:
   doy=212+day; 
   break;
  case 9:
   doy=243+day; 
   break;
  case 10:
   doy=273+day; 
   break;
  case 11:
   doy=304+day; 
   break;
  case 12:
   doy=334+day; 
   break;
 }

 return doy;
}

void zenithUsage(){
 fprintf(stderr,"Usage: earth -solpos month day hour minute latitude\n\n");
 fprintf(stderr, "   month \n");
 fprintf(stderr, "   day \n");
 fprintf(stderr, "   hour \n");
 fprintf(stderr, "   minute \n");
 fprintf(stderr, "   latitude \n\n");

 exit(EXIT_FAILURE);
}

