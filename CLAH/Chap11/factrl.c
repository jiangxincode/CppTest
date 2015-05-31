﻿#include "../utility.h"

/**
 * 函 数 名：factrl
 * 功能描述：求解阶乘的值，本函数需要伽马函数的支持。
 * 输入参数：n 函数变量
 * 返 回 值：阶乘函数的值
 */
double factrl(int n)
{
    int i;
    double t;
    static int k=6;
    static float f[22] = {1.0,1.0,2.0,6.0,24.0,120.0,720.0};

    if(n<0)                             /* n小于零时，不能继续*/
    {
        printf("n<0\n");
        return(0.0);
    }

    if(n<22)                           /* 21!以下的数据可以用双精度数精确表示*/
    {
        /* 所以这里直接连乘即可*/
        while(k<n)
        {
            i=k++;                         /* 依次计算并存入f中，之后就不用再计算*/
            f[k] = f[i]*k;
        }

        return(f[n]);
    }

    t = gammln(n+1.0);                 /* 22!及以上的阶乘需要用伽马函数计算*/
    t = exp(t);
    return(t);
}
