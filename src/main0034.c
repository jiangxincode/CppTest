#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 20
#define MAXNUM 11

struct list
{
    char data[MAXLENGTH];
    struct list *next;
};
static struct list* create_list(char array[][MAXLENGTH],int num);
static void connect(char *ch,struct list* pointer);

int main0034()
{
    char input[MAXLENGTH];
    char arr1[MAXLENGTH][MAXLENGTH]=
    {
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
        {"龙飞凤舞"}
    };
    struct list* ptr;
    ptr=create_list(arr1,11);
    printf("请输入一个成语\n");
    scanf("%s",input);
    connect(input,ptr);
    system("PAUSE");
    return 0;
}

static struct list* create_list(char array[][MAXLENGTH],int num)
{
    struct list *tmp1,*tmp2,*head;
    head=(struct list *)malloc(sizeof(struct list));
    strcpy(head->data,array[0]);
    tmp1=head;

    for(int i=1; i<num; i++)
    {
        tmp2=(struct list *)malloc(sizeof(struct list));
        tmp2->next=NULL;
        strcpy(tmp2->data,array[i]);
        tmp1->next=tmp2;
        tmp1=tmp1->next;
    }

    return head;
}

static void connect(char *input,struct list* head)
{
    struct list * p=head;
    char tmp[MAXLENGTH],tmp_head[3],tmp_tail[3];
    strcpy(tmp,input);

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
            p=head;
        }
        else
        {
            p=p->next;
        }
    }
}
