/*
华为面试题
写出下列代码的输出内容
*/
#include <stdio.h>

int inc(int a)
{
    return (++a); //如果是return (a++)则直接返回a+1之前的值
}

int multi(int *a, int *b, int *c)
{
    return (*c = *a**b);
}

typedef int (FUN1)(int);
typedef int (FUN2)(int*, int*, int*);

void show(FUN1 p, FUN2 fun, int arg1, int *arg2)
{
    int temp = p(arg1);
    fun(&temp, &arg1, arg2);
    printf("%d\n", *arg2);
}

int main0012()
{
    int a;
    show(inc, multi, 10, &a);
    return 0;
}
