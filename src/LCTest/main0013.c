#include<stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<math.h>
#include<unistd.h>
int main0013()
{
	pid_t child;
	int status;
	printf("This will demostrate how to get the child status\n");
	if((child=fork())==-1)
	{
		printf("Fork Error:%s\n",strerror(errno));
		exit(1);
	}
	else if(child==0)
	{
		int i=0;
		printf("I am the child:%d\n",getpid());
		for(i=0;i<1000000;i++);
		i=5;
		printf("I exit with%d\n",i);
		exit(i);
	}
	while(((child=wait(&status))==-1)&(errno==EINTR));
	if(child==-1)
	{
		printf("Wait Error:%s",strerror(errno));
	}
	else if(!status)
	{
		printf("Child %d terminated normally return status is zero\n",child);
	}
	else if(WIFEXITED(status))
	{
		printf("Child %d terminated normally return status is %d\n",child,WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status))
	{
		printf("Child %d terminated due to signal %d znot caught\n",child,WTERMSIG(status));
	}
	return 0;
}

