#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

int
main(int argc, char *argv[])
{
  int fd, dfd, r, w;
  if(argc <= 2){
    printf(2, "Pakai 2 argumen\n");
    exit();
  }
  
  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    printf(1, "cp: cannot open source %s\n", argv[1]);
    exit();
  }
  if ((dfd = open(argv[2], O_CREATE|O_RDWR)) < 0) {
    printf(1, "cp: cannot open destination %s\n", argv[2]);
    exit();
  }
  
  while ((r = read(fd, buf, sizeof(buf))) > 0) {
    w = write(dfd, buf, r);
    
  close(fd);
  close(dfd);

  exit();
}
