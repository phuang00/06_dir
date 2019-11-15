#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
  DIR *stream = opendir(".");
  if (errno > 0){
    printf("errno: %s\n", strerror(errno));
  }
  struct dirent *entry = readdir(stream);
  int size = 0;
  printf("Statistic for directory: .\n");
  while (entry != NULL) {
    struct stat info;
    stat(entry->d_name, &info);
    if (errno > 0){
      printf("errno: %s\n", strerror(errno));
    }
    size += info.st_size;
    entry = readdir(stream);
  }
  printf("Total Directory Size: %d Bytes\n", size);
  char buffer[50];
  double sized = size;
  char *sizes[] = {"B", "KB", "MB", "GB"};
  int i = 0;
  while (sized >= 1024){
    sized = sized / 1024.0;
    i++;
  }
  if (i == 0){
    sprintf(buffer, "%d%s", size, sizes[i]);
  }
  else{
    sprintf(buffer, "%0.2lf%s", sized, sizes[i]);
  }
  printf("Total Directory Size in human readable form: %s\n", buffer);
  printf("Directories:\n");
  rewinddir(stream);
  entry = readdir(stream);
  while (entry != NULL){
    if (entry->d_type == DT_DIR){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(stream);
  }
  printf("Regular files:\n");
  rewinddir(stream);
  entry = readdir(stream);
  while (entry != NULL){
    if (entry->d_type == DT_REG){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(stream);
  }



  return 0;
}
