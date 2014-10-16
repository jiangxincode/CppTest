/**
链表相关
*/

#include <stdlib.h>

struct Node
{
    int data ;
    Node *next ;
};

typedef struct Node Node ;


/**
已知链表的头结点head,写一个函数把这个链表逆序 ( Intel)
*/
Node * ReverseList(Node *head) //链表逆序
{
    if(head == NULL || head->next == NULL)
        return head;

    Node *p1 = head ;
    Node *p2 = p1->next ;
    Node *p3 = p2->next ;
    p1->next = NULL ;

    while(p3 != NULL)
    {
        p2->next = p1 ;
        p1 = p2 ;
        p2 = p3 ;
        p3 = p3->next ;
    }

    p2->next = p1 ;
    head = p2 ;
    return head ;
}

/**
已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序。
(保留所有结点，即便大小相同）
*/
Node * Merge(Node *head1 , Node *head2)
{
    if(head1 == NULL)
        return head2 ;

    if(head2 == NULL)
        return head1 ;

    Node *head = NULL ;
    Node *p1 = NULL;
    Node *p2 = NULL;

    if(head1->data < head2->data)
    {
        head = head1 ;
        p1 = head1->next;
        p2 = head2 ;
    }
    else
    {
        head = head2 ;
        p2 = head2->next ;
        p1 = head1 ;
    }

    Node *pcurrent = head ;

    while(p1 != NULL && p2 != NULL)
    {
        if(p1->data <= p2->data)
        {
            pcurrent->next = p1 ;
            pcurrent = p1 ;
            p1 = p1->next ;
        }
        else
        {
            pcurrent->next = p2 ;
            pcurrent = p2 ;
            p2 = p2->next ;
        }
    }

    if(p1 != NULL)
        pcurrent->next = p1 ;

    if(p2 != NULL)
        pcurrent->next = p2 ;

    return head ;
}
/**
已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序，
这次要求用递归方法进行。 (Autodesk)
*/
Node * MergeRecursive(Node *head1 , Node *head2)
{
    if(head1 == NULL)
        return head2 ;

    if(head2 == NULL)
        return head1 ;

    Node *head = NULL ;

    if(head1->data < head2->data)
    {
        head = head1 ;
        head->next = MergeRecursive(head1->next,head2);
    }
    else
    {
        head = head2 ;
        head->next = MergeRecursive(head1,head2->next);
    }

    return head ;
}

