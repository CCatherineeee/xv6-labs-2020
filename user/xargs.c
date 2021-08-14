#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Please input like : xargs '[-option] [command]\n");
        exit(1);
    }
    char* finalArgv[64];
    int POS = 1;
    finalArgv[0] = argv[1];
    for(int i = 2;i < argc; i++)
    {
        finalArgv[POS] = argv[i];
        POS++;
    }
    
    char buf[32];

    while(read(0,buf,32) != 0)
    {
        char* p = malloc(32);
        int pos = 0;
        //检查参数
        for(int i = 0; i<strlen(buf); i++)
        {
            if(buf[i] == ' ')
            {
                p[pos]=0;
                finalArgv[POS] = p;
                POS++;
                pos = 0;
                p=malloc(32);
            }
            else if(buf[i] == '\n')
            {
                p[pos] = 0;
                finalArgv[POS] = p;
                int pid = fork();
                if(pid == 0)
                {
                    exec(argv[1],finalArgv);
                }
                else
                {
                    wait(0);
                }
                //重置参数数组
                POS = argc-1;
            }
            else
            {
                p[pos] = buf[i];
                pos++;
            }
        }
        

    }
    
    for(int i=0;i<POS;i++)
        free(finalArgv[i]);
    exit(0);
}
