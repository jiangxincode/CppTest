#include "elevator.h"
int main()
{
	printf("The inter_show_process exec successfully!\n");
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
	
/*对info进行显示*/
	switch(p_map->current){
		case 1:puts("当前所在楼层：one");break;
		case 2:puts("当前所在楼层：two");break;
		case 3:puts("当前所在楼层：three");break;
		case 4:puts("当前所在楼层：four");break;
		case 5:puts("当前所在楼层：five");break;
		default:puts("ERROR!");break;
	}
	switch(p_map->destination){
		case 0:puts("目标楼层：none");break;
		case 1:puts("目标楼层：one");break;
		case 2:puts("目标楼层：two");break;
		case 3:puts("目标楼层：three");break;
		case 4:puts("目标楼层：four");break;
		case 5:puts("目标楼层：five");break;
		default:puts("ERROR!");break;
	}
	switch(p_map->status){
		case 1:puts("电梯运行状态：stop");break;
		case 2:puts("电梯运行状态：up");break;
		case 3:puts("电梯运行状态：down");break;
		default:puts("ERROR!");break;
	}
	switch(p_map->door){
		case 1:puts("电梯们所处状态：closed");break;
		case 2:puts("电梯们所处状态：open");break;
		default:puts("ERROR!");break;
	}
/*对info进行显示*/	
	
	return 0;
}
