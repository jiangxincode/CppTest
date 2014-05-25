#include "elevator.h"

int main()
{
	printf("The inter_control_process exec successfully!\n\n");
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
	
/*对info进行初始化*/
	p_map->current=one;
	p_map->destination=none;
	p_map->status=stop;
	p_map->door=closed;
/*对info进行初始化*/	
	while(1)
	{
	}
	system("pause");
	
	return 0;
}
