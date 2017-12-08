#include "user.h"
#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "fs.h"

void cpb(char *path, char *path1){
    char a[512], *p;
    char *temp_1 = malloc(100);
    memset(temp_1, 0, sizeof temp_1);
    char *temp_2 = malloc(100);
    memset(temp_2, 0, sizeof temp_2);
    int fd;
    struct dirent d;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        printf(2, "cp: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        printf(2, "cp: cannot stat %s\n", path);
        return;
    }

    switch(st.type){
        case T_FILE:
            return;

        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof a){
                printf(1, "ls: path too long\n");
                break;
            }

        strcpy(a, path);
        p = a+strlen(a);
        *p++ = '/';
        mkdir_(path1);
        while(read(fd, &d, sizeof(d) == sizeof(d))){
            if(d.inum == 0)
                continue;
            memmove(p, d.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(a, &st) < 0){
                printf(1, "ls: cannot stat %s\n", a);
                continue;
            }
            strcpy(temp_1, path);
            strcat(temp_1, "/");
            strcat(temp_1, fmtname(a));
            strcat(temp_1, "\0");
            strcpy(temp_2, path1);
            strcat(temp_2, "/");
            strcat(temp_2, fmtname(a))
            strcat(temp_2, "\0");
            if(strcmp(fmtname(a), ".a") == 0)
                continue;
            if(strcmp(fmtname(a), ".") == 0)
                continue;
            if(strcmp(fmtname(a), "..") == 0)
                continue;
            move(temp_1, temp_2);
        }
        break;
    }
    close(fd);
}

char* strcat(char* s1, char* s2){
    char* b = s1;
    while(*s1)
        ++s1;
    while(*s2)
        *s1++ = *s2++;

    *s1 = 0;

    return 0;
}

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
  if(strcmp(argv[3], "*") == 0){
    int k = open(".a", 0_CREATE | 0_RDWR);
    char *a = malloc(100);
    memset (a, 0, sizeof a);
    read(k, a, sizeof(a));
    char *temp_1 = malloc(100);
    memset(temp_1, 0, sizeof temp_1);
    if(*argv[2]!='/')
        strcat(temp_1, a);
    strcat(temp_1, argv[2]);
    char *temp_2 = malloc(100);
    memset(temp_2, 0, sizeof temp_1);
    if(*argv[3]!='/')
        strcat(temp_1, a);
    strcat(temp_2, argv[3]);
    cpb(temp_1, temp_2);
  }
  else
    move(argv[2], argv[3]);
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
