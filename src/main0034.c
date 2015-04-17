#include<stdio.h>
#include<string.h>
#include <stdlib.h>
struct list
{
    char data[10];
    struct list *next;
};
typedef struct list node;
typedef node *link;
link static create_list(char array[][10],int num);
void connect(char *ch,link pointer);
int main0034()
{
    char *input;
    char arr1[50][10]= {
        {"众星拱月"},
        {"月光弥漫"},
        {"漫游他方"},
        {"惊天动地"},
        {"地动山摇"},
        {"摇摆不定"},
        {"知情达理"},
        {"望子成龙"},
        {"来龙去脉"},
        {"群龙无首"},
        {"龙飞凤舞"}};
    link ptr;
    ptr=create_list(arr1,10);
    printf("请输入一个成语\n");
    scanf("%s",input);
    connect(input,ptr);
    system("PAUSE");
    return 0;
}
link static create_list(char array[][10],int num)
{
    link tmp1,tmp2,pointer;
    int i;
    pointer=(link)malloc(sizeof(node));
    strcpy(pointer->data,array[0]);
    tmp1=pointer;

    for(i=1; i<=num; i++)
    {
        tmp2=(link)malloc(sizeof(node));
        tmp2->next=NULL;
        strcpy(tmp2->data,array[i]);
        tmp1->next=tmp2;
        tmp1=tmp1->next;
    }

    return pointer;
}
void connect(char *ch,link pointer)
{
    link p=pointer;
    char tmp[10],tmp_head[3],tmp_tail[3];
    strcpy(tmp,ch);
    puts("\n");
    puts(ch);

    while(p->next!=NULL)
    {
        strncpy(tmp_tail,tmp+6,2);
        tmp_tail[2]='\0';
        strncpy(tmp_head,p->data,2);
        tmp_head[2]='\0';

        if(strcmp(tmp_head,tmp_tail)==0)
        {
            puts(p->data);
            strcpy(tmp,p->data);
            p=pointer;
        }
        else
        {
            p=p->next;
        }
    }
}
