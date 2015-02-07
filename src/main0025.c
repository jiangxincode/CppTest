#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_PART_SIZE 3 //停车场最大停车数量
#define PRIZE 6.00 //停留每小时单价

/**
 * 停车场管理
 * 设停车场是一个可停放n辆车的狭长通道，且只有一个大门可供汽车进出。
 * 在停车场内，汽车按到达的先后次序，由北向南依次排列（假设大门在最南端）。
 * 若车场内已停满n辆车，则后来的汽车需在门外的便道上等候，当有车开走时，便道上的第一辆车即可开入。
 * 当停车场内某辆车要离开时，在它之后进入的车辆必须先退出车场为它让路，待该辆车开出大门后，其他车辆再按原次序返回车场。
 * 每辆车离开停车场时，应按其停留时间的长短交费（在便道上停留的时间不收费）。
 * 试编写程序，模拟上述管理过程。
 * 要求以顺序栈模拟停车场，以链队列模拟便道。
 * 从终端读入汽车到达或离去的数据，每组数据包括三项：
 * 1，是“到达”还是“离去”；
 * 2，汽车牌照号码；
 * 3，“到达”或“离去”的时刻。
 * 与每组输入信息相应的输出信息为：
 * 如果是到达的车辆，则输出其在停车场中或便道上的位置；
 * 如果是离去的车辆，则输出其在停车场中停留的时间和应缴的费用。
（提示：需另设一个栈，临时停放为让路而从车场退出的车）
 */


/**定义顺序栈-模拟停车场*/
typedef struct STACK
{
    long pos[MAX_PART_SIZE]; //存储车牌号码
    int time[MAX_PART_SIZE]; //存储进入车站的时间
    int point; //最后一辆车的位置指针
} Stack;


/**定义链队列-模拟停车场外*/
typedef struct queue
{
    int num; //存储车牌号
    struct queue *next; //指向下一辆车
} Queue;


/**初始化栈*/
void static InitStack(Stack *s)
{
    s->point=-1;
}

/**初始化队列*/
Queue *InitQueue()
{
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    q->next=NULL;
    return q;
}

/**退栈函数*/
int StackPop(Stack *s,long *i,int *j)
{
    if(s->point==-1)
    {
        return false;
    }
    else
    {
        *i=s->pos[s->point];
        *j=s->time[s->point];
        s->point--;
        return true;
    }
}

/**压栈函数*/
int StackPush(Stack *s,long i,int j)
{
    if(s->point==MAX_PART_SIZE-1)
    {
        return false;
    }
    else
    {
        s->point++;
        s->pos[s->point]=i;
        s->time[s->point]=j;
        return true;
    }
}

/**退队函数*/
int QueuePop(Queue **qH,long *i)
{
    Queue *temp;

    if((*qH)->next==NULL)return false;
    else
    {
        temp=(*qH)->next;
        (*qH)->next=temp->next;
        *i=temp->num;
        free(temp);
        return true;
    }
}

/**入队函数*/
int QueuePush(Queue **q,long i)
{
    Queue *temp;

    if((temp=(Queue *)malloc(sizeof(Queue)))==NULL)return false;
    else
    {
        (*q)->next=temp;
        temp->num=i;
        temp->next=NULL;
        *q=temp;
        return true;
    }
}


int main0025()
{
    int time,i,j;
    long num;
    Stack part;
    Queue *H,*p,*temp,*temp2;
    H=InitQueue();
    p=H;
    InitStack(&part);//初始化队列和栈
    printf("这里是停车场管理程序\n");
    printf("\n停车场最大能停车%d辆,现在停车的单价为每小时%.2f元\n",MAX_PART_SIZE,PRIZE);

    while(1)
    {
        int inStack = 0;
        int inQueue = 0;
        temp=H;
        printf("\n--------------------停车场管理系统---------------------------\n");
        printf("请选择\n\n\t\t(A或a)汽车到达和已到汽车查询\n\t\t(L或l)汽车离开\n\t\t(Q或q)程序退出\n");
        printf("\n-------------------------------------------------------------\n您的选择是:");
        char state = getche();

        if(state=='a'||state=='A'||state=='l'||state=='L')
        {
            printf("\n输入车牌号(数字):");
            scanf("%ld",&num);
            printf("\n输入到达或离开的的时间(24小时制,单位:小时):");
            scanf("%d",&time);
        }

        if(state=='a'||state=='A')
        {
            for(i=0; i<=part.point; i++)
                if(part.pos[i]==num)
                {
                    inStack=1;
                    break;
                }//在车站中查找

            for(j=1; temp->next!=NULL; j++)
            {
                temp2=temp;
                temp=temp2->next;

                if(temp->num==num)
                {
                    inQueue=1;
                    break;
                }
            }//在车站外查找

            if(inStack)
                printf("\n查询结果:输入的汽车已经在车站中第%d个位置停留了%d个小时!\n",i+1,time-part.time[i]);
            else if(inQueue)
                printf("\n查询结果:输入的汽车已经在车站外第%d个位置等候\n",j);
            else
            {
                if(StackPush(&part,num,time)==false)
                {
                    QueuePush(&p,num);
                    printf("\n车站已满,车辆停在场外。\n");
                }
                else printf("\n车辆成功进站!\n");
            }//如果车辆到达，当车站已满，停在车站外，否则，进入车站
        }
        else if(state=='l'||state=='L')     //如果是离开
        {
            for(i=0; i<=part.point; i++)
                if(part.pos[i]==num)
                {
                    inStack=1;
                    break;
                }//在车站中查找

            if(inStack)   //如果在车站中
            {
                printf("\n正要离开的汽车在车站中第%d个位置停留了%d个小时,应付%.2f元\n",i+1,time-part.time[i],(time-part.time[i])*PRIZE);

                while(i<part.point)
                {
                    part.pos[i]=part.pos[i+1];
                    part.time[i]=part.time[i+1];
                    i++;
                }

                part.point--;//把离开的车辆从车站中删除

                if(H->next!=NULL)
                {
                    QueuePop(&H,&num);

                    if(H->next==NULL)p=H;

                    StackPush(&part,num,time);
                    printf("\n停车场空出一位置。场外等候的%ld号汽车入站了!\n",num);
                }//如果车站外有车，入站
            }
            else     //不在车站中
            {
                for(i=1; temp->next!=NULL; i++)
                {
                    temp2=temp;
                    temp=temp2->next;

                    if(temp->num==num)
                    {
                        inQueue=1;
                        break;
                    }
                }//查找是否在车站外

                if(inQueue)
                {
                    printf("\n汽车%d在停车场外,不收费\n",i);
                    temp2->next=temp->next;

                    if(temp==p)p=temp2;

                    free(temp);
                }//在车站外
                else printf("\n错误!你输入了不存在的车牌号!\n");//如果不在车站外，说明输入车辆不存在
            }
        }
        else if(state=='q'||state=='Q')
        {
            printf("\n");
            break;
        }
        else printf("\n输入错误!\n");
    }//end while

    return 0;
}

