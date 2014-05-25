#include "elevator.h"

#define BUFSZ 4096

int main()
{
	int shm_id;	//共享内存标识符
	key_t key;
	key=ftok(".",1);	//利用当前目录索引节点号，子序号为1
	shm_id=shmget(key,BUFSZ,0666|IPC_CREAT);
	if(shm_id<0)
	{
		perror("shmget failed!\n");
		exit(1);
	}
	printf("Create a shared memory segment successfully:%d\n",shm_id);
	system("ipcs -m");
	return 0;
}
