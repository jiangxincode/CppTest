﻿#include "../utility.h"

/**
 * 函数名：lagr1
 * 功能描述：拉格朗日线性插值
 * 输入参数：x 指向存放n个结点的数据的数组的指针
 *           y 指向存放n个结点的函数值的数组的指针
 *           n 结点个数。
 *           t 指定的插值点
 * 返回值：  在指定插值点的函数近似值
 */
double lagr1(double *x,double *y,int n,double t)
{
    int i,j,k;
    double z;

    if((x==NULL)||(y==NULL))             /* 检测输入指针是否为空*/
    {
        printf("Pointer is Null\n");
        return(0.0);
    }

    if(n<1)                              /* 没有提供结点，返回0.0*/
    {
        return(0.0);
    }

    if(n==1)                             /* 只有一个结点，返回此函数值*/
    {
        return(y[0]);
    }

    i = 0;

    while((x[i]<t)&&(i<n))               /* 寻找合适的区间*/
    {
        i++;
    }

    i = i-1;

    if(i < 1)
    {
        i = 0;
    }

    if(i > (n-2))
    {
        i = n-2;
    }

    printf("lagr1: %d,%d\n",i,i+1);      /* 打印使用的区间*/
    z = (y[i]*(t-x[i+1]) - y[i+1]*(t-x[i]))/(x[i] - x[i+1]); /* 计算近似值*/
    return(z);
}
