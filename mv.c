
#include "types.h"
#include "stat.h"

int main(int argc, char argv[])
{
  if(argc != 3){
     printf(1, "Please, input the command as [mv src_file dest_file]\n");
     exit();
  }
  if((link(argv[1], argv[2]) < 0) || (unlink(argv[1]) < 0)){
  }
  exit();
}
