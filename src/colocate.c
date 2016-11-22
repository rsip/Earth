/*
NAME:		colocate.c 
DESCRIPTION: 	Identifying offsets between collocated data
		across an image scene.  One image is shifted 
                with pixel offsest in both the x (cols) and y
                (rows) directions against the image over an 
                area of window specified by the user (default is 15).
	        The outputs are to standard output in 6 columns:
				
		column 1: x position of patch
                column 2: y position of patch
		column 3: x offset for best correlation
		column 4: y offset for best correlation
		column 5: Cross-correlation of best correlation
		column 6: Singal-to-Noise ratio

AUTHOR:	 	Will Grey
VERSION:	2016-05-06	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"
#define MAX_WINSIZE 99

int colocate(int argc, char *argv[])
{
 
 float *data1, *data1_patch; 
 float *data2, *data2_patch;
 int x, y, i, j, edge, winsize, skip=30, correl_winsize=15, correl_edge;
 int start_xpos, start_ypos, end_xpos, end_ypos, xdim, ydim, flag=0;
 offset off;
 struct stat size; 

 if (argc < 5) colocateUsage();
 
 xdim = atoi(argv[5]);

 if (argc >= 6) skip            = atoi(argv[5]);
 if (argc == 7) correl_winsize  = atoi(argv[6]);
 
 winsize = correl_winsize * 3;
 correl_edge = correl_winsize / 2;
 edge = winsize / 2;
 
 if (stat(argv[2], &size) == -1) fileReadError(argv[2]);
 else ydim = size.st_size / xdim;  

 data1=readFloatData("", argv[2], xdim*ydim);
 data2=readFloatData("", argv[3], xdim*ydim);
  
 data2_patch = (float *) calloc(winsize*winsize,sizeof(float));
 data1_patch = (float *) calloc(winsize*winsize,sizeof(float));
 
 for (y=0;y<ydim;y++){
  for (x=0;x<xdim;x++){   
   if ((*(data1 + y * xdim + x) != 0) && (flag == 0)){
	start_xpos= x + edge;
	start_ypos= y + edge;
	flag=1;
   }  
  }
 }
 
 for (y=ydim-1;y>=0;y--){
  for (x=xdim-1;x>=0;x--){   
   if ((*(data1 + y * xdim + x) != 0) && (flag == 1)){
	end_xpos = x - edge + 1;
	end_ypos = y - edge + 1;
	flag=2;
   }  
  }
 }
 
 for (y=start_ypos;y<end_ypos;y=y+skip){   
  for (x=start_xpos;x<end_xpos;x=x+skip){    
   for (i=0;i<winsize;i++){	
    for (j=0;j<winsize;j++){	  
    *(data2_patch + i * winsize + j) = *(data2 + (y - edge + i) * xdim + x - edge +j );
    *(data1_patch + i * winsize + j) = *(data1 + (y - edge + i) * xdim + x - edge +j );		
   } 
  }
  
   off=cci(data2_patch, data1_patch, winsize, correl_winsize, correl_edge);
   fprintf(stdout,"%d %d %d %d %6.4f %6.4f\n",x+1,y+1,off.x,off.y,off.max,off.snr);    
  
  } 
 } 
 
 return (EXIT_SUCCESS);

}

int colocateUsage(){
 fprintf(stderr,"Usage: earth -colocate inImg outImg xdim [skip] [correl_winsize] \n\n");	 	
 fprintf(stderr, "   inImg1           Input image (byte)\n");
 fprintf(stderr, "   inImg2          Output image (byte)\n");      
 fprintf(stderr, "   xdim             Number of xdim per row\n"); 
 fprintf(stderr, "   skip             Window size; odd only Default: 3\n"); 
 fprintf(stderr, "   correl_winsize   default=15         \n\n"); 
 exit(EXIT_FAILURE);	
}

offset cci(float *data2, float *data1, int winsize, int correl_winsize, int correl_edge)
{
 int x, y, i, j;
 unsigned short win_data1[MAX_WINSIZE][MAX_WINSIZE]; 
 short win_data2[MAX_WINSIZE][MAX_WINSIZE];
 double sum_data1, sum_data2, ave_data2, ave_data1, sum_prod, sum_off;
 double sum_sqr_data1, sum_sqr_data2, corr[(MAX_WINSIZE*2)+1][(MAX_WINSIZE*2)+1];
 offset off;
 
 /* Read in only window size number of xdim */
	
 for(y = 0; y < correl_winsize; y++)
  for(x = 0; x < correl_winsize; x++)
	win_data2[x][y] = *(data2 + ( ( y + correl_winsize ) * winsize ) +  correl_winsize + x );
 											
 for(i = 0 ; i <= correl_winsize * 2 ; i++){
  for(j = 0 ; j <= correl_winsize * 2 ; j++){	

   /* Read in only window size number of xdim but incrementing offset  */    

   for(y = 0; y < correl_winsize ; y++)
    for(x = 0; x < correl_winsize ; x++)
      win_data1[x][y] = *(data1 + ( ( y +  i ) * winsize ) +   x + j );
    		   	   
    /* Calculate mean */
    	   
    sum_data1=0;
    sum_data2=0;
    
   for(y = 0; y < correl_winsize; y++){
    for(x = 0; x < correl_winsize; x++){
      sum_data1 += (double)win_data1[x][y];
      sum_data2 += (double)win_data2[x][y];
    }
   }
	
   ave_data2 = sum_data2 / (correl_winsize * correl_winsize);
   ave_data1 = sum_data1 / (correl_winsize * correl_winsize);
																	
   /* Calculate covariance and correlation matrix */
			
   sum_prod=0;
   sum_sqr_data1=0; 
   sum_sqr_data2=0;
			
   for(y = 0; y < correl_winsize; y++){
    for(x = 0; x < correl_winsize; x++){		
	 sum_prod +=	((double)win_data1[x][y] - ave_data1) * ((double)win_data2[x][y] - ave_data2);	
	 sum_sqr_data1 += pow((double)win_data1[x][y] - ave_data1,2);
	 sum_sqr_data2 += pow((double)win_data2[x][y] - ave_data2,2);
	}
   }	
   corr[i][j] = pow(sum_prod/sqrt(sum_sqr_data1*sum_sqr_data2),2);
  }	
 }

 /* Find offset of maximum correlation */
 
 off.max=0;
 sum_off=0;
   							
 for(i=0 ; i <= correl_winsize * 2 ; i++){
  for(j=0 ; j <= correl_winsize * 2 ; j++){
   sum_off = sum_off + corr[i][j]; 
   if ( corr[i][j] > off.max ) {
    off.max = corr[i][j];
	off.x = j - correl_winsize;
	off.y = i - correl_winsize;
   } 
  }
 }
 
 off.snr = corr[off.x+correl_winsize][off.y+correl_winsize] / (sum_off / (((correl_winsize * 2 + 1)) * ((correl_winsize * 2 + 1)))); 

 return off;
	
}



