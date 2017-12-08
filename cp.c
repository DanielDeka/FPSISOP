#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

int
main(int argc, char *argv[])
{
  int fd, dfd, r;
  char *src;
  char *dest;
  
  if(argc <= 2){
    printf(1, "Pakai 2 argumen\n");
    exit();
  }
  
  src = argv[1];
  dest = argv[2];
  
  if ((fd = open(src, O_RDONLY)) < 0) {
    printf(1, "cp: cannot open source %s\n", argv[1]);
    exit();
  }
  if ((dfd = open(dest, O_CREATE|O_RDWR)) < 0) {
    printf(1, "cp: cannot open destination %s\n", argv[2]);
    exit();
  }
  
  while ((r = read(fd, buf, sizeof(buf))) > 0) {
    w = write(dfd, buf, r);
    if (w != r || w < 0) 
      break;
  }
  
  close(fd);
  close(dfd);

  exit();
}
