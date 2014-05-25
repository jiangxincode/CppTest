#include "elevator.h"
  
int main(int argc,char *argv[])
{
	pid_t pid;
	int temp;
	
/*start引入共享内存*/
	info *p_map;
	key_t key;
	int shmid;
	if((key=ftok(".",1))<0)
	{
		perror("ftok error!\n");
		exit(1);
	}
	
	shmid=shmget(key,BUFSZ,0666|IPC_CREAT);
	if(shmid<0)
	{
		perror("shmget error!\n");
		exit(1);
	}	
	p_map=(info *)shmat(shmid,NULL,0);	//附加共享内存
/*end引入共享内存*/

/*start对info进行初始化*/
	p_map->current=one;
	p_map->destination=none;
	p_map->guest=none;
	p_map->status=stop;
	p_map->door=closed;
	p_map->whocare=none;
	p_map->icare=stop;
/*end对info进行初始化*/	

	while(1)
	{
		puts("Please input which floor that you are:\n");
		puts("1\t2\t3\t4\t5\n");
		scanf("%d",&temp);
		switch(temp){
			case 1:p_map->guest=one;break;
			case 2:p_map->guest=two;break;
			case 3:p_map->guest=three;break;
			case 4:p_map->guest=four;break;
			case 5:p_map->guest=five;break;
			default:puts("Error\n");break;
		}

	/*start create floor_one_process*/
		if(p_map->guest==one)
		{
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
		}		
	/*end create floor_one_process*/

	/*start create floor_two_process*/
		if(p_map->guest==two)
		{
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
		}		
	/*end create floor_two_process*/
	
	/*start create floor_three_process*/
		if(p_map->guest==three)
		{
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
		}		
	/*end create floor_three_process*/
		
	/*start create floor_four_process*/
		if(p_map->guest==four)
		{
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
		}
	/*end create floor_four_process*/
		
	/*start create floor_five_process*/
		if(p_map->guest==five)
		{
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
		}		
	/*end create floor_five_process*/
	
		//wait(NULL);
		waitpid(pid,NULL,0);
		
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

		//wait(NULL);
		waitpid(pid,NULL,0);
		
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

		//wait(NULL);
		waitpid(pid,NULL,0);
		system("sl");
		sleep(1);

	}
	return 0;
}
