/*=============================================================
// 函 数 名：bsl1
// 功能描述：求解第一类整数阶贝塞尔函数的值
// 输入参数：x 自变量x的值。
//           n 贝塞尔函数的阶数
// 返 回 值：第一类整数阶贝塞尔函数的值
//==============================================================*/
#include "math.h"
#include "stdio.h"
#define ENUMB 30.0                      /* 逆向递推时计算递推起点的数据，越大结果的有效数字越多*/
#include "something.h"


double bsl1(int n,double x)
{
    double t;
    int j,nn,flag;
    double ax,nx,bj0,bj1,bj,bjs;
    ax = fabs(x);
    if(ax==0.0)
        return(0.0);
    nx = 2.0/ax;                          /* 计算2*n/x需要的值2/x*/
    if(ax>(double)n)                      /* 正向递推*/
    {
        bj0 = J0(ax);                       /* 递推初值J0*/
        bj1 = J1(ax);                       /* 递推初值J1*/
        for(j=1; j<n; j++)
        {
            bj = j*nx*bj1-bj0;                /* 递推计算*/
            bj0 = bj1;
            bj1 = bj;
        }
        if(n==0)
            t = bj0;
        else
            t = bj1;
    }
    else
    {
        nn = 2*((int)(n+sqrt(ENUMB*n))/2);   /* 保证是偶数*/
        bjs = 0.0;                           /* 偶数项相加的和，用于归一化*/
        flag = 0;                            /* 只对偶数项进行相加*/
        bj1 = 0.0;                           /* 第nn+1项设为0*/
        bj0 = 1.0;                           /* 第nn项设为1.0*/
        for(j=nn; j>0; j--)
        {
            bj = j*nx*bj0-bj1;                 /* 递推计算*/
            bj1 = bj0;
            bj0 = bj;
            if(flag)                           /* 偶数项进行累加*/
                bjs = bjs+bj;
            flag = !flag;
            if(j==n)
                t = bj1;
            if(fabs(bj)>1.0e10)                /* 在递推过程中进行归一化，防止溢出*/
            {
                bj0 = bj0*1.0e-10;
                bj1 = bj1*1.0e-10;
                bjs = bjs*1.0e-10;
                t = t*1.0e-10;
            }
        }
        bjs = 2.0*bjs-bj;
        t = t/bjs;
    }
    return (x<0.0)&&(n&1)?-t:t;            /* n为奇数且x为负时，返回-t*/
}

double J0(double x)                     /* 计算J0(x)*/
{
    double x1,x2,t,t1,t2,y;
    x1 = fabs(x);
    if(x1 < 8.0)                           /* 有理分式逼近*/
    {
        x2 = x*x;
        t1 = 57568490574.0+x2*(-13362590354.0+
                               x2*(651629640.7+x2*(-11214424.18+
                                       x2*(77392.33017+x2*(-184.9052456)))));
        t2 = 57568490411.0+x2*(1029532985.0+
                               x2*(9494680.718+x2*(59272.64853+
                                       x2*(267.8532712+x2))));
        t = t1/t2;
    }
    else                                  /* x>8的情况*/
    {
        y = 8.0/x1;
        x2 = y*y;
        t1 = 1.0+x2*(-0.1098628627e-2+x2*(0.2734510407e-4+
                                          x2*(-0.2073370639e-5+x2*0.2093887211e-6)));
        t2 = -0.1562499995e-1+x2*(0.1430488765e-3+
                                  x2*(-0.6911147651e-5+x2*(0.7621095161e-6-
                                          x2*0.934945152e-7)));
        t = x1-0.785398164;
        t = sqrt(0.0795774715*y)*(cos(t)*t1-y*sin(t)*t2);
    }
    return t;
}

double J1(double x)                  /* 计算J1(x)*/
{
    double x1,x2,t,t1,t2,y;
    x1 = fabs(x);
    if(x1 < 8.0)                           /* 有理分式逼近*/
    {
        x2 = x*x;
        t1 = x*(72362614232.0+x2*(-7895059235.0+
                                  x2*(242396853.1+x2*(-2972611.439+
                                          x2*(15704.48260+x2*(-30.16036606))))));
        t2 = 144725228442.0+x2*(2300535178.0+
                                x2*(18583304.74+x2*(99447.43394+
                                        x2*(376.9991397+x2))));
        t = t1/t2;
    }
    else                                  /* x>8的情况*/
    {
        y = 8.0/x1;
        x2 = y*y;
        t1 = 1.0+x2*(0.183105e-2+x2*(-0.3516396496e-4+
                                     x2*(0.2457520174e-5+x2*(-0.240337019e-6))));
        t2 = 0.04687499995+x2*(-0.2002690873e-3+
                               x2*(0.8449199096e-5+x2*(-0.88228987e-6+
                                       x2*0.105787412e-6)));
        t = x1-2.356194491;
        t = sqrt(0.0795774715*y)*(cos(t)*t1-y*sin(t)*t2);
        t = (x<0.0)?-t:t;
    }
    return t;
}
