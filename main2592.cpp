/**
 * 쳲�����/쳲�����/Fibonacci/Fib
 * f(1)=1
 * f(2)=1
 * f(n)=f(n-1)+f(n-2) n>2
 */

#include <iostream>
#include <cerrno>
#include <cstring>

using namespace std;

/**
 * �ǵݹ����
 * �������㷵��ʵ�ʽ�������򷵻�-1
 * ͬʱ����errno��ֵ
 * ����С��0:EDOM
 * ������󣬵��½�����:ERANGE
 */
int fibonacci(int n)
{
    errno = 0; //���errno
    int result;
    int smaller = 0,bigger = 1;
    if(n < 0) //��������
    {
        errno = EDOM;
        return -1;
    }
    else if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    else
    {
        for(int i=2;i<=n;i++)
        {
            result = smaller+bigger;
            /**
             * ˵�����ϴ�result = smaller+bigger���������磬
             * resultһ����smaller��bigger��С
             */
            if(result < smaller)
            {
                errno = ERANGE;
                return -1;
            }
            smaller = bigger;
            bigger = result;

        }
    }

    return result;
}
/**
�ݹ��㷨
*/
int fibonacci_2(int n)
{
    if(n==1||n==2)
        return 1;
    else
        return fibonacci_2(n-1)+fibonacci_2(n-2);
}

int main2592()
{
    for(int i=-100;i<100;i++)
    {
        int result = fibonacci(i);
        cout << i << ": " << result << " " << ((result==-1)?strerror(errno):"") << endl;
    }

    return 0;
}
