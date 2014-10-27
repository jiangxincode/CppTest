#include <iostream>
#include <cstdlib>

#include "linked_list.h"
#include "seq_list.h"
#include "static_list.h"

using namespace std;


/**
 * 约瑟夫问题（华为面试）
 * 输入游戏者人数、开始的序号数（从哪个人开始）和报数间隔
 */
int main0031()
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
                j++;
        }

        cout << "出列的人是：" << player[i] << endl;
        player[i] = 0;
        k++;
    }

    return 0;
}

int main2_12()
{
    List<int> A,B,C;
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

int main2_20()
{
    List<int> A,odd,even;
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

    printf("\033[31mThe Previous linkedlist is:\n\033[0m");
    //cout<<"The Previous linkedlist is:"<<endl;
    A.output();
    printf("\033[31mThe odd linkedlist is:\n\033[0m");
    //cout<<"The odd linkedlist is:"<<endl;
    odd.output();
    printf("\033[31mThe even linkedlist is:\n\033[0m");
    //cout<<"The even linkedlist is:"<<endl;
    even.output();
    return 0;
}
int main003()
{
    main0031();
    return 0;
}
