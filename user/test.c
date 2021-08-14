#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    char path[64]="./a";
    int fd = open(path,O_RDONLY);
    if(fd < 0)
    {
        printf("open failed\n");
        exit(1);
    }
    struct dirent de;
    while(read(fd,&de,sizeof(de) == sizeof(de)))
    {
        if(de.inum != 0)
        {
            char buf[512];
            printf("de.inum: %d  ",de.inum);
            memmove(buf,de.name,DIRSIZ);
            printf("de.name: %s **",buf);
            printf("\n");
        }
    }
    exit(0);
}

