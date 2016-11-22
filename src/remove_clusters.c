
/*
NAME:		remove_clusters.c 
DESCRIPTION: 	Program for removing small or big pixel clusters
 		Need to run count_clusters first 
AUTHOR:	 	Will Grey
VERSION:	v1: October 2001
                v2: 2016-09-28	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#include "earth.h"

#define MAX_NUM_CLUSTERS_CHAR 256
#define MAX_NUM_CLUSTERS_INT 30000

int run_clusters(int argc, char *argv[], void (*f)(FILE *, FILE*, unsigned int, unsigned int, unsigned int))
{

 unsigned int xdim, ydim, size=5; 
 FILE *fin1, *fin2;
 struct stat size1;
 
 if(argc < 5) clusters_usage(argv[1]);
 if(argc == 5) size = atoi(argv[4]);
 fin1=openFile("",argv[2],"r");	
 fin2=openFile("",argv[3],"w");			

 xdim = atoi(argv[4]);

 ydim=(int)(size1.st_size/xdim);
 f(fin1, fin2, xdim, ydim, size);

 fclose(fin1);
 fclose(fin2);
    	
 return(EXIT_SUCCESS);
}

void clusters_usage(char *tool)
{
 fprintf(stderr,"Usage: earth %s infile outfile xdim size \n", tool);	
 fprintf(stderr, "   infile      Change map\n");
 fprintf(stderr, "   outfile     Modified change map\n");
 fprintf(stderr, "   xdim        Number of pixels in width\n");        
 fprintf(stderr, "   size        Remove clusters smaller than or equal to size xdim or bigger: default=5\n\n");	
 exit(EXIT_FAILURE);	
}

void remove_small_clusters_byte(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim, unsigned int size)
{
	
 unsigned int x, y, a, area[MAX_NUM_CLUSTERS_CHAR], blob=0, clusters=0;
 unsigned char *in_img, *out_img;

 if((in_img = (unsigned char *) calloc(xdim * ydim , sizeof(char))) == NULL) memoryCheck();
 if((out_img = (unsigned char *) calloc(xdim * ydim, sizeof(char))) == NULL) memoryCheck();
	
 fread(in_img, sizeof(unsigned char), xdim * ydim, fin);
 
 for(a=0; a<MAX_NUM_CLUSTERS_CHAR; a++)area[a]=0;

 /* copy imput image to output image and 
 count number of pixels in each cluster */
	
 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   *(out_img + (y * xdim) + x) = *(in_img + (y * xdim) + x); 
   area[*(out_img + (y * xdim) + x)]++; 
  }
 }
	
/* count number of pixel clusters */
	
 for(a=2; a<MAX_NUM_CLUSTERS_CHAR; a++){
  if(area[a] != 0)blob++;
 }
	
 /* remove clusters smaller or equal to size pixels */

 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   if(area[*(out_img + (y * xdim) + x)] <= size) 
    *(out_img + (y * xdim) + x) = 0;  
   if(area[*(out_img + (y * xdim) + x)] > size && *(out_img + (y * xdim) + x) !=0)
    *(out_img + (y * xdim) + x) = 1;           
  }
 }
	
 for(a=2; a<MAX_NUM_CLUSTERS_CHAR; a++)if(area[a] > size)clusters++;	
 fwrite(out_img, sizeof(unsigned char), xdim * ydim, fout);

 fprintf(stdout,"input_number_of_change_areas: %d \n", blob);
 fprintf(stdout,"output_number_of_change_areas: %d \n", clusters);

 free(in_img);
 free(out_img);
	
}	

void remove_small_clusters_int(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim, unsigned int size)
{
	
 unsigned int x, y, a, area[MAX_NUM_CLUSTERS_INT], blob=0, clusters=0;
 unsigned int *in_img, *out_img;

 if((in_img = (unsigned int *) calloc(xdim * ydim , sizeof(int))) == NULL) memoryCheck();
 if((out_img = (unsigned int *) calloc(xdim * ydim, sizeof(int))) == NULL) memoryCheck();
	
 fread(in_img, sizeof(unsigned int), xdim * ydim, fin);
 
 for(a=0; a<MAX_NUM_CLUSTERS_INT; a++)area[a]=0;

 /* copy imput image to output image and 
 count number of pixels in each cluster */
	
 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   *(out_img + (y * xdim) + x) = *(in_img + (y * xdim) + x); 
   area[*(out_img + (y * xdim) + x)]++; 
  }
 }
	
