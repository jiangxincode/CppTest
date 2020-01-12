﻿#include "../utility.h"

/**
 * 函数名：orelax
 * 功能描述：用超松驰方法解对称方程组
 * 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
 *           n 未知数个数，w 超松驰因子
 *           eps 精度要求，iter 允许的最多迭代次数
 * 返回值：整型。运行成功则返回迭代次数,失败则返回0
 */
int orelax(double *a,double *b,double *x,int n,double w,double eps,int iter)
{
    int i,j,piter=0;
    double fr = 1.0,t,*x2;

    if((a==NULL)||(b==NULL)||(x==NULL))            /* 检测输入的指针是否为空*/
    {
        printf("The pointer is NULL\n");
        return 0;
    }

    x2 = (double *)malloc(n*sizeof(double));       /* 分配空间并检测是否成功*/

    if(x2==NULL)
    {
        printf("Memory alloc failed\n");
        return 0;
    }

    for(i=0; i<n; i++)
        if(fabs(a[i*n+i]) < 1e-12)               /* 因为要做除数，需要检查是否过小*/
        {
            printf("A[%d,%d] is too small,cannot converged",i,i);
            return 0;
        }

    for(i=0; i<n; i++)                        /* 对解向量赋初值*/
    {
        x[i] = 0.0;
    }

    while((fr>eps) && (piter<iter))
    {
        fr = 0.0;

        for(i=0; i<n; i++)
        {
            t = 0.0;

            for(j=0; j<i; j++)
            {
                t = t+a[i*n+j]*x2[j];    /* 立即使用刚求出的新x*/
            }

            for(j=i+1; j<n; j++)
            {
                t = t+a[i*n+j]*x[j];
            }

            x2[i] = (b[i] - t)/a[i*n+i];            /* 更新的x值*/
            x2[i] = (1.0-w)*x[i] + w*x2[i];         /* 使用超松驰因子*/
            t = fabs(x2[i]-x[i])/(1.0+fabs(x[i]));  /* 更新误差*/

            if(t > fr)
            {
                fr = t;
            }
        }

        for(i=0; i<n; i++)
        {
            x[i] = x2[i];
        }

        piter++;                               /* 迭代次数增加1*/
    }

    return(piter);
}
