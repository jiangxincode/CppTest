/**
斐波拉契
斐波那契
Fibonacci
f(1)=1
f(2)=1
f(n)=f(n-1)+f(n-2) n>2
*/

/**
非递归计算
*/
int fibonacci_1(int n)
{
    int i,s,s1,s2;
    s1=1;/*s1用于保存f(n-1)的值*/
    s2=1;/*s2用于保存f(n-2)的值*/
    s=1;

    for(i=3; i<=n; i++)
    {
        s=s1+s2;
        s2=s1;
        s1=s;
    }

    return(s);
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
