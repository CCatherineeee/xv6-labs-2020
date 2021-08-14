#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"
//#include<string.h>

#define T_DIR  1  // Directory
#define T_FILE  2  // File
#define T_DEVICE  3  // Device

void path_name(char* path,char* target)
{
    int len = strlen(path);
    char* i;
    for(i = path + len; i >= path && *i != '/'; i--);
    i++;
    char fname[512];
    strcpy(fname, i);
    int res = strcmp(target,fname);
    if(res == 0)
    {
        printf("%s \n",path);
        return;
    }

}

void find(char* path,char* target)
{
    char buf[512], *p;
    struct dirent de;
    int fd = open(path,O_RDONLY);
    if(fd < 0)
    {
        printf("open failed,path: %s\n",path);
        return;
    }
    //printf("%s %d\n",path,fd);
    struct stat st;
    if(fstat(fd,&st) < 0)
    {
        printf("cannot save stat\n");
        close(fd);
        return;
    }
    if(st.type == T_DIR)
    {
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("path too long\n");
            close(fd);
            return;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            //0为空闲
            if(de.inum == 0) continue;
            //.. .不递归
            ///printf("find into %s %d\n",de.name,st.type);
            if(strcmp(de.name, ".")==0 || strcmp(de.name, "..")==0) continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf,target);
        }


    }
    else if(st.type == T_FILE)
    {
       // printf("file: %s  type: %d \n",path,st.type);
        path_name(path,target);
    }
    close(fd);
}


int main(int argc, char *argv[]){
    if (argc < 3){
        printf("Please input like : find [path] [filename]\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}

