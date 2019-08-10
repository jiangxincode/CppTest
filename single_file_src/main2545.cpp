/*
写出计算Ackermann函数ack(m,n)值的递归函数并用它计算ack(2,2)的值。ack(m,n)定义如下(m≥0,n≥0)：
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
int main()
{
    cout << ack(2,2);
    return 0;
}
