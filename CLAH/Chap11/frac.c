﻿#include <math.h>

/**
 * 函 数 名：frac
 * 功能描述：求解连分式级数的值。
 * 输入参数：fa 计算第i个系数a和b的函数的指针
 *            nmax 递推计算的最多次数
 *            e1 精度要求，当两次递推的值变化率小于e1时，认为已收敛
 *            e0 极小的数值，接近浮点数能表示的最小数据。为避免除零，将除数设置的值。
 * 返 回 值：连分式级数的值
 */
double frac(double *fab(int, double*),int nmax,double e1,double e0)
{
    int j;
    double f,a,b,ab[2];
    double c,d,t;
    fab(0,ab);
    f = ab[1];                         /* 设置初值*/

    if(fabs(f) < e0)
    {
        f = e0;
    }

    c = f;
    d = 0.0;
    j = 1;

    do
    {
        fab(j,ab);                      /* 计算这一节的系数a和b*/
        a = ab[0];
        b = ab[1];
        d = b+a*d;                    /* 计算cj和dj*/
        c = b+a/c;

        if(fabs(d) < e0)               /* 若小于e0，则认为是0*/
        {
            d = e0;
        }

        if(fabs(c) < e0)
        {
            c = e0;
        }

        d = 1.0/d;                    /* 更新dj值*/
        t = c*d;
        f = f*t;                        /* 计算新的连分式值*/
        j++;
    }
    while((fabs(t-1.0)>e1)&&(j<nmax));  /* 循环终止条件*/

    return(f);
}
