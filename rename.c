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

	f2 = open(argv[2], O_CREATE|O_RDWR);

	while((n=read(file1, buff,sizeof(buff))) > 0){
		write(file2,buff,n);
		}

	if(unlink(argv[1]) < 0){
		printf(2, "gagal hapus file %s\n", argv[1]);
		exit();
	}

	close(f1);
	close(f2);

	exit();
}
