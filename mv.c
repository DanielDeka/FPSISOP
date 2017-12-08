#include "user.h"
#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "fs.h"

#define sized 256

int main(int argc, char argv[])
{
  if(argc != 3){
     printf(1, "Please, input the command as [mv src_file dest_file]\n");
     exit();
  }
  int file_src = open(argv[1], O_RDONLY);
	if (file_src == -1){
		printf(1, "open source file failed\n");
		exit();
  }
  struct stat st;
	fstat(file_src, &st);
	if (st.type == T_DIR){
		printf(1, "Source filenya berada di sebuah direktori, file yang berada di direktori:\n");
		ls(argv[1]);
		printf(1, "Program ini tidak bisa membuka filenya yang telah dilist\n");
		printf(1,"Jadi, pindahin satu-satu filenya\n");
		exit();
  }
  
  char c[128] = {};
	strcpy(c, argv[2]);
	int len_1 = strlen(argv[1]);
	int len_2 = strlen(argv[2]);
	if (argv[2][len_2-1] == '/'){
		int i = len_1 - 1;
		for (; i >= 0; i--)
			if (argv[1][i] == '/')
				break;
		i++;
		strcpy(&com[len2], &argv[1][i]);
  }
  
  int file_dest = open(com, O_WRONLY|O_CREATE);
	if (file_dest == -1){
		printf(1, "Membuat file destination gagal\n");
		exit();
  }
  
  char buf[sized] = {};
	int len = 0;
	while((len = read(fd_src, buf, BUF_SIZE)) > 0)
		write(fd_dest, buf, len);
	
	close(file_src);
	close(file_dest);
	
	if(unlink(argv[1]) < 0)
  printf(1, "Menghapus source file gagal\n");
  
  exit();
}
