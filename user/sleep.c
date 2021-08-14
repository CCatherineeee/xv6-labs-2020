#include "kernel/types.h"
#include "user/user.h"

int main(int argn,char* argv[])
{
	if(argn != 2)
	{
		fprintf(2,"need 2 argument\n");
		exit(1);
	}
	int sleeptime = atoi(argv[1]);
	printf("wait %d,in this time nothing would happen\n" , sleeptime);
	sleep(sleeptime);
	for(int i = 0;i < sleeptime;i++)
	{
		printf("%d left\n",10-i);
		sleep(1);
	}
	exit(0);
}
