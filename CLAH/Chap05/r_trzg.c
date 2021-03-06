﻿#include "../utility.h"

/**
 * 函数名：r_trzg
 * 功能描述：用追赶法解线性方程组
 * 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
 *           n 未知数个数，eps 精度要求，小于eps的值，认为是0。
 * 返回值：整型。运行成功则返回1,失败则返回0
 */
int r_trzg(double *a,double *b,double *x,int n,double eps)
{
    int i,k,l;

    if((a==NULL)||(b==NULL)||(x==NULL))             /* 检测输入的指针是否为空*/
    {
        printf("The pointer is NULL\n");
        return 0;
    }

    for(k=0; k<n-1; k++)
    {
        l = k*n + k;

        if(fabs(a[l]) < eps)                          /* 判断主元是否过小*/
        {
            printf("failed.\n");                        /* 主元过小则求解失败*/
            return 0;                                  /* 若主元过小则退出程序*/
        }

        a[l+1] = a[l+1]/a[l];                         /* 归一化计算*/
        b[k] = b[k]/a[l];                             /* 常数向量的归一化计算*/
        a[l+n+1] -= a[l+n]*a[l+1];                    /* 消元计算*/
        b[k+1] -= a[l+n]*b[k];                        /* 常数向量也要进行消元计算*/
    }

    x[n-1] = b[n-1]/a[n*n-1];                       /* 第一个解可直接读出*/

    for(i=n-2; i>=0; i--)                          /* 继续进行回代，求出解向量*/
    {
        x[i] = b[i] - a[i*n+i+1]*x[i+1];
    }

    return 1;                                     /* 求解成功，返回1*/
}
