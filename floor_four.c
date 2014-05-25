#include "elevator.h"

int main()
{
	int temp=0;
	printf("The floor_four_process exec successfully!\n");
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

	puts("Please input status:\n");
	puts("up:1\tdown:2\n");
	scanf("%d",&temp);
	switch(temp){
		case 1:p_map->status=up;break;
		case 2:p_map->status=down;break;
		default:puts("Error!\n");break;
	}
	return 0;
}
