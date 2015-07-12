﻿#include "../utility.h"

static   double f(double,double);
static  void  fy(double,double []);
int main8simps20()
{
    double a,b,eps,s,h0;
    a = 0.0;
    b = 4.0;
    eps = 0.0001;
    h0 = 1e-6;
    s = simps2(a,b,10,eps,h0,f,fy);        /* 调用函数进行积分*/
    printf("simps2: s=%2.5f\n",s);         /* 打印积分结果*/
    getchar();
    return 0;
}
static double f(x,y)                            /* 被积分的函数*/
double x,y;
{
    double z;
    z = exp(-x*y)/(1.0+x*y);
    return(z);
}
static void fy(x,y)                             /* 求积分界的函数*/
double x,y[2];
{
    y[0] = 0;
    y[1] = x;
    return;
}
