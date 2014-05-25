#include "elevator.h"
  
int main(int argc,char *argv[])
{
	pid_t pid;
/*start create elevator_process*/
	if((pid=fork())<0)
	{
		perror("Error!The elevator_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The elevator_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/elevator","elevator",NULL)==-1)
		{
			perror("The elevaor_process exec error!\n");
		}
	}
/*end create elevator_process*/
	sleep(1);
/*start create inter_process*/
	if((pid=fork())<0)
	{
		perror("Error!The inter_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The inter_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/inter","inter",NULL)==-1)
		{
			perror("The inter_process exec error!\n");
		}
	}
/*end create inter_process*/
	sleep(1);
/*start create floor_one_process*/
	if((pid=fork())<0)
	{
		perror("Error!The floor_one_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The floor_one_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/floor_one","floor_one",NULL)==-1)
		{
			perror("The floor_one_process exec error!\n");
		}
	}
/*end create floor_one_process*/
	sleep(1);
/*start create floor_two_process*/
	if((pid=fork())<0)
	{
		perror("Error!The floor_two_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The floor_two_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/floor_two","floor_two",NULL)==-1)
		{
			perror("The floor_two_process exec error!\n");
		}
	}
/*end create floor_two_process*/
	sleep(1);
/*start create floor_three_process*/
	if((pid=fork())<0)
	{
		perror("Error!The floor_three_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The floor_three_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/floor_three","floor_three",NULL)==-1)
		{
			perror("The floor_three_process exec error!\n");
		}
	}
/*end create floor_three_process*/
	sleep(1);
/*start create floor_four_process*/
	if((pid=fork())<0)
	{
		perror("Error!The floor_four_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The floor_four_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/floor_four","floor_four",NULL)==-1)
		{
			perror("The floor_four_process exec error!\n");
		}
	}
/*end create floor_four_process*/
	sleep(1);
/*start create floor_five_process*/
	if((pid=fork())<0)
	{
		perror("Error!The floor_five_process can't create!\n");
	}
	else if(pid==0)
	{
		printf("The floor_five_process create successfully!\n");
		if(execl("/home/jiangxin/Elevator/floor_five","floor_five",NULL)==-1)
		{
			perror("The floor_five_process exec error!\n");
		}
	}
/*end create floor_five_process*/
	while(1){
	}
	system("pause");
	return 0;
}
