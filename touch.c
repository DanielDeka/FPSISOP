#include "xv6/types.h"
#include <syscall.h>
#include "xv6/stat.h"
#include "xv6/fcntl.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int
main(int argc, char *argv[])
{
 int i;
 int file;
 if (argc < 2){
  printf("Usage: touch files...\n");
  sysexit();
 }
