/*
    author:
        jiangxin
    Blog:
        http://blog.csdn.net/jiangxinnju
    function:
    ����������reverse����ABCD���DCBA��ֻ����������һ��
*/
#include <iostream>

using namespace std;
struct node
{
    char data;
    struct node *next;
};
typedef struct node NODE;
int main0510()
{
    NODE *head = new NODE; //��������ͷ���
    head->next = NULL;

    /*��������*/
    NODE *current,*previous;
    previous = head;
    char input;
    cout << "Input your list table NODE data,end with '#':";
    cin >> input;
    while(input != '#')
    {
        current = new NODE;
        current->data = input;
        current->next = NULL;
        previous->next = current;
        previous = previous->next;
        cout << "Input your list table NODE data,end with '#':";
        cin >> input;
    }

    /*�������*/
    current = head->next;
    while(current != NULL)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    /*��ת����*/
    current = head->next;
    NODE *p = current->next;
    NODE *q = p->next;
    while(q != NULL)
    {
        p->next = current;
        current = p;
        p = q;
        q = q->next;
    }
    p->next = current;
    current = p;
    head->next->next = NULL;
    head->next = current;

    /*�������*/
    current = head->next;
    while(current != NULL)
    {
        cout << current->data << " ";
        current = current->next;
    }
    return 0;
}

