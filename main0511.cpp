/*
2006�껪Ϊ�з�����Ա����(2006��10��29�����ɶ����ӿƼ���ѧ������Ŀ)
��Ŀ���������Ĺ���100�����򳡣�ÿ����λ����������1��100�ĳ��أ�����ĳ��ر�ű����������ģ�
��������Ѿ���������λռ�ã��Ͳ����ٴ�ʹ�ã����ҵ�λ��ʹ���곡�غ����黹��
�����һ��������ϵͳ(c���ԣ���
����ʱ5���ӣ�
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct TennisGround
{
    int num;
    //�˴�֮����ʹ��const�޶�������Ϊ�����ʹ�ã�����agentName = " "�����㱨����
    //��Ϊ���ַ�������ת����char *�ǲ�����ġ�
    const char *agentName;
};

typedef struct TennisGround TG;

void mallocTG(TG *total);
void freeTG(TG *total);

void mallocTG(TG *total)
{
    // size: how many tennis grounds do you want to get
    // start: start from which tennis ground
    // count: from start to the number that you really get
    int size, start, count = 0;
    char *agentName = (char*)malloc(sizeof(char)*10);
    printf("Please input your agentName:");
    scanf("%s", agentName);
    printf("Please input the size of the TennisGround(1-100):");
    scanf("%d", &size);
    printf("Please input the TennisGround number you want to start(1-100):");
    scanf("%d", &start);

    if(strcmp((total+start)->agentName," ")!=0)
    {
        printf("malloc failed!\n");
        exit(-1);
    }
    else
    {
        while(count < size)
        {
            (total+start+count)->agentName = agentName;
            count++;
        }
    }
}

void freeTG(TG* total)
{
    char *an = (char*)malloc(sizeof(char)*10);
    printf("please input agentName you want to free:");
    scanf("%s", an);
    int count = 1; //��ʹ��0��

    while(count <= 100)
    {
        if(strcmp((total+count)->agentName, an) == 0)
            (total+count)->agentName = " ";

        count++;
    }
    free(an);
}

int main0511()
{
    int i;
    int sw;
    TG *total = (TG*)malloc(sizeof(TG)*101);//��ʹ�õ�0��

    for(i=1; i<=100; i++) //init
    {
        (total+i)->num = i;
        (total+i)->agentName = " ";
    }

    while(1)
    {
        printf("*******Tennis Ground Mallocation******************\n");

        for(i=1; i<=100; i++)
        {
            printf("%d(%s) ", (total+i)->num, (total+i)->agentName);

            if(i%5 == 0)
                printf("\n");
        }

        printf("\n");
        printf("**************************************************\n");
        printf("Please input your choosen:(1-malloc,2-free):");
        scanf("%d", &sw);

        if(sw == 1)
            mallocTG(total);
        else
            freeTG(total);
    }

    return 0;
}
