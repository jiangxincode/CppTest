#include <stdio.h>
#include <math.h>
#include "something.h" /* 需要伽马函数的支持*/
#include "factrl.c"
int main11factrl0()
{
    int n;
    double x;
    printf("factorial(x): \n");
    for(n=18; n<25; n++)
    {
        x = factrl(n);                                /* 调用函数求解，并打印结果*/
        printf("n=%d, factorial(n)=%e\n",n,x);
    }
    getchar();
    return 0;
}
