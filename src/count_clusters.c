
/*
NAME:		count_clusters.c 
DESCRIPTION: 	Program for counting clusters in a byte 1 / 0
                raw binary image  
AUTHOR:	 	Will Grey
VERSION:	v1: October 2001
                v2: 2016-10-23	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/


#include "earth.h"

#define MAX_NUM_CLUSTERS_CHAR 256
#define MAX_NUM_CLUSTERS_INT 30000

int run_count_clusters(int argc, char *argv[], void (*f)(FILE *, FILE*, unsigned int, unsigned int, unsigned int))
{

 unsigned int xdim, ydim, flag=0; 
 FILE *fin1, *fin2;
 struct stat size1;
 
 if(argc < 5) count_clusters_usage(argv[1]);
 if(argc == 5) flag = atoi(argv[4]);
 fin1=openFile("",argv[2],"r");	
 fin2=openFile("",argv[3],"w");			

 xdim = atoi(argv[4]);

 ydim=(int)(size1.st_size/xdim);
 f(fin1, fin2, xdim, ydim, flag);

 fclose(fin1);
 fclose(fin2);
    	
 return(EXIT_SUCCESS);
}

void count_clusters_usage(char *tool)
{
 fprintf(stderr,"Usage: earth %s infile outfile xdim size \n", tool);	
 fprintf(stderr, "   infile      Change map\n");
 fprintf(stderr, "   outfile     Modified change map\n");
 fprintf(stderr, "   xdim        Number of pixels in width\n");        
 fprintf(stderr, "   flag        flag=1 will print stats (default=0)\n\n");
 exit(EXIT_FAILURE);	
}

void identify_clusters_byte(unsigned char *img, unsigned int xdim, unsigned int ydim)
{

 int x,y, i, j, break_out, count=1;

 for(y=0; y<ydim; y++){
  for(x=0; x <xdim; x++){
   break_out=0;
   if (img[y * xdim + x] == 1){
    for(i=0;i<2;i++){
     for(j=0;j<2;j++){
      if(img[((y + i - 1) * xdim) + (x + j - 1)] > 1){
       img[y * xdim + x] =img[((y + i - 1) * xdim) + (x + j - 1)];
       break_out=1;
       break;	
      }	
     }
    if(break_out==1)break;	
   }
   if (break_out ==0){
    count++;
    img[y * xdim + x]=count;
    }
   }
  }
 }	

}


void homogenise_clusters_forwards_byte(unsigned char *img, unsigned int xdim, unsigned int ydim){

 int x, y, i, j;

 for(y=1; y < ydim; y++)
  for(x=1; x < xdim; x++)
   if (img[y * xdim + x] > 1)
    for(i=0;i<2;i++)
     for(j=0;j<2;j++)
      if(img[((y + i - 1) * xdim) + (x + j - 1)] > 1)
       if (img[y * xdim + x] > img[((y + i - 1) * xdim) + (x + j - 1)])
        img[y * xdim + x]=img[((y + i - 1) * xdim) + (x + j - 1)];

}

void homogenise_clusters_backwards_byte(unsigned char *img, unsigned int xdim, unsigned int ydim){

 int x, y, i, j;

 for(y=ydim-1; y > 0; y--)
  for(x=xdim-1; x > 0; x--)
   if (img[y * xdim + x] > 1)
    for(i=0;i<2;i++)
     for(j=0;j<2;j++)
      if(img[((y + i) * xdim) + (x + j)] > 1)
       if (img[y * xdim + x] > img[((y + i) * xdim) + (x + j)])
        img[y * xdim + x]=img[((y + i) * xdim) + (x + j)];
}

void horizontal_edge_clusters_byte(unsigned char *img, unsigned int xdim, unsigned int ydim){
 
 int x, i;
 
 for(x=0; x < xdim; x++){
  if (img[x] == 1){
   for(i=0;i<3;i++){
    if(img[xdim + x + i] > 1){
     img[x] = img[xdim + x + i];
     break;
    }
   }
  }
 }
}

void vertical_edge_clusters_byte(unsigned char *img, unsigned int xdim, unsigned int ydim){

 int y, i;

 for(y=0; y < ydim; y++){
  if (img[y * xdim] == 1){
   for(i=0;i<3;i++){
    if(img[xdim * (y + i) + 1] > 1){
     img[y * xdim] = img[xdim * (y + i) + 1];
     break;
    }
   }
  }
 }
}

void reassign_clusters_byte(unsigned char *img, unsigned int xdim, unsigned int ydim){
 
 int y, x, i;
 unsigned char *cluster_in, *cluster_out;

 if((cluster_in = (unsigned char *) calloc(MAX_NUM_CLUSTERS_CHAR, sizeof(char))) == NULL) memoryCheck();
 if((cluster_out = (unsigned char *) calloc(MAX_NUM_CLUSTERS_CHAR, sizeof(char))) == NULL) memoryCheck();
 
 for (i=1;i<MAX_NUM_CLUSTERS_CHAR;i++)
  cluster_in[i]=0;

 for(y=0; y < ydim; y++)
  for(x=0; x < xdim; x++)
   if(img[y * xdim + x] !=0)
    cluster_in[img[y * xdim + x]]=1;

  for (i=1;i<MAX_NUM_CLUSTERS_CHAR;i++)
   if (cluster_in[i]==1) 
    cluster_out[i]=i;
   
 for(y=0; y < ydim; y++)
  for(x=0; x < xdim; x++)
   if(img[y * xdim + x] !=0) 
    img[y * xdim + x]=cluster_out[img[y * xdim + x]];
 
 free(cluster_in);
 free(cluster_out);
}

void stat_clusters_byte(unsigned char *img, unsigned int xdim, unsigned int ydim){

 int x, y, i, sum=0, clusters=0;
 int count[MAX_NUM_CLUSTERS_CHAR];

 for (i=0;i<MAX_NUM_CLUSTERS_CHAR;i++)
  count[i]=0;

 for(y=0; y < ydim; y++){
  for(x=0; x < xdim; x++){
   if (img[y * xdim + x]!=0){
    count[img[y * xdim + x]]++;
    sum++;
   }
  }
 }   
 
 for (i=0;i<MAX_NUM_CLUSTERS_CHAR;i++)
  if (count[i]!=0) clusters++;

 fprintf(stdout,"Number_of_change_areas: %d \n", clusters);
 fprintf(stdout,"Number_of_change_pixels: %d \n", sum);

 for (i=0;i<MAX_NUM_CLUSTERS_CHAR;i++)
  if (count[i]!=0) fprintf(stdout,"Area: %d %d \n", i, count[i]);
 
}

void count_clusters_byte(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim, unsigned int flag)
{
	
 unsigned char *img;

 if((img = (unsigned char *) calloc(xdim * ydim , sizeof(char))) == NULL) memoryCheck();
 
 fread(img, sizeof(unsigned char), xdim * ydim, fin);

 identify_clusters_byte(img,xdim,ydim);
 homogenise_clusters_forwards_byte(img,xdim,ydim);  
 homogenise_clusters_backwards_byte(img,xdim,ydim); 
 horizontal_edge_clusters_byte(img,xdim,ydim); 
 vertical_edge_clusters_byte(img,xdim,ydim); 
 reassign_clusters_byte(img,xdim,ydim);
 if (flag==1) stat_clusters_byte(img,xdim,ydim);
 
 fwrite(img, sizeof(unsigned char), xdim * ydim, fout);

 free(img);

}


void identify_clusters_int(unsigned int *img, unsigned int xdim, unsigned int ydim)
{

 int x,y, i, j, break_out, count=1;

 for(y=0; y<ydim; y++){
  for(x=0; x <xdim; x++){
   break_out=0;
   if (img[y * xdim + x] == 1){
    for(i=0;i<2;i++){
     for(j=0;j<2;j++){
      if(img[((y + i - 1) * xdim) + (x + j - 1)] > 1){
       img[y * xdim + x] =img[((y + i - 1) * xdim) + (x + j - 1)];
       break_out=1;
       break;	
      }	
     }
    if(break_out==1)break;	
   }
   if (break_out ==0){
    count++;
    img[y * xdim + x]=count;
    }
   }
  }
 }	

}


void homogenise_clusters_forwards_int(unsigned int *img, unsigned int xdim, unsigned int ydim){

 int x, y, i, j;

 for(y=1; y < ydim; y++)
  for(x=1; x < xdim; x++)
   if (img[y * xdim + x] > 1)
    for(i=0;i<2;i++)
     for(j=0;j<2;j++)
      if(img[((y + i - 1) * xdim) + (x + j - 1)] > 1)
       if (img[y * xdim + x] > img[((y + i - 1) * xdim) + (x + j - 1)])
        img[y * xdim + x]=img[((y + i - 1) * xdim) + (x + j - 1)];

}

void homogenise_clusters_backwards_int(unsigned int *img, unsigned int xdim, unsigned int ydim){

 int x, y, i, j;

 for(y=ydim-1; y > 0; y--)
  for(x=xdim-1; x > 0; x--)
   if (img[y * xdim + x] > 1)
    for(i=0;i<2;i++)
     for(j=0;j<2;j++)
      if(img[((y + i) * xdim) + (x + j)] > 1)
       if (img[y * xdim + x] > img[((y + i) * xdim) + (x + j)])
        img[y * xdim + x]=img[((y + i) * xdim) + (x + j)];
}

void horizontal_edge_clusters_int(unsigned int *img, unsigned int xdim, unsigned int ydim){
 
 int x, i;
 
 for(x=0; x < xdim; x++){
  if (img[x] == 1){
   for(i=0;i<3;i++){
    if(img[xdim + x + i] > 1){
     img[x] = img[xdim + x + i];
     break;
    }
   }
  }
 }
}

void vertical_edge_clusters_int(unsigned int *img, unsigned int xdim, unsigned int ydim){

 int y, i;

 for(y=0; y < ydim; y++){
  if (img[y * xdim] == 1){
   for(i=0;i<3;i++){
    if(img[xdim * (y + i) + 1] > 1){
     img[y * xdim] = img[xdim * (y + i) + 1];
     break;
    }
   }
  }
 }
}

void reassign_clusters_int(unsigned int *img, unsigned int xdim, unsigned int ydim){
 
 int y, x, i;
 unsigned int *cluster_in, *cluster_out;

 if((cluster_in = (unsigned int *) calloc(MAX_NUM_CLUSTERS_CHAR, sizeof(int))) == NULL) memoryCheck();
 if((cluster_out = (unsigned int *) calloc(MAX_NUM_CLUSTERS_CHAR, sizeof(int))) == NULL) memoryCheck();
 
 for (i=1;i<MAX_NUM_CLUSTERS_INT;i++)
  cluster_in[i]=0;

 for(y=0; y < ydim; y++)
  for(x=0; x < xdim; x++)
   if(img[y * xdim + x] !=0)
    cluster_in[img[y * xdim + x]]=1;

  for (i=1;i<MAX_NUM_CLUSTERS_INT;i++)
   if (cluster_in[i]==1) 
    cluster_out[i]=i;
   
 for(y=0; y < ydim; y++)
  for(x=0; x < xdim; x++)
   if(img[y * xdim + x] !=0) 
    img[y * xdim + x]=cluster_out[img[y * xdim + x]];
 
 free(cluster_in);
 free(cluster_out);
}

void stat_clusters_int(unsigned int *img, unsigned int xdim, unsigned int ydim){

 int x, y, i, sum=0, clusters=0;
 int count[MAX_NUM_CLUSTERS_INT];

 for (i=0;i<MAX_NUM_CLUSTERS_INT;i++)
  count[i]=0;

 for(y=0; y < ydim; y++){
  for(x=0; x < xdim; x++){
   if (img[y * xdim + x]!=0){
    count[img[y * xdim + x]]++;
    sum++;
   }
  }
 }   
 
 for (i=0;i<MAX_NUM_CLUSTERS_INT;i++)
  if (count[i]!=0) clusters++;

 fprintf(stdout,"Number_of_change_areas: %d \n", clusters);
 fprintf(stdout,"Number_of_change_pixels: %d \n", sum);

 for (i=0;i<MAX_NUM_CLUSTERS_INT;i++)
  if (count[i]!=0) fprintf(stdout,"Area: %d %d \n", i, count[i]);
 
}

void count_clusters_int(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim, unsigned int flag)
{
	
 unsigned int *img;

 if((img = (unsigned int *) calloc(xdim * ydim , sizeof(int))) == NULL) memoryCheck();
 
 fread(img, sizeof(int), xdim * ydim, fin);

 identify_clusters_int(img,xdim,ydim);
 homogenise_clusters_forwards_int(img,xdim,ydim);  
 homogenise_clusters_backwards_int(img,xdim,ydim); 
 horizontal_edge_clusters_int(img,xdim,ydim); 
 vertical_edge_clusters_int(img,xdim,ydim); 
 reassign_clusters_int(img,xdim,ydim);
 if (flag==1) stat_clusters_int(img,xdim,ydim);
 
 fwrite(img, sizeof(int), xdim * ydim, fout);

 free(img);

}



void count_clusters_slow(FILE *fin, FILE *fout, unsigned int xdim, unsigned int ydim)
{
	
 unsigned int x, y, a, i, j, break_out, cluster, blob;
 unsigned char round[MAX_NUM_CLUSTERS_CHAR];
 unsigned char *in_img, *out_img;

 if((in_img = (unsigned char *) calloc(xdim * ydim , sizeof(char))) == NULL) memoryCheck();
 if((out_img = (unsigned char *) calloc(xdim * ydim, sizeof(char))) == NULL) memoryCheck();	

 fread(in_img, sizeof(unsigned char), xdim * ydim, fin);

 /* copy input image to output image */
	
 for(y=0; y<ydim; y++)
  for(x=0; x < xdim; x++)
   *(out_img + (y * xdim) + x) = *(in_img + (y * xdim) + x);   
	
	
 for(a=0; a<MAX_NUM_CLUSTERS_CHAR; a++)round[a]=a;
	
 a=1, cluster = 1;
	
 while (cluster == 1){  
  a++;
  break_out = 0, cluster = 0;
	
  /* Locate first pixel in new cluster and 
  reassign that pixel with another value */
		
  for(y=0; y<ydim; y++){
   for(x=0; x < xdim; x++){
    if (*(out_img + (y * xdim) + x) == 1){
     *(out_img + (y * xdim) + x) = round[a];
     break_out = 1;
     cluster = 1;
     break;
    }	 	
   }
   if(break_out==1)break;
  }		
	
  blob=1;	
		
  /* for each cluster of pixel this loop keeps going 
  until there are no xdim in that cluster left  */
		  
  while(blob==1){
   blob = 0;
		
   for(y=0; y<ydim; y++){
    for(x=0; x <xdim; x++){
     if (*(out_img + (y * xdim) + x) == 1){
      for(i=0;i<3;i++){
       for(j=0;j<3;j++){
        if(*(out_img + ((y + i - 1) * xdim) + (x + j - 1)) == round[a]){
         *(out_img + x + (y * xdim)) = round[a];
         blob = 1;	
        }
       }				
      }
     }
    }	
   }	
  }
 }  
    
 fwrite(out_img, sizeof(unsigned char), xdim * ydim, fout);
 fprintf(stdout,"Number_of_change_areas: %d \n", a-2);
 
 free(in_img);
 free(out_img);

}






