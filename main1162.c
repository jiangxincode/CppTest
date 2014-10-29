#include<stdio.h>
#include<stdlib.h>

struct data_array
{
    long num;
    int score;
};
typedef  struct student
{
    long num;
    int score;
    struct student *next;
} NODE;

static NODE * create(struct  data_array *array, int n);
static void display(NODE *head);
void copy_list(NODE *head1, NODE **head2);
static NODE *merge(NODE *head1, NODE *head2);
NODE *del(NODE *head1, NODE *head2);
NODE *insert(NODE *head,NODE *p0);

int main1162(void)
{
    FILE *fp;
    struct  data_array data_a[10],data_b[10];
    NODE *heada,*headb,*a_dup,*b_dup;
    int na=0,nb=0;
    fp=fopen("a.txt","r");

    if(fp==NULL)
    {
        puts("can't open a.txt");
        exit(1);
    }

    while(!feof(fp))
    {
        fscanf(fp,"%11ld%11d",&data_a[na].num,&data_a[na].score);
        na++;
    }
    fclose(fp);

    fp=fopen("b.txt","r");

    if(fp==NULL)
    {
        puts("can't open b.txt");
        exit(1);
    }

    while(!feof(fp))
    {
        fscanf(fp,"%11ld%11d",&data_b[nb].num,&data_b[nb].score);
        nb++;
    }
    fclose(fp);

    heada=create(data_a,na);
    puts("a:");
    display(heada);
    headb=create(data_b,nb);
    puts("b:");
    display(headb);
    copy_list(heada,&a_dup);
    copy_list(headb,&b_dup);
    heada=merge(heada,headb);
    puts("a:");
    display(heada);
    b_dup=del(b_dup,a_dup);
    puts("b:");
    display(b_dup);
    return 0;
}
static NODE * create(struct  data_array *array, int n)
{
    NODE *head=NULL;
    int i;

    for(i=0; i<n; i++)
    {
        NODE *p=(NODE *)malloc(sizeof(NODE));
        p->num=array[i].num, p->score=array[i].score;
        p->next=NULL;
        head=insert(head,p);
    }

    return head;
}
NODE *insert(NODE *head,NODE *p0)
{
    NODE *p1=NULL;

    if(head==NULL)
    {
        head=p0;
        p0->next=NULL;
    }
    else
    {
        p1=head;
        NODE *p2=NULL;

        while((p0->num>p1->num) && (p1->next!=NULL))
        {
            p2=p1;
            p1=p1->next;
        }

        if(p1==head&&(p0->num<p1->num))
        {
            p0->next=head;
            head=p0;
        }
        else if(p0->num<p1->num)
        {
            p2->next=p0;
            p0->next=p1;
        }
        else
        {
            p1->next=p0;
            p0->next=NULL;
        }
    }

    return head;
}
static void display(NODE *head)
{
    NODE *p=NULL;

    if(head==NULL)
    {
        printf("\nlist null!\n");
        return;
    }

    p=head;

    while(p!=NULL)
    {
        printf("\t%ld\t%d\n",p->num,p->score);
        p=p->next;
    }
}
void copy_list(NODE *head1, NODE **head2)
{
    NODE *p=head1,*stu,*p1;
    int num=0;

    while(p!=NULL)
    {
        num++;
        stu=(NODE *)malloc(sizeof(NODE));
        stu->num=p->num;
        stu->score=p->score;

        if(num==1)
        {
            *head2=stu;
            p1=stu;
        }
        else
        {
            p1->next=stu;
            p1=stu;
        }

        p=p->next;
    }

    p1->next=NULL;
}

static NODE * merge(NODE *head1, NODE *head2)
{
    NODE *p1,*p2,*head,*p;
    p1=head1,p2=head2;

    if(p1->num>p2->num)
        head=p2,p=p2,p2=p2->next;
    else
        head=p1,p=p1,p1=p1->next;

    while(p1!=NULL&&p2!=NULL)
    {
        if(p1->num>p2->num)
            p->next=p2,p=p2,p2=p2->next;
        else if(p1->num<p2->num)
            p->next=p1,p=p1,p1=p1->next;
        else
        {
            if(p1->score>p2->score)
                p->next=p1,p=p1;
            else
                p->next=p2,p=p2;

            p1=p1->next;
            p2=p2->next;
        }
    }

    if(p1==NULL) p->next=p2;
    else p->next=p1;

    return (head);
}
NODE * del(NODE *head1, NODE *head2)
{
    NODE *p1,*p2,*p0;
    p0=p1=head1;

    while(p1!=NULL)
    {
        p2=head2;
        int flag=0;

        while(p2!=NULL)
        {
            if(p2->num==p1->num)
            {
                flag=1;
                break;
            }

            p2=p2->next;
        }

        if(flag)
            if(p1==head1)
            {
                head1=head1->next;
                free(p1);
                p0=p1=head1;
            }
            else
            {
                p0->next=p1->next;
                free(p1);
                p1=p0->next;
            }
        else
        {
            p0=p1;
            p1=p1->next;
        }
    }

    return(head1);
}
