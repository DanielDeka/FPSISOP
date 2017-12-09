<<<<<<< HEAD
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buff[600];

int main(int argc, char *argv[]){

	int f1,f2,n;
	if (argc<2)
	{
		printf(2, "Kegunaan: ganti nama file\n");
		exit();
	}

	if((f1 = open(argv[1], O_RDONLY)) < 0) {
		printf(1, "gagal buka file %s\n",argv[1]);
		exit();
	}

	f2 = open(argv[2], O_CREATE|O_RDWR)

	while((n=read(file1, buff,sizeof(buff))) > 0){
		write(file2,buff,n);
		}

	close(f1);
	close(f2);
	
	exit();
}
=======
#include <syscall.h>
#include <stdio.h>
#include <assert.h>

int rename(const char* src, const char* dst)
{
  assert(0 && "not implemented yet.");
  return 0;
}

sysexit();
>>>>>>> 94cadf717a7e8f3484b69e2438005c45d79c9c86
