#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

char * permissions(int o) {
  if (o == 7)
    return "rwx";
  else if (o == 6)
    return "rw-";
  else if (o == 5)
    return "r-x";
  else if (o == 4)
    return "r--";
  else if (o == 3)
    return "-wx";
  else if (o == 2)
    return "-w-";
  else if (o == 1)
    return "--x";
  else
    return "---";
}

int main() {
  struct stat stats;
  stat("stat.c", &stats);
  int size = stats.st_size;
  int gb = size / 1000000000;
  size %= 1000000000;
  int mb = size / 1000000;
  size %= 1000000;
  int kb = size / 1000;
  size %= 1000;
  int p = stats.st_mode % 512;
  
  printf("Size: %d GB, %d MB, %d KB, %d B\n", gb, mb, kb, size);
  printf("Mode: -%s%s%s\n", permissions(p/64), permissions(p/8%8), permissions(p%8));
  printf("Time of last access: %s\n", ctime(&stats.st_atime));
  return 0;
}
