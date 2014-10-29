/*
华为公司2014届校园招聘软件类上机考试样题
已知2条地铁线路，其中A为环线，B为东西向线路，线路都是双向的。
经过的站点名分别如下，两条线交叉的换乘点用T1、T2表示。
编写程序，任意输入两个站点名称，输出乘坐地铁最少需要经过的车站数量
（含输入的起点和终点，换乘站点只计算一次）。
地铁线A（环线）经过车站：A1 A2 A3 A4 A5 A6 A7 A8 A9 T1 A10 A11 A12 A13 T2 A14 A15 A16 A17 A18
地铁线B（直线）经过车站：B1 B2 B3 B4 B5 T1 B6 B7 B8 B9 B10 T2 B11 B12 B13 B14 B15

输入：输入两个不同的站名
输出：输出最少经过的站数,含输入的起点和终点，换乘站点只计算一次
输入样例：A1 A3
输出样例：3
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <queue>
#include <vector>

using namespace std;

#define MAX 35
#define SUBWAY_A 20
#define SUBWAY_B 15

typedef struct node
{
    int adjvex;
    struct node *next;
} edgenode;

typedef struct
{
    char name[10];
    bool flag;
    edgenode *link;
} vexnode;

const char subway_name1[SUBWAY_A][10]= {"A1","A2","A3","A4","A5","A6","A7","A8","A9","T1","A10","A11","A12","A13","T2","A14","A15","A16","A17","A18"};
const char subway_name2[SUBWAY_B][10]= {"B1","B2","B3","B4","B5","B6","B7","B8","B9","B10","B11","B12","B13","B14","B15"};

void creat(vexnode ga[])
{
    int i;
    edgenode *p;

    for(i=0; i<MAX; i++)
    {
        ga[i].link=NULL;
        ga[i].flag=true;

        if(i<SUBWAY_A)
        {
            strcpy(ga[i].name,subway_name1[i]);
        }
        else
        {
            strcpy(ga[i].name,subway_name2[i-20]);
        }
    }

    for(i=1; i<SUBWAY_A-1; i++) //A地铁建邻接表
    {
        p=(edgenode*)malloc(sizeof(edgenode));
        p->adjvex=i-1;
        p->next=NULL;
        ga[i].link=p;
        p=(edgenode*)malloc(sizeof(edgenode));
        p->adjvex=i+1;
        p->next=NULL;
        ga[i].link->next=p;

        if(i==9)
        {
            p=(edgenode*)malloc(sizeof(edgenode));
            p->adjvex=SUBWAY_A+4;
            p->next=NULL;
            ga[i].link->next->next=p;
            p=(edgenode*)malloc(sizeof(edgenode));
            p->adjvex=SUBWAY_A+5;
            p->next=NULL;
            ga[i].link->next->next->next=p;
        }
        else if(i==14)
        {
            p=(edgenode*)malloc(sizeof(edgenode));
            p->adjvex=SUBWAY_A+9;
            p->next=NULL;
            ga[i].link->next->next=p;
            p=(edgenode*)malloc(sizeof(edgenode));
            p->adjvex=SUBWAY_A+10;
            p->next=NULL;
            ga[i].link->next->next->next=p;
        }
    }

    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A-1;
    p->next=NULL;
    ga[0].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=1;
    p->next=NULL;
    ga[0].link->next=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A-2;
    p->next=NULL;
    ga[SUBWAY_A-1].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=0;
    p->next=NULL;
    ga[SUBWAY_A-1].link->next=p;

    for(i=1; i<SUBWAY_B-1; i++) //B地铁建邻接表
    {
        if(i==4||i==5||i==9||i==10) continue;

        p=(edgenode*)malloc(sizeof(edgenode));
        p->adjvex=SUBWAY_A+i-1;
        p->next=NULL;
        ga[i+SUBWAY_A].link=p;
        p=(edgenode*)malloc(sizeof(edgenode));
        p->adjvex=SUBWAY_A+i+1;
        p->next=NULL;
        ga[i+SUBWAY_A].link->next=p;
    }

    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A+3;
    p->next=NULL;
    ga[SUBWAY_A+4].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=9;
    p->next=NULL;
    ga[SUBWAY_A+4].link->next=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=9;
    p->next=NULL;
    ga[SUBWAY_A+5].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A+6;
    p->next=NULL;
    ga[SUBWAY_A+5].link->next=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A+8;
    p->next=NULL;
    ga[SUBWAY_A+9].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=14;
    p->next=NULL;
    ga[SUBWAY_A+9].link->next=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=14;
    p->next=NULL;
    ga[SUBWAY_A+10].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A+11;
    p->next=NULL;
    ga[SUBWAY_A+10].link->next=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A+1;
    p->next=NULL;
    ga[SUBWAY_A].link=p;
    p=(edgenode*)malloc(sizeof(edgenode));
    p->adjvex=SUBWAY_A+SUBWAY_B-2;
    p->next=NULL;
    ga[SUBWAY_A+SUBWAY_B-1].link=p;

    for(i=0; i<MAX; i++) //打印各邻接节点
    {
        printf("%s:",ga[i].name);
        edgenode *s;
        s=ga[i].link;

        while(s!=NULL)
        {
            printf("->%s",ga[s->adjvex].name);
            s=s->next;
        }

        printf("\n");
    }
}

int main0517()
{
    vexnode ga[MAX];
    creat(ga);
    int i;
    char str[2][10];

    while(scanf("%s%s",str[0],str[1])!=EOF)
    {
        int temp=0;

        for(i=0; i<MAX; i++)
        {
            ga[i].flag=true;

            if(!strcmp(str[0],ga[i].name))
            {
                temp=i;
            }
        }

        queue<vexnode> q;
        q.push(ga[temp]);
        ga[temp].flag=false;
        int count=0;
        int start=0;
        int end=1;
        bool find_flag=false;

        while(!q.empty())
        {
            if(find_flag) break;

            count++;
            printf("************************\n");
            printf("第%d层搜索：",count);
            int temp_end=end;

            while(start<temp_end)
            {
                printf("%s ",q.front().name);

                if(!strcmp(q.front().name,str[1]))
                {
                    find_flag=true;
                    break;
                }

                edgenode *s;
                s=q.front().link;

                while(s!=NULL)
                {
                    if(ga[s->adjvex].flag)
                    {
                        q.push(ga[s->adjvex]);
                        ga[s->adjvex].flag=false;
                        end++;
                        //printf("%s ",ga[s->adjvex].name);
                    }

                    s=s->next;
                }

                q.pop();
                start++;
            }

            printf("\n");
        }

        printf("%d\n",count);
    }

    return 0;
}
