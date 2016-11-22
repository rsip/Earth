#include "earth.h"

#define TINY 1e-6
#define PROBABILITY_95_PERCENT 1.96

int kriging_test_1(int argc, char *argv[]){
     
 FILE *fin;
 int pts, n, i, j;
 float *x, *y, *val, *dist, *sv;
 double **gamma;
 double **gamma_inverse;
 double *lambda;
 double *g;
 double valPrime;
 double sum=0.0;
 float xpos=65.0, ypos=137.0;

 if(argc < 4) krigingUsage();

 pts=getNumPts(argv[2]);
 
 fprintf(stdout,"%d\n",pts);

 if((x = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((y = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();
 if((val = (float *) calloc(pts, sizeof(float))) == NULL) memoryCheck();

 fin=openFile("",argv[2],"r");
 
 readPoint(fin,x,y,val,pts);
 n=(pts*(pts-1))/2;

 if((dist = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck();
 if((sv = (float *) calloc(n, sizeof(float))) == NULL) memoryCheck();

 g=calc_g_vector(x,y,pts,xpos,ypos,linear_model, 0.0, 0.0);
 gamma=calc_gamma_matrix(x,y,pts,linear_model, 0.0, 0.0); 

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



int kriging_test_2(int argc, char *argv[]){
     
 FILE *fin;
 int pts, n, i, j, nbins, flag=1, nugget=1;
 float lag_tolerance=1.0;
 float *x, *y, *val, *dist, *sv;
 double **gamma;
 double **gamma_inverse;
 double *lambda;
 double *g;
 double valPrime;
 double *p;
 double sum=0.0;
 float xpos=1.0, ypos=4.0;

 if(argc < 4) krigingUsage();

 if (argc >= 5) flag=atoi(argv[4]);
 if (argc >= 6) lag_tolerance=atoi(argv[5]);
 if (argc >= 7) nugget=atoi(argv[6]);

 pts=getNumPts(argv[2]);
 
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

 if (flag==1){
  g=calc_g_vector(x,y,pts,xpos,ypos,linear_model, p[0], p[1]);
  gamma=calc_gamma_matrix(x,y,pts,linear_model, p[0], p[1]);  
 } 
 if (flag==2){
  g=calc_g_vector(x,y,pts,xpos,ypos,exponential_model, p[0], p[1]);
  gamma=calc_gamma_matrix(x,y,pts,exponential_model, p[0], p[1]);  
 }
 
 if (flag==3){
  g=calc_g_vector(x,y,pts,xpos,ypos,spherical_model, p[0], p[1]);
  gamma=calc_gamma_matrix(x,y,pts,spherical_model, p[0], p[1]);  
 } 

 if (flag==4){
  g=calc_g_vector(x,y,pts,xpos,ypos,gaussian_model, p[0], p[1]);
  gamma=calc_gamma_matrix(x,y,pts,gaussian_model, p[0], p[1]);  
 }

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

float linear_model(float c, float a, float h){

 return 10.0 * exp(-0.3 * h);

}
