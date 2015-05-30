﻿/*======================================================
 * 函数名：sple
 * 功能描述：等距光滑插值
 * 输入参数：x 等距结点的第一个值, h 等距结点的距离
 *           y 指向存放n个结点的函数值的数组的指针
 *           n 结点个数
 *           t 指定的插值点,eps 绝对值小于此值的数据认为是0
 * 返回值：  在指定插值点的函数近似值
=========================================================*/
#include <stdio.h>
#include <math.h>

static double sple(x,h,y,n,t,eps)
double x,h,*y,t,eps;
int n;
{
    int k;
    double z,d[5],p[4],yy[2];
    double tmp1,tmp2;

    if((y==NULL))                    /* 检测输入指针是否为空*/
    {
        printf("Pointer is Null\n");
        return(0.0);
    }

    if(n<1)                                     /* 没有提供结点，返回0.0*/
    {
        return(0.0);
    }

    if(n==1)                                    /* 只有一个结点，返回此函数值*/
    {
        return(y[0]);
    }

    if(n==2)                                    /* 只有两个结点，使用线性插值*/
    {
        z = (y[0]*(t-x-h) - y[1]*(t-x))/h;
        return(z);
    }

    k = 0;

    while(((x+k*h)<t)&&(k<n))                      /* 寻找合适的区间*/
    {
        k++;
    }

    k = k-1;

    if(k < 1)
    {
        k = 0;
    }

    if(k==(n-1))
    {
        k = n-2;
    }

    d[2] = (y[k+1]-y[k]);                      /* 求得中间的养值*/

    if(k==0)                                    /* 判断范围并给出d1和d3值*/
    {
        d[3] = (y[k+2]-y[k+1]);
        d[1] = 2*d[2]-d[3];
    }
    else if(k==(n-2))
    {
        d[1] = (y[k]-y[k-1]);
        d[3] = 2*d[2]-d[1];
    }
    else
    {
        d[1] = (y[k]-y[k-1]);
        d[3] = (y[k+2]-y[k+1]);
    }

    if(k<=1)                                    /* 求出d0值*/
    {
        d[0] = 2*d[1]-d[2];
    }
    else
    {
        d[0] = (y[k-1]-y[k-2]);
    }

    if(k>=(n-3))                                /* 求出d4值*/
    {
        d[4] = 2*d[3]-d[2];
    }
    else
    {
        d[4] = (y[k+3]-y[k+2]);
    }

    tmp1 = fabs(d[3]-d[2]);                     /* 求出在第k和k+1两个结点处的导数*/
    tmp2 = fabs(d[0]-d[1]);

    if((tmp1 + tmp2)<eps)
    {
        yy[0] = (d[1]+d[2])/2.0;
    }
    else
    {
        yy[0] = (tmp1*d[1] + tmp2*d[2])/(tmp1 + tmp2);
    }

    tmp1 = fabs(d[3]-d[4]);
    tmp2 = fabs(d[2]-d[1]);

    if((tmp1+tmp2)<eps)
    {
        yy[1] = (d[2]+d[3])/2.0;
    }
    else
    {
        yy[1] = (tmp1*d[2] + tmp2*d[3])/(tmp1 + tmp2);
    }

    p[0] = y[k];                               /* 利用求得的导数构造多项式*/
    p[1] = yy[0]/h;
    p[2] = (3.0*d[2] - 2.0*yy[0] - yy[1])/(h*h);
    p[3] = (yy[0]+yy[1]-2.0*d[2])/(h*h*h);
    tmp1 = t-x-k*h;
    z = p[0] + ((p[3]*tmp1+p[2])*tmp1+p[1])*tmp1;  /* 按照多项式求得近似值*/
    return(z);
}
