﻿#include "../utility.h"

/**
 * 函 数 名：rpmul(a,n,b,m,c)
 * 功能描述：完成系数表示的实系数的多项式A与B相乘，结果系数放在c里
 * 输入参数：a（多项式A系数），n（系数个数）
 *           b（多项式B系数），m（系数个数）
 *            c（返回的多项式C的系数）
 * 返 回 值：整型数字。计算成功则返回1，否则返回0
 */
int rpmul(double *a,int n,double *b,int m,double *c)
{
    int i,j,k;

    if((a==NULL) || (b==NULL) || (c==NULL))
    {
        printf("rpmul)NULL pointer found.\n");
        return 0;
    }

    k = m+n-1;	 	/* 相乘后的系数个数*/

    for(i=0; i<k; i++)    /* 先将系数向量置为0*/
    {
        c[i] = 0.0;
    }

    for(i=0; i<n; i++)    /* 依次将相乘的结果累加到对应的项上*/
        for(j=0; j<m; j++)
        {
            c[i+j] += a[i]*b[j];
        }

    return 1;
}
