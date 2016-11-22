/*
NAME:		dimap2bsq.c 
DESCRIPTION: 	convert from dimap2bsq format
AUTHOR:	 	Will Grey
VERSION:	2015-11-11	
LICENSE:	This is free and unencumbered software 
                released into the public domain.
*/

#include "earth.h"

int dimap2bsq(int argc, char **argv){
 
 metaData hdrData;
 FILE **fin, *fout;
 int file;  

 if (argc != 4)  dimap2bsqUsage();	
 
 fout=openFile("",argv[3],"wb");

 if (checkFileDir(argv[2]) != 1){
  fprintf(stderr,"Input Dimap needs to be a folder\n");
  exit(EXIT_FAILURE);
 }

 hdrData.channels = getNumFiles(argv[2]);
 	
 fin=openMultipleReadFiles(argv[2], hdrData.channels);
 catFile(fin, fout, &hdrData);  	

 for(file = 0; file < hdrData.channels; file++)
  fclose(fin[file]); 
 
 fclose(fout);

 return (EXIT_SUCCESS);
	
}

void dimap2bsqUsage(){
 fprintf(stderr,"Usage: earth -dimap2bsq indir outfile \n\n");
 fprintf(stderr, "   indir          input path (Dimap folder) 1\n");
 fprintf(stderr, "   outImg         output image \n\n");   		
 exit(EXIT_FAILURE);
}

int catFile(FILE **fin, FILE *fout, metaData *hdrData){

 char *img;
 int i, remainderPixels;
 
 if((img  = (char *) calloc(PIXELS,sizeof(char)))== NULL) memoryCheck();	
 
  for (i=0;i<hdrData->channels;i++){ 
   while ((remainderPixels=fread(img,sizeof(char),PIXELS,fin[i])) == PIXELS) 
    fwrite(img,sizeof(char),PIXELS,fout);

   fread(img,sizeof(char),remainderPixels,fin[i]);
   fwrite(img,sizeof(char),remainderPixels,fout);
 }

 free(img);

 return (EXIT_SUCCESS);

}

FILE ** openMultipleReadFiles(char *path, int numFiles){
  
 FILE **f;
 DIR *d;
 struct dirent **dirlist;
 int n;

 strcat(path,"/");
 d = opendir(path);
 int i=0, j=0;
 char filename[TEXT_LINE_LEN], filename2[TEXT_LINE_LEN];
 
 if((f = malloc (sizeof(FILE *) * numFiles)) == NULL) memoryCheck(); 

 if (d){
  
  n=scandir(path,&dirlist,0,alphasort); 
  
  if (n <=0){
   fprintf(stderr,"No images in DIMAP folder\n");
   exit(EXIT_FAILURE);
  }

   printf("Images concatonated:\n"); 

  for (i=0;i<n;i++){
   if (dirlist[i]->d_type == DT_REG 
     && strncmp(".",dirlist[i]->d_name,1)
     && (strstr(dirlist[i]->d_name,HEADER)==NULL) ){
      
     f[j]  = openFile(path, dirlist[i]->d_name,  "rb"); 
     strcpy(filename,path);
     strcat(filename,dirlist[i]->d_name);
     fprintf(stdout,"%s\n",filename);
     if  (j >= 1) compareFileSize(filename2, filename);
     strcpy(filename2,filename);  
     j++;  

   }
  }
 }

 closedir(d);
 return f;
}

int getNumFiles(char *path){
  
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  int i=0;
 
  if (d){
    while ((dir = readdir(d)) != NULL)
     if (dir->d_type == DT_REG 
      && strncmp(".",dir->d_name,1)
      && (strstr(dir->d_name,HEADER)==NULL) )
      i++;
   
    closedir(d);
  }

  return(i);
}

int checkFileDir(char *path){

 struct stat s;
 int dir=1;

 if( stat(path,&s) == 0 ){
  if( s.st_mode & S_IFDIR ){ 
    dir=1; /* directory */
   }
  else if( s.st_mode & S_IFREG ){ 
    dir=0; /* file */ 
   }
 }

 return dir;
}

