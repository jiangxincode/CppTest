﻿#include "../utility.h"

/**
 * 函 数 名：rp2va(a,m,n,x,y)
 * 功能描述：求解二元多项式的值
 * 输入参数：a（多项式系数），m,n（分别为x项和y项的多项式阶次）
 *            (x,y（指定的点）)
 * 返 回 值：二元多项式在(x,y)处的值
 */
double rp2va(double *a,int m,int n,double x,double y)
{
    int i,j;
    double r1,r2;
    r1 = 0;   	 		/* 结果赋初值 */

    for(i=m-1; i>=0; i--)	/* 累次相加*/
    {
        r2 = a[i*n+n-1];

        for(j=n-2; j>=0; j--)
        {
            r2=r2*y + a[i*n+j];
        }

        r1 = r1*x + r2;
    }

    return(r1);
}

