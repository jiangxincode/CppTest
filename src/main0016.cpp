/*
2006年华为研发类笔试编程题(2006年10月29日晚，成都电子科技大学考试题目)
题目：网球中心共有100个网球场，每个单位可以来申请1到100的场地，申请的场地编号必须是连续的，
如果场地已经被其他单位占用，就不能再次使用，而且单位在使用完场地后必须归还。
请设计一个完整的系统(c语言）。
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct TennisGround
{
    int num;
    //此处之所以使用const限定，是因为如果不使用，类似agentName = " "的语句汇报警告
    //因为把字符串常量转换成char *是不合理的。
    const char *agentName;
};

typedef struct TennisGround TG;

void mallocTG(TG *total);
void freeTG(TG *total);

void mallocTG(TG *total)
{
    // size: how many tennis grounds do you want to get
    // start: start from which tennis ground
    int size, start;
    char *agentName = (char*)malloc(sizeof(char)*10);
    printf("Please input your agentName:");
    scanf("%9s", agentName);
    printf("Please input the size of the TennisGround(1-100):");
    scanf("%11d", &size);
    printf("Please input the TennisGround number you want to start(1-100):");
    scanf("%11d", &start);

    if(strcmp((total+start)->agentName," ")!=0)
    {
        printf("malloc failed!\n");
        exit(-1);
    }
    else
    {
        int count = 0; // count: from start to the number that you really get

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
    scanf("%9s", an);
    int count = 1; //不使用0号

    while(count <= 100)
    {
        if(strcmp((total+count)->agentName, an) == 0)
        {
            (total+count)->agentName = " ";
        }

        count++;
    }

    free(an);
}

/** \cond */
int main0016()
{
    int i;
    int sw;
    TG *total = (TG*)malloc(sizeof(TG)*101);//不使用第0号

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
            {
                printf("\n");
            }
        }

        printf("\n");
        printf("**************************************************\n");
        printf("Please input your choosen:(1-malloc,2-free):");
        scanf("%11d", &sw);

        if(sw == 1)
        {
            mallocTG(total);
        }
        else
        {
            freeTG(total);
        }
    }

    return 0;
}
/** \endcond */
