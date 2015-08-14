﻿#include "../utility.h"

/**
 * 函数名：cheb
 * 功能描述：切比雪夫求积法进行积分
 * 输入参数：a 积分下限，b 积分上限,
 *           n0 初始划分数
 *           eps 精度要求
 *           h0 最小步长
 *           f 指向被积函数的指针
 * 返回值：  积分近似值
 */
double cheb(double a,double b,int n0,double eps,double h0,double(*f)())
{
    int n,i,j;
    double z,z2,h,d,x;
    static double t[5] = {-0.951056516295154, -0.587785252292473,0.0,
                          0.587785252292473, 0.951056516295154
                         }; /* 5阶切比雪夫多项式的零点*/
    n = n0;                            /* 初始的划分数*/
    h = (b-a)/n;                       /* 求得初始步长*/
    z = 0.0;                            /* 计算初始的积分值*/

    for(i=0; i<n; i++)
    {
        x = a+i*h+h/2.0;

        for(j=0; j<5; j++)
        {
            z = z+(*f)(h/2.0*t[j]+x);
        }
    }

    z = z*h/5.0;                        /* 尽量减少乘法次数*/

    do
    {
        n = 2*n;                           /* 更新划分数*/
        h = h/2.0;                          /* 更新步长*/
        z2 = 0.0;                         /* 计算新的积分值*/

        for(i=0; i<n; i++)
        {
            x = a+i*h+h/2.0;

            for(j=0; j<5; j++)
            {
                z2 = z2+(*f)(h/2.0*t[j]+x);
            }
        }

        z2 = z2*h/5.0;                   /* 尽量减少乘法次数*/
        d = fabs(z2-z);                  /* 计算两次积分值的差*/
        z = z2;                          /* 更新积分值*/
    }
    while((d>eps)&&(h>h0));

    return(z);
}