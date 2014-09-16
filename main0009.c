/*
美团网2014年招聘笔试题
3.
k链表翻转。
给出一个链表和一个数k，比如链表1→2→3→4→5→6
若k=2，则翻转后2→1→4→3→6→5
若k=3,翻转后3→2→1→6→5→4
若k=4，翻转后4→3→2→1→5→6
用程序实现
（非递归可运行代码）
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    struct node *next;
    int data;
} node;

void createList(node **head, int data)
{
    node *pre, *cur, *new;
    pre = NULL;
    cur = *head;

    while(cur != NULL)
    {
        pre = cur;
        cur = cur->next;
    }

    new = (node *)malloc(sizeof(node));
    new->data = data;
    new->next = cur;

    if(pre == NULL)
        *head = new;
    else
        pre->next = new;
}

void printLink(node *head)
{
    while(head->next != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }

    printf("%d\n", head->data);
}

int linkLen(node *head)
{
    int len = 0;

    while(head != NULL)
    {
        len ++;
        head = head->next;
    }

    return len;
}

node* reverseK(node *head, int k)
{
    int i, len, time, now;
    len = linkLen(head);

    if(len < k)
    {
        return head;
    }
    else
    {
        time = len / k;
    }

    node *newhead, *prev, *next, *old, *tail;

    for(now = 0, tail = NULL; now < time; now ++)
    {
        old = head;

        for(i = 0, prev = NULL; i < k; i ++)
        {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        if(now == 0)
        {
            newhead = prev;
        }

        old->next = head;

        if(tail != NULL)
        {
            tail->next = prev;
        }

        tail = old;
    }

    if(head != NULL)
    {
        tail->next = head;
    }

    return newhead;
}


int main0009()
{
    int i, n, k, data;
    node *head, *newhead;

    while(scanf("%d %d", &n, &k) != EOF)
    {
        for(i = 0, head = NULL; i < n; i ++)
        {
            scanf("%d", &data);
            createList(&head, data);
        }

        printLink(head);
        newhead = reverseK(head, k);
        printLink(newhead);
    }

    return 0;
}
