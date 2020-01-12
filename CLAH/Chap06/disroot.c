﻿#include "../utility.h"

/**
 * 函数名：disroot
 * 功能描述：求出[a,b]区间内的非线性方程f(x)的一个实根
 *  * 返回值 * 返回值左端点）
 *          b（根所在区间的右端点）
 *          f（非线性方程左端函数）
 *          eps（精度要求）
//返回值：方程的实根
 */
double disroot(double a,double b,double (*f)(),double eps)
{
    double x,ym;                   /* 定义区间中点及中点处的函数值*/
    double ya=(*f)(a);             /* 区间左端点的函数值*/
    double yb=(*f)(b);             /* 区间右端点的函数值*/

    while(b-a>eps)                 /* 测试是否满足精度要求，不满足则继续对分*/
    {
        x=(a+b)/2;
        printf("%1.7f    %1.7f    %1.7f\n",a,x,b);
        ym=(*f)(x);                /* 求区间中点及中点处的函数值*/

        if(ym==0)                  /* 为0时结束*/
        {
            return(x);
        }

        if(ya*ym<0.0)              /* 中点代替左端点b，中点函数值作为左端点函数值*/
        {
            b=x;
            yb=ym;
        }
        else
        {
            a=x;
            ya=ym;             /* 中点代替右端点a，中点函数值作为右端点函数值*/
        }
    }

    return((a+b)/2);  /*结束后返回区间中点*/
}
