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

for(i = 1 ; i < argc; i++){
  if((file = open(argv[i], O_CREAT|O_RDWR)) < 0){
  printf("touch : %s failed to create\n",argv[i]);
  break;
  }
  sysexit();
 }

sysexit();
return 0;
}
