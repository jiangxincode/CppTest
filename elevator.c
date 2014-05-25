#include "elevator.h"

int main()
{
	int temp,i;
	pid_t pid;
	printf("The elevator_process exec successfully!\n");
/*srart引入共享内存*/
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
	
	
	//p_map->whocare=p_map->destination;
	p_map->icare=p_map->status;

	if((p_map->current)>(p_map->guest))
	{
		p_map->status=down;
		temp=p_map->current;
				
		for(i=0;i<=(temp-p_map->guest);i++)
		{
			/*start create show_process*/
			if((pid=fork())<0)
			{
				perror("Error!The show_process can't create!\n");
			}
			else if(pid==0)
			{
				printf("The show_process create successfully!\n");
				if(execl("/home/jiangxin/Elevator/show","show",NULL)==-1)
				{
					perror("The show_process exec error!\n");
				}
			}
			sleep(1);
			(p_map->current)--;
			/*end create show_five_process*/
		}
		p_map->current++;
	}

	else if((p_map->current)<(p_map->guest))
	{	
		p_map->status=up;
		temp=p_map->current;
		for(i=0;i<=(p_map->guest-temp);i++)
		{
			/*start create show_process*/
			if((pid=fork())<0)
			{
				perror("Error!The show_process can't create!\n");
			}
			else if(pid==0)
			{
				printf("The show_process create successfully!\n");
				if(execl("/home/jiangxin/Elevator/show","show",NULL)==-1)
				{
					perror("The show_process exec error!\n");
				}
			}
			sleep(1);
			(p_map->current)++;
			/*end create show_five_process*/
		}
		p_map->current--;
	}



	p_map->status=stop;
	p_map->door=open;
	sleep(1);
	p_map->door=closed;
	//p_map->destination=p_map->whocare;
	p_map->status=p_map->icare;
	if(p_map->status==down)
	{
		temp=p_map->current;
		for(i=0;i<=(temp-p_map->destination);i++)
		{
			/*start create show_process*/
			if((pid=fork())<0)
			{
				perror("Error!The show_process can't create!\n");
			}
			else if(pid==0)
			{
				printf("The show_process create successfully!\n");
				if(execl("/home/jiangxin/Elevator/show","show",NULL)==-1)
				{
					perror("The show_process exec error!\n");
				}
			}
			sleep(1);
			(p_map->current)--;
			/*end create show_five_process*/
		}
		p_map->current++;
	}
	if(p_map->status==up)
	{
		temp=p_map->current;
		printf("%d\n\n\n",temp);
		for(i=0;i<=(p_map->destination-temp);i++)
		{
			/*start create show_process*/
			if((pid=fork())<0)
			{
				perror("Error!The show_process can't create!\n");
			}
			else if(pid==0)
			{
				printf("The show_process create successfully!\n");
				if(execl("/home/jiangxin/Elevator/show","show",NULL)==-1)
				{
					perror("The show_process exec error!\n");
				}
			}
			sleep(1);
			(p_map->current)++;
			/*end create show_five_process*/
		}
		p_map->current--;
	}

	return 0;
}
