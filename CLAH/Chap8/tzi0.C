﻿
#include "../utility.h"

static double f1(double);

int main8tzi0()
{
    double a,b,eps,h0,z;
    a = 0.0;
    b = 4.0;
    eps = 1e-8;
    h0 = 1e-5;
    z=tzi1(a,b,4,eps,h0,f1);                     /* 用变步长梯形求积法积分*/
    printf("tzi1: t=%2.5f\n",z);                 /* 打印结果*/
    z=tzi2(a,b,4,eps,h0,f1);                     /* 用自适应梯形求积法积分*/
    printf("tzi2: t=%2.5f\n",z);
    z=simps1(a,b,4,eps,h0,f1);                   /* 用变步长辛卜生求积法积分*/
    printf("simp: t=%2.5f\n",z);
    z=rbg(a,b,4,eps,f1);                         /* 用龙贝格积分法积分*/
    printf("robg: t=%2.5f\n",z);
    getchar();
    return 0;
}

static double f1(double x)                                      /* 被积分的函数*/
{
    double y;
    y=exp(-x*x)/(1.0+x*x);
    return(y);
}