/* count number of pixel clusters */
	
 for(a=2; a<MAX_NUM_CLUSTERS_INT; a++){
  if(area[a] != 0)blob++;
 }
	
 /* remove clusters smaller or equal to size pixels */

 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   if(area[*(out_img + (y * xdim) + x)] <= size) 
    *(out_img + (y * xdim) + x) = 0;  
   if(area[*(out_img + (y * xdim) + x)] > size && *(out_img + (y * xdim) + x) !=0)
    *(out_img + (y * xdim) + x) = 1;           
  }
 }
	
 for(a=2; a<MAX_NUM_CLUSTERS_INT; a++)if(area[a] > size)clusters++;	
 fwrite(out_img, sizeof(unsigned int), xdim * ydim, fout);

 fprintf(stdout,"input_number_of_change_areas: %d \n", blob);
 fprintf(stdout,"output_number_of_change_areas: %d \n", clusters);

 free(in_img);
 free(out_img);
	
}	

void remove_big_clusters_byte(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim, unsigned int size)
{
	
 unsigned int x, y, a, area[MAX_NUM_CLUSTERS_CHAR], blob=0, clusters=0;
 unsigned char *in_img, *out_img;

 if((in_img = (unsigned char *) calloc(xdim * ydim , sizeof(char))) == NULL) memoryCheck();
 if((out_img = (unsigned char *) calloc(xdim * ydim, sizeof(char))) == NULL) memoryCheck();
	
 fread(in_img, sizeof(unsigned char), xdim * ydim, fin);
 
 for(a=0; a<MAX_NUM_CLUSTERS_CHAR; a++)area[a]=0;

 /* copy imput image to output image and 
 count number of pixels in each cluster */
	
 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   *(out_img + (y * xdim) + x) = *(in_img + (y * xdim) + x); 
   area[*(out_img + (y * xdim) + x)]++; 
  }
 }
	
/* count number of pixel clusters */
	
 for(a=2; a<MAX_NUM_CLUSTERS_CHAR; a++){
  if(area[a] != 0)blob++;
 }
	
 /* remove clusters smaller or equal to size pixels */

 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   if(area[*(out_img + (y * xdim) + x)] > size) 
    *(out_img + (y * xdim) + x) = 0;  
   if(area[*(out_img + (y * xdim) + x)] <= size && *(out_img + (y * xdim) + x) !=0)
    *(out_img + (y * xdim) + x) = 1;           
  }
 }
	
 for(a=2; a<MAX_NUM_CLUSTERS_CHAR; a++)if(area[a] <= size)clusters++;	
 fwrite(out_img, sizeof(unsigned char), xdim * ydim, fout);

 fprintf(stdout,"input_number_of_change_areas: %d \n", blob);
 fprintf(stdout,"output_number_of_change_areas: %d \n", clusters);

 free(in_img);
 free(out_img);
	
}	

void remove_big_clusters_int(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim, unsigned int size)
{
	
 unsigned int x, y, a, area[MAX_NUM_CLUSTERS_INT], blob=0, clusters=0;
 unsigned int *in_img, *out_img;

 if((in_img = (unsigned int *) calloc(xdim * ydim , sizeof(int))) == NULL) memoryCheck();
 if((out_img = (unsigned int *) calloc(xdim * ydim, sizeof(int))) == NULL) memoryCheck();
	
 fread(in_img, sizeof(unsigned int), xdim * ydim, fin);
 
 for(a=0; a<MAX_NUM_CLUSTERS_INT; a++)area[a]=0;

 /* copy imput image to output image and 
 count number of pixels in each cluster */
	
 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   *(out_img + (y * xdim) + x) = *(in_img + (y * xdim) + x); 
   area[*(out_img + (y * xdim) + x)]++; 
  }
 }
	
/* count number of pixel clusters */
	
 for(a=2; a<MAX_NUM_CLUSTERS_INT; a++){
  if(area[a] != 0)blob++;
 }
	
 /* remove clusters smaller or equal to size pixels */

 for(y=0; y<ydim; y++){
  for(x=0; x < xdim; x++){
   if(area[*(out_img + (y * xdim) + x)] > size) 
    *(out_img + (y * xdim) + x) = 0;  
   if(area[*(out_img + (y * xdim) + x)] <= size && *(out_img + (y * xdim) + x) !=0)
    *(out_img + (y * xdim) + x) = 1;           
  }
 }
	
 for(a=2; a<MAX_NUM_CLUSTERS_INT; a++)if(area[a] <= size)clusters++;	
 fwrite(out_img, sizeof(unsigned int), xdim * ydim, fout);

 fprintf(stdout,"input_number_of_change_areas: %d \n", blob);
 fprintf(stdout,"output_number_of_change_areas: %d \n", clusters);

 free(in_img);
 free(out_img);
	
}

