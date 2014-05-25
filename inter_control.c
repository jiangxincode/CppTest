#include "elevator.h"

int main()
{
	printf("The inter_control_process exec successfully!\n\n");
	info *p_map;
	
	p_map=(info *)shmat(SHMID,NULL,0);	//附加共享内存
	
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
