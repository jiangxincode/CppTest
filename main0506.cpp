/*
һ��ѧ������Ϣ�ǣ�������ѧ�ţ��Ա��������Ϣ��
��һ����������Щѧ����Ϣ����һ��
����һ��age, ��Щ������ɾ��ѧ���������age��ѧ����Ϣ��
*/

#include "stdio.h"
#include "stdlib.h"

struct stu
{
    char name[20];
    char sex;
    int no;
    int age;
    struct stu * next;
}*linklist;

struct stu *creatlist(int n)
{
    int i;
    struct stu *h,*p,*s; //hΪͷ��㣬pΪǰһ��㣬sΪ��ǰ���
    h = (struct stu *)malloc(sizeof(struct stu));
    h->next = NULL;
    p=h;

    for(i=0; i<n; i++)
    {
        s = (struct stu *)malloc(sizeof(struct stu));
        p->next = s;
        printf("Please input the information of the student: name sex no age \n");
        scanf("%s %c %d %d",s->name,&s->sex,&s->no,&s->age);
        s->next = NULL;
        p = s;
    }

    printf("Create successful!");
    return(h);
}
void deletelist(struct stu *s,int a)
{
    struct stu *p;

    while(s->age!=a)
    {
        p = s;
        s = s->next;
    }

    if(s==NULL)
        printf("The record is not exist.");
    else
    {
        p->next = s->next;
        printf("Delete successful!");
    }
}
void display(struct stu *s)
{
    s = s->next;

    while(s!=NULL)
    {
        printf("%s %c %d %d\n",s->name,s->sex,s->no,s->age);
        s = s->next;
    }
}
void main0506()
{
    struct stu *s;
    int n,age;
    printf("Please input the length of seqlist:\n");
    scanf("%d",&n);
    s = creatlist(n);
    display(s);
    printf("Please input the age:\n");
    scanf("%d",&age);
    deletelist(s,age);
    display(s);
}

