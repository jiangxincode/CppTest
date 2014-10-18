/*
    author:jiangxin
    Blog:http://blog.csdn.net/jiangxinnju
    Function:method of Josephus question
*/
#include <iostream>

using namespace std;

struct node
{
    int seq;
    node *next;
};
typedef struct node NODE;

int main0509()
{
    /*���蹲��n�ˣ��ӵ�s���˿�ʼ������ÿ����m���˳��У�����������¿�ʼ����֪��ȫ���˳���*/
    int n,s,m;
    NODE *head,*last,*current,*prev;
    cout << "Input the n,s,m(separate with space):";
    cin >> n >> s >> m;

    for(int i=1; i<=n; i++) //����ѭ������
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

    current = head; //����ѭ�������������

    do
    {
        cout << current->seq << " ";
        current = current->next;
    }
    while(current!=head);

    current = head; //��current���ڵ�s��λ��

    for(int i=1; i<s; i++)
    {
        current = current->next;
    }

    cout << endl;

    for(int i=1; i<=n; i++) //��ѭ��n�֣��õ�һ��������������
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
