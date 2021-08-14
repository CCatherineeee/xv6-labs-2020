#include "kernel/types.h"
#include "user/user.h"

void prime(int rd){
    
    int temp;
    if(read(rd, &temp, sizeof(int)) <= 0)
    {
        exit(1);
    }
    printf("prime %d\n", temp);
    int p[2];
    int num;
    pipe(p);
    int pid = fork();
    if(pid == 0){
        close(p[1]);
        prime(p[0]);
        return;
    }
    while(read(rd, &num, sizeof(int)) != 0){
        if(num % temp != 0){
            write(p[1], &num, 4);
        }
    }
    close(rd);
    close(p[1]);
    wait(0);
}

int main(){
    int p[2];
    pipe(p);

    int pid = fork();
    if(pid != 0){
        // first
        close(p[0]);
        for(int i = 2; i <= 35; i++){
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }else{
        close(p[1]);
        prime(p[0]);
        close(p[0]);
    }
    exit(0);
}
