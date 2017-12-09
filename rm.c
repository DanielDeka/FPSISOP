#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include <assert.h>
#include <stdarg.h>


char* strcat(char* s1, const char* s2){
    char* b = s1;
    while(*s1)
        ++s1;
    while(*s2)
        *s1++ = *s2++;

    *s1 = 0;

    return b;
}

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  strcat(buf,"\0");
  return p;
}

void rf(char *path){
  char a[512], *p;
  char *temp=malloc(100);
  memset(temp,0,sizeof temp);
  int fd;
  struct dirent d;
  struct stat st;
 
  if((fd = open(path, 0)) < 0 )
    return;
 
  if(fstat(fd, &st) < 0){
    close(fd);
    return;
  }
 
  switch(st.type){
    case T_FILE:
      break;
      
    case T_DIR:
      if(strlen(path) + 1 + DIRSIZ + 1 > sizeof a)
        break;
      strcpy(a, path);
      p = a+strlen(a);
      *p++ = '/';
      while(read(fd, &d, sizeof(d)) == sizeof(d)){
        if(d.inum == 0)
          continue;
        memmove(p, d.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(a, &st) < 0)
          continue;
        strcpy(temp,path);
        strcat(temp, "/");
        strcat(temp, fmtname(a));
        strcat(temp, "/0");
        if(strcmp(fmtname(a),".") == 0)
             continue;
        if(strcmp(fmtname(a),"..") == 0)
             continue;
        rf(temp);
    }
   break;
   }
   close(fd);
   unlink(path);
}

 int main(int argc, char *argv[]){
   int n;
   if(argc < 2){
     printf(2, "Usage: rm files...\n");
     exit();
   }
   
  if(!strcmp(argv[1], "-rf")){
    int k = open(".a", O_CREATE | O_RDWR);
    char *a = malloc(100);
    memset(a,0,100);
    read(k, a, 100);
    char *temp = malloc(100);
    memset(temp,0,sizeof temp);
    if(*argv[2]!='/')
      strcat(temp,a);
    strcat(temp, argv[2]);
    rf(temp);
    exit();
  }
   for(n = 1; n < argc; n++){
     if(unlink(argv[n]) < 0){
       printf(2, "rm: %s failed to delete\n", argv[n]);
       break;
      }
    }
  exit();
}
