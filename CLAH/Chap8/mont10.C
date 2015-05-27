#include <stdio.h>
#include <math.h>

#include "tzi1.c"
#include "something.h"

static double f1(double);
int main8mont10()
{
    double a,b,eps,h0,z;

    a = 0.0;
    b = 4.0;
    eps = 1e-8;
    h0 = 1e-5;
    z = tzi1(a,b,4,eps,h0,f1);                  /* 用变步长梯形求积法积分*/
    printf("tzi1: t=%2.5f\n",z);                /* 打印结果*/
    z = mont1(a,b,f1);                          /* 用蒙特卡洛法积分*/
    printf("mont1: t=%2.5f\n",z);
    getchar();
}

static double f1(double x)                                    /* 被积分的函数*/
{
    double y;
    y=exp(-x*x)/(1.0+x*x);
    return(y);
}
