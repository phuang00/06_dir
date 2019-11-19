#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
  char file[100];
  if (argc > 1){
    strcpy(file, argv[1]);
  }
  else{
    printf("Directory to Scan: ");
    fgets(file, 100, stdin);
    file[strlen(file) - 1] = 0;
  }
  DIR *stream = opendir(file);
  if (errno > 0){
    printf("errno: %s\n", strerror(errno));
  }
  struct dirent *entry = readdir(stream);
  int size = 0;
  printf("Statistic for directory: %s\n", file);
  while (entry != NULL) {
    struct stat info;
    char *name;
    sprintf(name, "%s/%s", file, entry->d_name);
    stat(name, &info);
    if (errno > 0){
      printf("errno: %d, %s\n", errno, strerror(errno));
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
