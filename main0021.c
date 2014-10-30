/*
设计一个结构类型，保存一门课程的课程名称、学分和选课人数。
设计一个函数，可以接受用户命令行输入的关于课程的信息，并保存于结构类型的变量中，并返回该结构变量的值。
实现一个关于课程的链表。链表中每一个元素表示一门课程的相关信息。
实现该链表的添加元素功能、按照选课人数排序功能、按照课程名称排序功能和按照课程名称查询功能。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node
{
    char name[125];
    unsigned credit;
    unsigned num;
    struct node* next;
};

typedef struct node NODE;

NODE* create(void);
void delete_List(NODE* head);
void print(NODE* head);
void print_node(NODE *node);
NODE* search(NODE* head,char* name);
NODE* insert(NODE* head,NODE* p0,unsigned short method);
NODE* creat_seq(void);
NODE* delete_Node(NODE* head,char* name);
NODE* sort(NODE* head,unsigned short method);

int main0021()
{
    puts("请按提示操作");
    unsigned short ch = 0;
    char name[125];
    unsigned credit;
    unsigned num;
    NODE *head = NULL,*temp = NULL;

    do
    {
        puts("按照课程名称排序，并显示(0)");
        puts("按照课程学分排序，并显示(1)");
        puts("按照选课人数排序，并显示(2)");
        puts("初始添加信息(3)");
        puts("追加信息(4)");
        puts("显示信息(9)");
        puts("退出(10)");
        scanf("%hu",&ch);

        switch(ch)
        {
        case 0:
            head = sort(head,0);
            print(head);
            break;

        case 1:
            head = sort(head,1);
            print(head);
            break;

        case 2:
            head = sort(head,2);
            print(head);
            break;

        case 3:
            head = create();
            break;

        case 4:
            temp = (NODE*)malloc(sizeof(NODE));
            puts("Input the name credit and num of the class: ");
            scanf("%s %u %u",name,&credit,&num);
            strcpy(temp->name,name);
            temp->credit = credit;
            temp->num = num;
            temp->next = head;
            head = temp;
            break;

        case 9:
            print(head);
            break;

        case 10:
            break;
        }
    }
    while(ch != 5);

    delete_List(head);
    return 0;
}
NODE* create(void)
{
    NODE *head = NULL,*p1 = NULL,*p2 = NULL;
    char name[125];
    unsigned credit;
    unsigned num;
    int n=0;

    do
    {
        puts("Input the name credit and num of the class: ");
        scanf("%s %u %u",name,&credit,&num);

        if(num == 0)
        {
            break;
        }

        n ++;
        p1 = (NODE*)malloc(sizeof(NODE));
        strcpy(p1->name,name);
        p1->credit = credit;
        p1->num = num;
        p1->next = NULL;

        if(n == 1)
        {
            head = p2 = p1;
        }
        else
        {
            p2->next = p1;
            p2 = p1;
        }
    }
    while(1);

    return head;
}
void delete_List(NODE* head)
{
    NODE* p1 = NULL;

    if(head == NULL)
    {
        return ;
    }

    while(head != NULL)
    {
        p1 = head;
        head = head->next;
        free(p1);
    }
}
void print(NODE* head)
{
    NODE* p = NULL;

    if(head == NULL)
    {
        printf("\nlist null\n");
        return ;
    }

    p = head;

    while(p != NULL)
    {
        printf("\n%s,%u,%u\n",p->name,p->credit,p->num);
        p = p->next;
    }
}
void print_node(NODE *node)
{
    if(node == NULL)
    {
        printf("\nIt's NULL!\n");
    }
    else
    {
        printf("\n%s,%u,%u\n",node->name,node->credit,node->num);
    }
}
NODE* search(NODE* head,char* name)
{
    NODE *p = NULL;

    if(head == NULL)
    {
        printf("\nlist null!\n");
        return NULL;
    }

    p = head;

    while(p != NULL)
    {
        if(!strcmp(name,p->name))
        {
            return p;
        }

        p = p->next;
    }

    printf("\nNot Found!\n");
    return NULL;
}
NODE* insert(NODE* head,NODE* p0,unsigned short method)
{
    NODE *p1 = NULL,*p2 = NULL;

    if(head == NULL)
    {
        head = p0;
        p0 -> next = NULL;
    }
    else
    {
        p1 = head;

        if(method == 0) //sorted by the name;
        {
            while((strcmp(p0->name,p1->name)>0) && (p1->next!=NULL))
            {
                p2 = p1;
                p1 = p1->next;
            }

            if(p1 == head && (strcmp(p0->name,p1->name)<0))
            {
                p0->next = head;
                head = p0;
            }
            else if(strcmp(p0->name,p1->name)<0)
            {
                p2->next = p0;
                p0->next = p1;
            }
            else
            {
                p1->next = p0;
                p0->next = NULL;
            }
        }
        else if(method == 1) //sorted by the credit
        {
            while((p0->credit > p1->credit) && (p1->next!=NULL))
            {
                p2 = p1;
                p1 = p1->next;
            }

            if(p1 == head && (p0->credit < p1->credit))
            {
                p0->next = head;
                head = p0;
            }
            else if(p0->credit < p1->credit)
            {
                p2->next = p0;
                p0->next = p1;
            }
            else
            {
                p1->next = p0;
                p0->next = NULL;
            }
        }
        else if(method == 2) //sorted by the num
        {
            while((p0->num > p1->num) && (p1->next!=NULL))
            {
                p2 = p1;
                p1 = p1->next;
            }

            if(p1 == head && (p0->num < p1->num))
            {
                p0->next = head;
                head = p0;
            }
            else if(p0->num < p1->num)
            {
                p2->next = p0;
                p0->next = p1;
            }
            else
            {
                p1->next = p0;
                p0->next = NULL;
            }
        }
        else
        {
            puts("Wrong parameter!");
        }
    }

    return head;
}
NODE* creat_seq(void)
{
    return NULL;
}
NODE* delete_Node(NODE* head,char* name)
{
    return NULL;
}
NODE* sort(NODE* head,unsigned short method)
{
    NODE *p = NULL,*temp = NULL;

    if(head == NULL)
    {
        printf("\nlist null!\n");
        return NULL;
    }

    p = head->next;
    head->next = NULL;

    while(p!=NULL)
    {
        temp = p->next;
        head = insert(head,p,method);
        p = temp;
    }

    return head;
}
