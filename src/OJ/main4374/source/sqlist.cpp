#include <stdlib.h>

#define MAXSIZE 50

struct strqueue
{
	int queue[MAXSIZE];
	int head; /* ��ͷ */
	int tail; /* ��β */
	int num;  /* ��Ԫ�ظ��� */
};

bool initqueue(struct strqueue *s)  /* ��ʼ�����У�����0��ʾʧ�ܣ�����1��ʾ�ɹ� */
{
    /* ����������ʵ�� */
    s->head = -1;
    s->tail = -1;
    s->num = 0;
    for(int i=0;i<MAXSIZE;i++)
    {
        s->queue[i]=0;
    }
    return 1;
}

bool enqueue(struct strqueue *s, int x) /* �����У�����0��ʾʧ�ܣ�����1��ʾ�ɹ� */
{
    /* ����������ʵ�� */
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

bool dequeue(struct strqueue *s, int *x) /* �����У�����0��ʾʧ�ܣ�����1��ʾ�ɹ� */
{
    /* ����������ʵ�� */
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

int gethead(struct strqueue *s)  /* ��ö���ͷ��ֵ */
{
    /* ����������ʵ�� */
    if(s->num==0)
    {
        return -1;
    }

    return s->queue[s->head];
}


int gettail(struct strqueue *s)  /* ��ö���β��ֵ */
{
    /* ����������ʵ�� */
    if(s->num==0)
    {
        return -1;
    }

    return s->queue[s->tail];
}

int getqueuelenth(struct strqueue *s)  /* ��ö��г��� */
{
    /* ����������ʵ�� */
    return s->num;
}

bool search(struct strqueue *s, int x)  /* �ڶ����в���x�Ƿ���ڣ�������ڷ���1�����򷵻�0 */
{
    /* ����������ʵ�� */
    for(int i=0;i<MAXSIZE;i++)
    {
        if(x==s->queue[i])
            return 1;
    }

    return 0;
}