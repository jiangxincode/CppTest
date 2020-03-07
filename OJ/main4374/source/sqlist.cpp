#include <stdlib.h>

#define MAXSIZE 50

struct strqueue
{
	int queue[MAXSIZE];
	int head; /* 队头 */
	int tail; /* 队尾 */
	int num;  /* 队元素个数 */
};

bool initqueue(struct strqueue *s)  /* 初始化队列，返回0表示失败，返回1表示成功 */
{
    /* 代码在这里实现 */
    s->head = -1;
    s->tail = -1;
    s->num = 0;
    for(int i=0;i<MAXSIZE;i++)
    {
        s->queue[i]=0;
    }
    return 1;
}

bool enqueue(struct strqueue *s, int x) /* 进队列，返回0表示失败，返回1表示成功 */
{
    /* 代码在这里实现 */
    if(s->num < MAXSIZE)
    {
        if((s->head == -1)&&(s->head == -1))
        {
            s->head=0;
            s->tail=0;
            s->queue[s->tail]=x;
            s->num = 1;
            return 1;

        }
        else
        {
            s->tail=(s->tail+1) % MAXSIZE;
            s->queue[s->tail] = x;
            s->num++;
            return 1;
        }

    }
    else
    {
        return 0;
    }
}

bool dequeue(struct strqueue *s, int *x) /* 出队列，返回0表示失败，返回1表示成功 */
{
    /* 代码在这里实现 */
    if(s->num == 0)
    {
        return 0;
    }
    if(s->num == 1)
    {
        *x = s->queue[0];
        s->queue[0] = 0;
        s->head = -1;
        s->tail = -1;
        s->num = 0;
        return 1;
    }
    else
    {
        *x = s->queue[s->head];
        s->queue[s->head] = 0;
        s->head = (s->head+1)%MAXSIZE;
        s->num--;
        return 1;
    }
}

int gethead(struct strqueue *s)  /* 获得队列头数值 */
{
    /* 代码在这里实现 */
    if(s->num==0)
    {
        return -1;
    }

    return s->queue[s->head];
}


int gettail(struct strqueue *s)  /* 获得队列尾数值 */
{
    /* 代码在这里实现 */
    if(s->num==0)
    {
        return -1;
    }

    return s->queue[s->tail];
}

int getqueuelenth(struct strqueue *s)  /* 获得队列长度 */
{
    /* 代码在这里实现 */
    return s->num;
}

bool search(struct strqueue *s, int x)  /* 在队列中查找x是否存在，如果存在返回1，否则返回0 */
{
    /* 代码在这里实现 */
    for(int i=0;i<MAXSIZE;i++)
    {
        if(x==s->queue[i])
            return 1;
    }

    return 0;
}