#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define MAXFLOOR 5
#define SHMID 1441796

enum FLOOR{
	none,one=1,two,three,four,five
};

enum STATUS{
	stop=1,up,down
};

enum DOOR{
	closed=1,open
};

typedef struct {
	enum FLOOR current; //电梯当前所在楼层
	enum FLOOR destination; //电梯目的楼层
	enum STATUS status; //电梯所处状态
	enum DOOR door; //电梯们所处状态 
}info;


