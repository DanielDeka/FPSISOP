#include "types.h"
#include <syscall.h>
#include "user.h"
#include "stat.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
 int i;
 int file;
 if (argc < 2){
  printf(1, "Usage: touch files...\n");
  exit();
 }

for(i = 1 ; i < argc; i++){
  if((file = open(argv[i], O_CREAT|O_RDWR)) < 0){
  printf(2, "touch : %s failed to create\n",argv[i]);
  break;
  }
  exit();
 }

exit();
return 0;
}
