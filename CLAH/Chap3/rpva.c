﻿/**
 * 函 数 名：rpva(a,n,x0)
 * 功能描述：求解一元多项式的值
 * 输入参数：a（多项式系数），n（系数个数）、0（指定的点）
 * 返 回 值：一元多项式在x0处的值
 */
double rpva(double *a,int n,double x0)
{
    int i;
    double r;
    r=a[n-1];    	     /* 初值是最高次项的系数*/

    for(i=n-2; i>=0; i--)    /* 从高次向低次循环完成运算*/
    {
        r=r*x0+a[i];
    }

    return(r);
}
