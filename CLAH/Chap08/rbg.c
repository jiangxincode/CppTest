﻿#include "../utility.h"

/**
 * 函数名：rbg
 * 功能描述：龙贝格积分法求积分
 * 输入参数：a 积分下限，b 积分上限,
 *           n0 初始划分数
 *           eps 精度要求
 *           h0 最小步长
 *           f 指向被积函数的指针
 * 返回值：  积分近似值
 */
double rbg(double a,double b,int n0,double eps,double(*f)(double))
{
    int n,k,m;
    double r[10],z,q,h,d,x,t;
    m = 1;
    n = n0;                            /* 初始的划分数*/
    h = (b-a)/n;                       /* 求得初始步长*/
    z = ((*f)(a)+(*f)(b))/2.0;         /* 计算初始的积分值*/

    for(k=1; k<n; k++)
    {
        x = a+k*h;
        z = z+(*f)(x);                   /* 累次求和*/
    }

    r[0] = z*h;                        /* 尽量减少乘法次数*/

    do
    {
        z = 0.0;

        for(k=0; k<n; k++)               /* 梯形求积公式*/
        {
            x = a+(k+0.5)*h;
            z = z+(*f)(x);
        }

        z = (r[0]+h*z)/2.0;              /* 计算新的积分值*/
        t = 1.0;

        for(k=1; k<m+1; k++)             /* 龙贝格公式递推计算*/
        {
            t = 4.0*t;
            q = (t*z-r[k-1])/(t-1.0);
            r[k-1] = z;
            z = q;
        }

        d = fabs(q-r[m-1]);              /* 计算两次积分值的差*/
        r[m] = q;                        /* 更新龙贝格公式递推值*/
        m = m+1;
        h = h/2.0;                       /* 更新步长*/
        n = 2*n;                         /* 更新划分数*/
    }
    while((d>eps)&&(m<10));

    return(q);
}
