
/*
NAME:		eval_clusters.c 
DESCRIPTION: 	Program for comparing pixel clusters between 
		two images to work out accuracy assessment.
AUTHOR:	 	Will Grey
VERSION:	v1: October 2001
                v2: 2016-09-28	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#include "earth.h"

#define MAX_NUM_CLUSTERS 30000
#define WIN 3

int run_eval_clusters(int argc, char *argv[])
{

 unsigned int xdim, ydim, flag=0; 
 FILE *fin1, *fin2;
 struct stat size;
 
 if(argc < 5) eval_clusters_usage();
 if(argc == 5) flag = atoi(argv[4]);
 fin1=openFile("",argv[2],"r");	
 fin2=openFile("",argv[3],"r");			

 xdim = atoi(argv[4]);

 ydim=(int)(size.st_size/xdim);
 eval_clusters(fin1, fin2, xdim, ydim, flag);

 fclose(fin1);
 fclose(fin2);
    	
 return(EXIT_SUCCESS);
}


void eval_clusters_usage()
{
 fprintf(stderr,"Usage: earth -eval_clusters infile infile2 xdim flag \n");	
 fprintf(stderr, "   infile1      ground truth image (unsigned int)\n");
 fprintf(stderr, "   infile2      classified change map (unsigned int)\n");
 fprintf(stderr, "   xdim         Number of pixels in width\n");        
 fprintf(stderr, "   flag         default 0: clusters only have to be touching to be correctly classified\n");
 fprintf(stderr, "                        1: clusters have to overlap to be correctly classified\n\n");
 exit(EXIT_FAILURE);	
}

void eval_clusters(FILE *fin1, FILE *fin2, unsigned int xdim, unsigned int ydim, unsigned int flag)
{
 unsigned int x, y, i, j, a, gt_area[MAX_NUM_CLUSTERS], chg_area[MAX_NUM_CLUSTERS]; 
 unsigned int gt_cluster=0, chg_cluster=0, chg=0;
 unsigned int *in_img1, *in_img2;
	
 if((in_img1 = (unsigned int *) calloc(xdim * ydim , sizeof(int))) == NULL) memoryCheck();
 if((in_img2 = (unsigned int *) calloc(xdim * ydim, sizeof(int))) == NULL) memoryCheck();
	
 fread(in_img1, sizeof(unsigned int), xdim * ydim, fin1);
 fread(in_img2, sizeof(unsigned int), xdim * ydim, fin2);

 for(a=0; a<MAX_NUM_CLUSTERS; a++){
  gt_area[a]=0;
  chg_area[a]=0;
 }

 /* count number of pixels in each cluster */
	
  for(x=0; x < xdim*ydim; x++){
   gt_area[*(in_img1 + x)]++; 
   chg_area[*(in_img2 + x)]++;
  }
 
 /* count number of clusters on each image */
	
 for(a=2; a<MAX_NUM_CLUSTERS; a++){
  if(gt_area[a] != 0)gt_cluster++;
  if(chg_area[a] != 0)chg_cluster++;
 }
	
 for(a=0; a<MAX_NUM_CLUSTERS; a++)
  chg_area[a]=0;
 
	
 /* clusters only have to be touching to be correctly classified  */
	
 if(flag == 0)
  for(y=0; y<ydim; y++)	
   for(x=0; x < xdim; x++)	
    for(i=0;i<WIN;i++)	
     for(j=0;j<WIN;j++)	
      if(*(in_img1 + (y * xdim) + x) !=0 && *(in_img2 + ((y + j - 1) * xdim) + x + i - 1) !=0)	
       chg_area[*(in_img1 + (y * xdim) + x)]=1;		
 
	
 /* clusters have to overlap to be correctly classified  */
 if(flag == 1)
  for(y=0; y<ydim; y++)
   for(x=0; x < xdim; x++)
    if(*(in_img1 + (y * xdim) + x) !=0 && *(in_img2 + (y * xdim) + x) !=0)
     chg_area[*(in_img1 + (y * xdim) + x)]=1;


 /* number of overlapping clusters */						
 for(a=0; a<MAX_NUM_CLUSTERS; a++)
  if(chg_area[a] == 1)chg++; 
   	
 fprintf(stdout,"num_clusters_on_change_map:      %2d\n", chg_cluster);
 fprintf(stdout,"num_clusters_on_ground_truth:    %2d\n", gt_cluster);
 fprintf(stdout,"num_overlap_clusters:      %2d \n", chg);
 fprintf(stdout,"accuracy_ground_truth:    %5.2f \n", ((float) chg  / (float) gt_cluster )*100);	
 fprintf(stdout,"accuracy_change_map:      %5.2f \n", ((float) chg / (float) chg_cluster)*100);		
 fprintf(stdout,"false_positives: %5.2f \n", 100 - ((float) chg / (float) chg_cluster)*100);
 fprintf(stdout,"false_negatives: %5.2f \n", 100 - ((float) chg  / (float) gt_cluster )*100); 

 free(in_img1);
 free(in_img2);

}	

