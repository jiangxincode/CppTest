#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#include<gtk/gtk.h>

#define MAXFLOOR 5
#define BUFSZ 4096	//共享内存
#define BUF_MAX 100	//缓冲区最的容纳字符数量

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


