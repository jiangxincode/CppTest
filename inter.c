#include "elevator.h"

int main()
{
	pid_t pid;
	printf("The inter_process exec successfully!\n");

	sleep(7);	//等待所用总进程创建完毕

	printf("所用总进程创建完毕\n\n\n");
	
	printf("开始创建inter下的进程\n");

/*start create The inter_control_process*/
	if((pid=fork())<0)
	{
		perror("The inter_control_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The inter_control_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/inter_control","inter_control",NULL)==-1)
		{
			perror("The inter_control exec error!\n");
		}
	}
/*end create The inter_control_process*/

	return 0;
}
