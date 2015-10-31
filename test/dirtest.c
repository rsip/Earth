#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 

int dimap(char *);

int main(void)
{
  
 dimap("/home/william");
  return(EXIT_SUCCESS);
}

int dimap(char *path){
  
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  
  if (d){
    while ((dir = readdir(d)) != NULL)
     if (dir->d_type == DT_REG)
      printf("%s\n", dir->d_name);
   
    closedir(d);
  }

  return(EXIT_SUCCESS);
}
