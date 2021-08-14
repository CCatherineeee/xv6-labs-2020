#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p1[2],p2[2];    //定义两个管道的输入输出
    char transinfo = 'P';
    pipe(p1);   //父进程写 子进程读的管道
    pipe(p2);   //子进程写 父进程读的管道
    long readsize=sizeof(transinfo);
    int pid=fork();
    if(pid == 0)
    {
        //首先关闭不需要的标识符
        close(p1[1]);
        close(p2[0]);
        //子进程在pipe1进行读
        if(read(p1[0],&transinfo,readsize) != readsize)
        {
            printf("child get info from parent failed\n");
            exit(1);
        }
        else
        {
            //子进程在pipe2中进行写
            printf("%d: received ping\n",getpid());
            if(write(p2[1],&transinfo,readsize) != readsize)
            {
                printf("child transfer info to parent failed\n");
                exit(1);
            }
            exit(0);
        }
    }
    else if(pid > 0)
    {
        close(p1[0]);
        close(p2[1]);
        //父进程在pipe1中进行写
        if(write(p1[1],&transinfo,readsize) != readsize)
        {
            printf("parent transfer info to child failed\n");
            exit(1);
        }
        else
        {
            wait(0);
            //父进程在pipe2中进行读
            if(read(p2[0],&transinfo,readsize) != readsize)
            {
                printf("parent get info from child failed\n");
                exit(1);
            }
            else
            {
                printf("%d: received pong\n",getpid());
            }
            exit(0);
        }
    }
    else
    {
        printf("fork failed");
        exit(1);
    }
} 