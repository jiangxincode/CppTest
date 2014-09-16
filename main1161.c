#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
typedef struct node
{
    int x;
    struct node *next;
} NODE;
NODE *create(void)
{
    int num,i=0;
    NODE *p1,*p2,*head=NULL;

    do
    {
        printf("Input the date of the member %d:\n",++i);
        scanf("%d",&num);

        if(num==0)
            break;

        p1=(NODE *)malloc(sizeof(NODE));
        p1->x=num;
        p1->next=NULL;

        if(i==1)
            head=p2=p1;
        else
        {
            p2->next=p1;
            p2=p1;
        }
    }
    while(1);

    return head;
}
void display1161(NODE *head)
{
    NODE *p=NULL;
    int i=0;

    if(head==NULL)
    {
        printf("\n listnull!");
        return;
    }

    p=head;

    while(p!=NULL)
    {
        printf("The date of the member %d:%d\tThe first address:%x \n",++i,p->x,p);
        p=p->next;
    }
}
void free_all(NODE *head)
{
    NODE *p1=NULL;

    if(head==NULL)
        return;

    while(head!=NULL)
    {
        p1=head;
        head=head->next;
        free(p1);
    }
}
main1161()
{
    NODE *p1;
    p1=create();
    display1161(p1);
    free_all(p1);
}

