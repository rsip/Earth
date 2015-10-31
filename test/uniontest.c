#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
 
typedef union Data
{
   char  *c;
   short *i;
   float *f;
   double *d;
   void   *s;
} data_t;


int cp8(data_t *, data_t *, int, int);
int cp16(data_t *, data_t *, int, int);
int cp32(data_t *, data_t *, int, int);
int cp64(data_t *, data_t *, int, int);

 
int main( )
{
   
  data_t data;  
  data_t dataOut;      
  int bpp=1;
  int bytes=20;
  
  data.s = calloc(bytes,bpp);
  dataOut.s = calloc(bytes,bpp); 
 
 switch (bpp){
  case 1:
   cp8(&data,&dataOut,bytes,bpp);
   break;
  case 2:
   cp16(&data,&dataOut,bytes,bpp);
   break;
  case 4:
   cp32(&data,&dataOut,bytes,bpp);
   break;
  case 8:
   cp64(&data,&dataOut,bytes,bpp);
   break; 
  default:
   break;
 }

 free(data.s);
 free(dataOut.s);

 return 0;
}


int cp8(data_t *data, data_t *dataOut, int bytes, int bpp){
 
 int i;
 
 for (i=0;i<bytes;i++)
   data->c[i]=i;
  
 for (i=0;i<bytes;i++)
  dataOut->c[bytes-1-i]=data->c[i];

  for (i=0;i<bytes;i++)
   printf( " %d\n", dataOut->c[i]);

return (EXIT_SUCCESS);

}

int cp16(data_t *data, data_t *dataOut, int bytes, int bpp){
 
 int i;
 
  for (i=0;i<bytes;i++)
   data->f[i]=i;
  memcpy(dataOut->f,data->f,bytes*bpp);
  for (i=0;i<bytes;i++)
   printf( " %f\n", dataOut->f[i]);

return (EXIT_SUCCESS);

}


int cp32(data_t *data, data_t *dataOut, int bytes, int bpp){
 
 int i;
 
  for (i=0;i<bytes;i++)
   data->f[i]=i;
  memcpy(dataOut->f,data->f,bytes*bpp);
  for (i=0;i<bytes;i++)
   printf( " %f\n", dataOut->f[i]);

return (EXIT_SUCCESS);

}


int cp64(data_t *data, data_t *dataOut, int bytes, int bpp){
 
 int i;
 
  for (i=0;i<bytes;i++)
   data->d[i]=i;
  memcpy(dataOut->d,data->d,bytes*bpp);
  for (i=0;i<bytes;i++)
   printf( " %f\n", dataOut->d[i]);

return (EXIT_SUCCESS);

}

