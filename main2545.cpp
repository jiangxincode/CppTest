/*
д������Ackermann����ack(m,n)ֵ�ĵݹ麯������������ack(2,2)��ֵ��ack(m,n)��������(m��0,n��0)��
ack(0,n) = n+1
ack(m,0) = Ack(m-1,1)
ack(m,n) = ack(m-1,ack(m,n-1))   (m>0, n>0)
*/
#include <iostream>
using namespace std;
int ack(int m,int n)
{
    if(m==0)
    {
        return n+1;
    }
    else if(n==0)
    {
        return ack(m-1,1);
    }
    else
    {
        return ack(m-1,ack(m,n-1));
    }
}
int main2545()
{
    cout << ack(2,2);
}
