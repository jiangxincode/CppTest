#include <stdio.h>
#include "something.h" /* QR分解的函数*/
#include "gmqr.c"
int main5gmqr0()
{
    int i;
    double x[4],a[5][4]= {{1.0,2.0,4.0,1.5},         /* 矩阵A赋值*/
        {-1.0,0.0,3.0,1.7},
        {2.0,-1.0,0.0,2.5},
        {3.0,1.0,2.0,3.5},
        {4.0,2.0,1.5,4.5}
    };
    double b[5] = {3.0,1.5,-2.5,2.0,1.0};            /* 常数向量赋值*/
    i=gmqr(a,b,x,5,4,1e-16);                     /* 调用函数求解*/

    if(i!=0)                                     /* 打印结果*/
    {
        for(i=0; i<4; i++)
        {
            printf("x(%d) = %5.2f\n",i,x[i]);
        }
    }

    return 0;
}
