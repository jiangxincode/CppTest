/*
ĳ�Ա��̼Ҹ��ݿͻ����򱦱�����n������ͬ���ۿ���discnt���ݷ�f�Żݲ��ԡ�
���������ۿ������ݷѼ������Ƭ�ε����ӣ�����Ľ��������������Ľ�����
*/
#include <iostream>
#include <cstdio>
using namespace std;
int main2527()
{
    int f = 10, n = 0;
    double discnt = 0;
    double d_prince = 0.0;
    scanf("%d", &n);
    if(n <= 0)
    {
        printf("Error!");
    }
    else
    {
        if(n <= 9)
            ;
        else if(n <= 19)
            discnt = 0.05;
        else if(n <= 29)
            discnt = 0.1;
        else if(n <= 49)
            discnt = 0.2;
        else if(n > 49)
        {
            discnt = 0.2;
            f = 0;
        }
    }
}
