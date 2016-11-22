/*
NAME:		kriging.c 
DESCRIPTION: 	Perform omnidirectional ordinary Kriging.
AUTHOR:	 	Will Grey
VERSION:	2016-11-06	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

#define TINY 1e-6
#define PROBABILITY_95_PERCENT 1.96


int kriging_point(int argc, char *argv[]){
     
 FILE *fin;
 int pts, n, i, j, nbins, flag=1, nugget=1;
 float lag_tolerance=1.0, *x, *y, *val, *dist, *sv;
 double **gamma, **gamma_inverse, *lambda;
 double *g, valPrime, *p, sum=0.0;
 float xpos=1.0, ypos=4.0;
 float (*f)(float, float, float);

 if (flag==1) f=linear_model;
 if (flag==2) f=spherical_model;
 if (flag==3) f=gaussian_model;
 if (flag==4) f=exponential_model;

 if(argc < 5) kriging_point_usage();

 pts=getNumPts(argv[2]);

 xpos=atof(argv[3]);
 ypos=atof(argv[4]);

 if (argc >= 6) flag=atoi(argv[5]);
 if (argc >= 7) lag_tolerance=atoi(argv[6]);
 if (argc >= 8) nugget=atoi(argv[7]);

 fprintf(stdout,"%d\n",pts);

 if((x = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((y = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((val = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();

 fin=openFile("",argv[2],"r");
 
 readPoint(fin,x,y,val,pts);
 n=(pts*(pts-1))/2;

 if((dist = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck();
 if((sv = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck();

 nbins=variogram(x,y,val,dist,sv,n,pts,lag_tolerance);

 if (nugget == 1){
  p=fit_variogram_model(dist,sv,nbins,flag);    
 } else{
  p=fit_variogram_model_golden(dist,sv,nbins,flag);
 } 

 g=calc_g_vector(x,y,pts,xpos,ypos,f, p[0], p[1]);
 gamma=calc_gamma_matrix(x,y,pts,f, p[0], p[1]);  
 gamma_inverse=matrixInverse((double **)gamma,pts+1);
 lambda=multiplyMatrixVector(gamma_inverse, g,  pts+1, pts+1);
 valPrime=calc_krig_value(lambda,val,pts); 

fprintf(stdout,"\ng vector\n");
 for (i=0;i<pts+1;i++)
  fprintf(stdout,"%f\n",g[i]);

 fprintf(stdout,"\nGamma matrix\n");
 for (j=0;j<pts+1;j++){
  fprintf(stdout,"\n");
  for (i=0;i<pts+1;i++){
   fprintf(stdout,"%f\t",gamma_inverse[i][j]);
  }
 }

 fprintf(stdout,"\n");

 sum=0.0;
 fprintf(stdout,"\nLambda\n");
 for (i=0;i<pts+1;i++){
  fprintf(stdout,"%f\n",lambda[i]);
  sum+=lambda[i];
 }

  fprintf(stdout,"sum_lambda: %f\n",sum);


 sum=0.0;
 for (i=0;i<pts+1;i++)
   sum+=g[i] * lambda[i];

 fprintf(stdout,"\nvalPrime: %f\n",valPrime); 
 fprintf(stdout,"Kriging_variance: %f\n",sum);
 fprintf(stdout,"valPrime_min_95_percent_probability: %f\n",valPrime + PROBABILITY_95_PERCENT * sqrt(fabs(sum)));
 fprintf(stdout,"valPrime_max_95_percent_probability: %f\n",valPrime - PROBABILITY_95_PERCENT * sqrt(fabs(sum)));

 fclose(fin); 
 return (EXIT_SUCCESS);

}

void kriging_point_usage(){

 fprintf(stderr,"Usage: earth -kriging_point pointFile xpos ypos [Model] [Lag_tolerance] [nugget]\n");	
 fprintf(stderr, "    pointFile       Vector file of points in text format\n");
 fprintf(stderr, "    xpos            pixel location in x\n");
 fprintf(stderr, "    ypos            pixel location in y\n");
 fprintf(stderr, "    model           1: linear (default), 2: exponential, 3:spherical, 4: gaussian\n");
 fprintf(stderr, "    lag_tolerance   Semivariogram lag tolerance (default=1.0)\n");
 fprintf(stderr, "    nugget          Include nugget: 1, yes; 2, no (default=1)\n");

 exit(EXIT_FAILURE);

}


int kriging(int argc, char *argv[]){
     
 FILE *fin, *fout, *ferr;
 int pts, n, i, j, k, nbins, flag=1, nugget=1, xdim, ydim;
 float lag_tolerance=1.0, *x, *y, *val, *dist, *sv;
 double **gamma, **gamma_inverse, *lambda;
 double *g, *p;
 float xpos, ypos, dy=1.0, dx=1.0;
 float (*f)(float, float, float);
 double xmax,xmin,ymin,ymax;
 float *outImg, *outErr;

 if (flag==1) f=linear_model;
 if (flag==2) f=spherical_model;
 if (flag==3) f=gaussian_model;
 if (flag==4) f=exponential_model;

 if(argc < 5) krigingUsage();

 if (argc >= 6) flag=atoi(argv[5]);
 if (argc >= 7) lag_tolerance=atoi(argv[6]);
 if (argc >= 8) nugget=atoi(argv[7]);
 if (argc >= 9) dx=atof(argv[8]);
 if (argc >= 10) dy=atof(argv[9]);
 
 pts=getNumPts(argv[2]);
 
 fprintf(stdout,"%d\n",pts);

 if((x = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((y = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((val = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();

 fin=openFile("",argv[2],"r");
 fout=openFile("",argv[3],"wb");
 ferr=openFile("",argv[4],"wb");
 
 readPoint(fin,x,y,val,pts);
 n=(pts*(pts-1))/2;

 if((dist = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck();
 if((sv = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck();

 nbins=variogram(x,y,val,dist,sv,n,pts,lag_tolerance);

 if (nugget == 1){
  p=fit_variogram_model(dist,sv,nbins,flag);    
 } else{
  p=fit_variogram_model_golden(dist,sv,nbins,flag);
 } 

 xmax=max(x,pts);
 ymax=max(x,pts);
 xmin=min(x,pts);
 ymin=min(y,pts);

 xdim=floor((xmax-xmin)/dx);
 ydim=floor((ymax-ymin)/dy);

 if((outImg  = (float *) calloc(xdim,sizeof(float)))== NULL) memoryCheck();	
 if((outErr  = (float *) calloc(xdim,sizeof(float)))== NULL) memoryCheck();

 fprintf(stdout,"\n Kriging:\n");
 
 for(j=0;j<ydim;j++){
  for (i=0;i<xdim;i++){
  
   xpos=xmin+(i*dx);
   ypos=ymin+(j*dy);

   g=calc_g_vector(x,y,pts,xpos,ypos,f, p[0], p[1]);
   gamma=calc_gamma_matrix(x,y,pts,f, p[0], p[1]);  
   gamma_inverse=matrixInverse((double **)gamma,pts+1);
   lambda=multiplyMatrixVector(gamma_inverse, g,  pts+1, pts+1);
   outImg[i]=calc_krig_value(lambda,val,pts); 

   outErr[i]=0.0;
   for (k=0;k<pts+1;k++)
    outErr[i]+=g[k] * lambda[k];
   }

  fwrite(outImg, sizeof(char), xdim, fout);
  fwrite(outErr, sizeof(char), xdim, ferr);
 }
 
 
 free(outImg);
 free(outErr);
 free(x);
 free(y);
 free(val);
 free(dist);
 free(sv);

 fclose(ferr); 
 fclose(fout); 
 fclose(fin); 
 return (EXIT_SUCCESS);

}


double * fit_variogram_model(float *dist, float *sv, int nbins, int flag){

 double **x, *y;
 int dim=2;
 
 x = allocateDoubleMatrix(dim+1,dim);
 y = allocateDoubleVector(dim);
 x[0][0]=0.0; x[0][1]=1.0;
 x[1][0]=-50.0; x[1][1]=20;
 x[2][0]=-100.0; x[2][1]=30.0;
 
 printf("\nSimplex\n");
 simplexFit(x,2,dist,sv,nbins,flag);
 printf("%f %f\n",x[0][0],x[0][1]);

 y[0]=x[0][0];
 y[1]=x[0][1]; 
 

 return y;
}

float merit_function(double *x, float *dist, float *sv, int n, int flag){

 float e=0.0;
 int i;

 if (flag==1)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-linear_model(x[0],x[1],dist[i]),2);
  
 if (flag==2)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-exponential_model(x[0],x[1],dist[i]),2);
 
 if (flag==3)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-spherical_model(x[0],x[1],dist[i]),2);
  
 if (flag==4)
  for (i=0;i<n;i++)
   e+=pow(sv[i]-gaussian_model(x[0],x[1],dist[i]),2);
  
 return e;

}




double calc_krig_value(double *lambda, float * val, int pts){

 double calc_krig_value=0.0;
 int i;

 for (i=0;i<pts;i++)
  calc_krig_value+=lambda[i]*(double)val[i];

 return calc_krig_value;

}

double ** calc_gamma_matrix(float *x, float *y, int n, float(*f)(float, float, float), float a, float c){

 double **gamma; 
 int i,j;

 gamma=allocateDoubleMatrix(n+1, n+1);
 
  for (i=0; i<=n; i++)
   for (j=0; j<=n;j++)
    gamma[i][j]=0.0;

  for (i=0; i<n; i++){
   gamma[i][n]=1.0;
   gamma[n][i]=1.0;
  }

 for (i=0; i<n; i++)
  for (j=0; j<n;j++)
   gamma[i][j]=f(a,c,sqrt(SQUARE(x[i]-x[j])+SQUARE(y[i]-y[j])));    
  
 
 return gamma;
}



double *calc_g_vector(float *x, float *y, int n, float xprime, float yprime, float (*f)(float, float, float), float a, float c){

 
 int i;
 double *g;
 
 g=allocateDoubleVector(n+1);

 for (i=0; i<n; i++)
  g[i]=(double)f(a,c, sqrt(SQUARE(x[i]-xprime)+SQUARE(y[i]-yprime))); 
 
 g[n]=1.0;

 return g;
}


float spherical_model(float c, float a, float h){

 float gamma;

 if (h <=a)
  gamma=c + 1.5*(h/a)-0.5*pow(h/a,3);
 else
  gamma=c;

 return gamma;
}

float exponential_model(float c, float a, float h){
 
 float gamma;
 gamma= c + 1.0 - exp((3*h)/a);
 
 return gamma;
}

float gaussian_model(float c, float a, float h){
 
 float gamma;
 gamma=c + 1.0 - exp((3*h*h)/(a*a));
 
 return gamma;
}

float linear_model(float c, float a, float h){
 
 float gamma;
 gamma= c +  a * h;
 
 return gamma;
}


int variogram(float *x, float *y, float *val, float *dist, float *sv, int n, int pts, float lag_tolerance){

 int i,j,k=0;
 int lo, hi;
 int nbins;
 int *histogram;
 int bin; 
 float *tot, *v;

 fprintf(stdout,"\nDifference\n");


 for (i=0; i<pts-1; i++){
  for (j=i; j<pts-1;j++){
    dist[k]=sqrt(SQUARE(x[i]-x[j+1])+SQUARE(y[i]-y[j+1]))-TINY;
    sv[k]=SQUARE(val[i]-val[j+1])/2.0;
    fprintf(stdout,"%f %f %d\n",dist[k],sv[k],k);
    k++;
  }
 }
  
 lo=floor(min(dist,n));
 hi=ceil(max(dist,n));
 nbins=(int)(((float)hi-(float)lo)/lag_tolerance);
 fprintf(stdout,"%d %d %d\n",lo,hi,nbins);

 if((histogram = (int *) calloc((nbins), sizeof(int))) == NULL) memoryCheck();
 if((tot = (float *) calloc((nbins), sizeof(float))) == NULL) memoryCheck();
 if((v = (float *) calloc((nbins), sizeof(float))) == NULL) memoryCheck();
  
 for (i=0;i<nbins;i++){
  tot[i]=0.0;
  v[i]=0.0;
 }

 for (j=0;j<n;j++){
  bin=(int)(((int)*(dist+j)-(int)lo) / lag_tolerance);

  fprintf(stdout,"%f %d\n",*(dist + j),(int)*(dist+j)-(int)lo);

  histogram[bin]++;
  tot[bin]=tot[bin]+*(dist+j);
  v[bin]=v[bin]+*(sv + j);
 } 

 fprintf(stdout,"Semivariogram\n");

 for (i=0;i<nbins;i++){
  tot[i]=tot[i]/(float)histogram[i];
  v[i]=v[i]/histogram[i];
  fprintf(stdout,"%d %f %f\n",histogram[i], tot[i], v[i]);
 }

 for (i=0;i<nbins;i++){
  dist[i]=tot[i];
  sv[i]=v[i];
 }

 return nbins;

}


void krigingUsage(){

 fprintf(stderr,"Usage: earth -kriging pointFile outImg outErr [Model] [Lag_tolerance] [nugget] [dx] [dy]\n");	
 fprintf(stderr, "    pointFile       Vector file of points in text format\n");
 fprintf(stderr, "    outImg          Output kriged image\n");
 fprintf(stderr, "    outErr          Output kriged variance image\n");
 fprintf(stderr, "    model           1: linear (default), 2: exponential, 3:spherical, 4: gaussian\n");
 fprintf(stderr, "    lag_tolerance   Semivariogram lag tolerance (default=1.0)\n");
 fprintf(stderr, "    nugget          Include nugget: 1, yes; 2, no (default=1)\n");
 fprintf(stderr, "    dx              pixel size in x\n");
 fprintf(stderr, "    dx              pixel size in y\n");
 exit(EXIT_FAILURE);

}


int getNumPts(char *ptsFile){

 int row=0;
 char *buffer, *p;
 FILE *ftext;

 ftext  = openFile("",ptsFile,  "r"); 
 if((buffer = (char *) calloc(TEXT_LINE_LEN, sizeof(char))) == NULL) memoryCheck();
 
 while(fgets(buffer, TEXT_LINE_LEN, ftext)!=NULL){
  
  p=buffer;
  while(*p==' ' || *p=='\t' || *p=='\r') p++;
  if(*p!='\n') row++;

 } 
   
 free(buffer);
 fclose(ftext);
 return row;
}


int readPoint(FILE *ftext, float *x, float *y, float *val, int pts){
 
 char buffer[TEXT_LINE_LEN], *p;
 int j;

 for(j=0;j<pts;j++){
  fgets(buffer, TEXT_LINE_LEN, ftext);
  
  p=buffer;
  while(*p==' ' || *p=='\t' || *p=='\r') p++;
  if(*p=='\n') filePtsError(ftext);
    
  sscanf(buffer,"%f %f %f",&x[j],&y[j],&val[j]);

 }    	

 return (EXIT_SUCCESS);
}

int filePtsError()
{

 fprintf(stderr,"\nInput pts file not properly formatted\n\n");
 fprintf(stderr," x1 y1 val1 \n");
 fprintf(stderr," x2 y2 val2 \n");
 fprintf(stderr," .. .. .... \n");
 fprintf(stderr," xn yn valn \n\n");

 exit(EXIT_FAILURE);
}
