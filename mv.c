#include "user.h"
#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "fs.h"

//buat fungsi mkdir utk cpnya
void mkdir_(char *path){
    if(mkdir(path) < 0){
        printf(2, "mkdir: %s failed to create\n", path);
        return;
    }
    char *temp = malloc(100);
    memset(temp, 0, sizeof temp);
    strcat(temp, path);
    strcat(temp, "/.a");
    int f_output = open(temp, 0_CREATE | 0_RDWR);
    if(*path == '/'){
        write(f_output, path, strlen(path));
        close(f_output);
        return;
    }
    int f_input, fd;
    if((f_input = open(".a", 0_RDWR)) < 0){
        printf(1, "cp: cannot open %s\n", path);
        exit();
    }
    strcat(temp, path);
    strcat(temp, "/.a");
    if((fd = open(temp, 0)) < 0){
        int n;
        char a[512];
        while((n = read(f_input, a, sizeof(a))) > 0){
            write(f_output,a,n);
        }
        memset(temp,0,sizeof temp);
        strcat(temp, path);
        strcat(temp, "/");
        write(f_output, temp, strlen(temp));
        close(f_output);
    }
    else
        printf(1, "cp: file %s already exist\n", path);
    close(fd);
    close(f_input);

}
//mengganti dari int main ke fungsi
void move(char *path, char *path1){
    char a[256];
    int f_input, f_output, fd;
    if((f_input = open(path, 0)) < 0){
        printf(1, "cannot open %s\n", path);
        exit();
    }
    struct stat st;
    if(fstat(f_input, &st) < 0)
        return;
    if(st.type == TP_DIR)
        return;
    if((fd = open(path1, 0)) < 0){
        int i;
        f_output = open(path1, 0_CREATE | 0_RDWR);
        while((i = read(f_input, a, sizeof(a))) > 0){
            write(f_output,a,i);
        }
        close(f_output);
    }
    else
        printf(1, "cp : file %s already exist \n", path1);
    close(fd);
    close(f_input);
    unlink(path);
}

int main(int argc, char argv[])
{
  if(argc < 2)
    exit();
  if(strcmp(argv[3], "..") == 0){
    int k = open(".a", 0_CREATE | 0_RDWR);
    char *a = malloc(100);
    memset (a, 0, sizeof a);
    read(k, a, sizeof(a));
    char *temp;
    temp = a + strlen(a)-1;
    while(*temp!='/')
        temp--;
    temp++;
    *temp='\0';
    strcpy(argv[3], temp);
    printf(1, "%s\n", temp);
  }
  
  exit();
}

char* fmtname(char *path){
	static char buf[DIRSIZ+1];
	char *p;
	
	
	for(p=path+strlen(path); p >= path && *p != '/'; p--);
	p++;
	
	
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}
