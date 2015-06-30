﻿#include <stdio.h>
#include <math.h>
/*======================================================
 * 函数名：lfsi
 * 功能描述：连分式求积分
 * 输入参数：a 积分下限，b 积分上限,
 *           n0 初始划分数
 *           eps 精度要求
 *           f 指向被积函数的指针
 * 返回值：  积分近似值
=========================================================*/
double lfsi(double a,double b,int n0,double eps,double(*f)(double))
{
    int k,j,p,n,flag;
    double z,z2,u,t,d,h,x,bb[8],hx[8];
    n = n0;                            /* 初始的划分数*/
    h = (b-a)/n;                       /* 求得初始步长*/
    z = ((*f)(a)+(*f)(b))/2.0;         /* 计算初始的积分值*/

    for(k=1; k<n; k++)
    {
        x = a+k*h;
        z = z+(*f)(x);                   /* 累次求和*/
    }

    z = z*h;
    bb[0] = z;                         /* 初始积分值*/
    u = z;                             /* u用于存放连分式计算的结果*/
    p = 1;
    hx[0] = h;

    do
    {
        t = 0.0;

        for(k=0; k<n; k++)
        {
            x = a+(k+0.5)*h;
            t = t+(*f)(x);
        }

        z2 = (z+h*t)/2.0;                /* 计算新的积分值*/
        z = z2;                          /* 更新积分值*/
        h = h/2.0;                       /* 更新步长*/
        n = 2*n;                         /* 更新划分数*/
        flag = 0;

        for(j=0; j<p; j++)               /* 计算新的连分式节点b[p]*/
        {
            if(fabs(z2-bb[j])<eps)         /* 要做除数，因此需要检查范围*/
            {
                flag = 1;
                j = p;                       /* 若除数为0,则连分式到此为止*/
            }
            else
            {
                z2=(h-hx[j])/(z2-bb[j]);
            }
        }

        hx[p] = h;                       /* 记录步长，做为连分式插值的结点*/

        if(flag == 1)
        {
            bb[p] = 1.0e35;    /* 这个数据用来终止连分式*/
        }
        else
        {
            bb[p] = z2;
        }

        z2 = bb[p];                        /* 计算在h=0处的近似值*/

        for(j=p-1; j>=0; j--)
        {
            z2 = bb[j]-hx[j]/z2;
        }

        d = fabs(z2-u);
        u = z2;
        p = p+1;
    }
    while((d>eps) && (p<8) &&(flag==0));

    return(u);
}
