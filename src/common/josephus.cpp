#include <iostream>
#include <cstdlib>

#include "linear_list.h"
#include "static_list.h"

using namespace std;

/**
 * 约瑟夫问题（华为面试）
 * 输入游戏者人数、开始的序号数（从哪个人开始）和报数间隔
 */
int josephus()
{
    int num; //the numbers of the players
    int start; //from which player to start
    int interval; //count to which number to quit
    cout<<"输入游戏者人数、开始的序号数和报数间隔："<<endl;
    cin >> num >> start >> interval;

    if((num<1) || (start<1) || (start>num) || (interval<1) || (interval>num))
    {
        cerr << "Invalid Input" << endl;
        exit(1);
    }

    int player[num];

    for(int j=0; j<num; j++)
    {
        player[j] = j+1;
    }

    int k = 0;
    int i = start-2; //warning

    while(k<num)
    {
        for(int j=1; j<=interval;)
        {
            i = (i+1)%num;

            if(player[i] != 0)
            {
                j++;
            }
        }

        cout << "出列的人是：" << player[i] << endl;
        player[i] = 0;
        k++;
    }

    return 0;
}

int main2_12()
{
    linked_list<int> A,B,C;
    LinkNode<int> *current_a,*current_b,*current_c;
    LinkNode<int> *current;
    int temp = 1000;
    cout<<"Which number do you want to end with:"<<endl;
    cin>>temp;
    A.inputRear(temp);
    B.inputRear(temp);
    cout<<"Check your input"<<endl;
    A.output();
    B.output();
    current_a = A.getHead()->link;
    current_b = B.getHead()->link;
    current_c = C.getHead();

    while(current_a != NULL)
    {
        while(current_b != NULL)
        {
            if(current_a->data <= current_b->data)
            {
                current = new LinkNode<int>(current_a->data);

                if(current == NULL)
                {
                    cerr<<"存储分配错误"<<endl;
                }

                current_c->link = current;
                current_c = current;
                break;
            }
            else if(current_a->data > current_b->data)
            {
                current = new LinkNode<int>(current_b->data);

                if(current == NULL)
                {
                    cerr<<"存储分配错误"<<endl;
                }

                current_c->link = current;
                current_c = current;
                current_b = current_b->link;
            }
        }

        if(current_b == NULL)
        {
            current = new LinkNode<int>(current_a->data);
            current_c->link = current;
            current_c = current;
        }

        current_a = current_a->link;
    }

    while(current_b != NULL)
    {
        current = new LinkNode<int>(current_b->data);

        if(current == NULL)
        {
            cerr<<"存储分配错误"<<endl;
        }

        current_c->link = current;
        current_c = current;
        current_b = current_b->link;
    }

    cout<<"The output is:"<<endl;
    C.output();
    return 0;
}

/*
    author:jiangxin
    Blog:http://blog.csdn.net/jiangxinnju
    Function:method of Josephus question
*/

struct node
{
    int seq;
    node *next;
};
typedef struct node NODE;

int main0032()
{
    /*假设共有n人，从第s个人开始数数，每数到m该人出列，后面的人重新开始数，知道全部人出列*/
    int n,s,m;
    NODE *head = NULL,*last,*current,*prev;
    cout << "Input the n,s,m(separate with space):";
    cin >> n >> s >> m;

    for(int i=1; i<=n; i++) //建立循环链表
    {
        current = new NODE;
        current->seq = i;
        current->next = head;

        if(i == 1)
        {
            head = current;
            last = current;
        }
        else
        {
            last->next = current;
            last = last->next;
        }
    }

    current = head; //遍历循环链表，输出序列

    do
    {
        cout << current->seq << " ";
        current = current->next;
    }
    while(current!=head);

    current = head; //将current置于第s个位置

    for(int i=1; i<s; i++)
    {
        current = current->next;
    }

    cout << endl;

    for(int i=1; i<=n; i++) //共循环n轮，得到一个整体的输出序列
    {
        for(int j=1; j<m; j++)
        {
            prev = current;
            current = current->next;
        }

        cout << current->seq << " ";
        prev->next = current->next;
        delete current;
        current = prev->next;
    }

    return 0;
}



int main2_20()
{
    linked_list<int> A,odd,even;
    LinkNode<int> *current_a,*current_odd,*current_even;
    LinkNode<int> *current;
    int temp = 1000;
    cout<<"Which number do you want to end with:"<<endl;
    cin>>temp;
    A.inputRear(temp);
    cout<<"Check your input"<<endl;
    A.output();
    current_a = A.getHead()->link;
    current_odd = odd.getHead();
    current_even = even.getHead();

    while(current_a != NULL)
    {
        if(current_a->data%2 == 1)
        {
            current = new LinkNode<int>(current_a->data);
            current_odd->link = current;
            current_odd = current;
        }

        if(current_a->data%2 == 0)
        {
            current = new LinkNode<int>(current_a->data);
            current_even->link = current;
            current_even = current;
        }

        current_a = current_a->link;
    }

    cout<<"The Previous linkedlist is:"<<endl;
    A.output();
    cout<<"The odd linkedlist is:"<<endl;
    odd.output();
    cout<<"The even linkedlist is:"<<endl;
    even.output();
    return 0;
}
