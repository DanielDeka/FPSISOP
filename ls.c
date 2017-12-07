#include <syscall.h>
#include <stdio.h>
#include <string.h>

#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>

int pathstat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

