#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
  int n;
  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }
  
  for(n = 1; n < argc; n++){
    if(unlink(argv[i]) < 0){
      printf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }

  exit();
}
