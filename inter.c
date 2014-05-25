#include "elevator.h"

int main()
{
	int temp;
	printf("The inter_process exec successfully!\n\n");
	
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
	
		puts("Please input the the destination:\n");
		puts("1\t2\t3\t4\t5\n");
		scanf("%d",&temp);
		switch(temp){
			case 1:p_map->destination=one;break;
			case 2:p_map->destination=two;break;
			case 3:p_map->destination=three;break;
			case 4:p_map->destination=four;break;
			case 5:p_map->destination=five;break;
			default:puts("Error\n");break;
		}
		puts("Please input the door status:\n");
		puts("closed:1\topen:2\n");
		scanf("%d",&temp);
		switch(temp){
			case 1:p_map->door=closed;break;
			case 2:p_map->door=open;break;
			default:puts("Error\n");break;
		}
	
	return 0;
}
