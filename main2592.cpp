/**
 * 斐波拉契/斐波那契/Fibonacci/Fib
 * f(1)=1
 * f(2)=1
 * f(n)=f(n-1)+f(n-2) n>2
 */

#include <iostream>
#include <cerrno>
#include <cstring>

using namespace std;

/**
 * 非递归计算
 * 正常计算返回实际结果，否则返回-1
 * 同时设置errno的值
 * 输入小于0:EDOM
 * 输入过大，导致结果溢出:ERANGE
 */
int fibonacci(int n)
{
    errno = 0; //清楚errno
    int result;
    int smaller = 0,bigger = 1;
    if(n < 0) //错误输入
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
             * 说明在上次result = smaller+bigger发生了上溢，
             * result一定比smaller和bigger都小
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
递归算法
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
