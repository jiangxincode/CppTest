﻿#include <math.h>
#include <stdio.h>

/**
 * 函 数 名：gammln
 * 功能描述：求解伽马函数的值的自然对数
 * 输入参数：x 求值的自变量
 * 返 回 值：伽马函数的值的自然对数
 */
double gammln(double x)
{
    int i;
    double t,s;
    static double c[6] = {76.18009172947148,
                          -86.50532032941677,24.01409824083091,
                          -1.231739572450155,0.1208650973866179e-2,
                          -0.5395239384953e-5
                         };          /* 系数*/

    if(x<0)
    {
        printf("incorrect input parameter\n");
        return(0.0);
    }

    s = 1.000000000190015;

    for(i=0; i<6; i++)                       /* 级数和*/
    {
        s = s+c[i]/(x+i);
    }

    t = x+4.5;                               /* 已取对数*/
    t = t-(x-0.5)*log(t);
    t = log(2.5066282746310005*s)-t;         /* 最后结果*/
    return(t);
}
