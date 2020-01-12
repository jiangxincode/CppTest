﻿#include "../utility.h"

/**
 * 函 数 名：RC
 * 功能描述：求解第一类椭圆积分的退化形式的值
 * 输入参数：x 求值的自变量
 *           y 求值的自变量
 * 返 回 值：第一类椭圆积分的退化形式的值
 */
double RC(double x,double y)
{
    double ll,t,t1,f,eps;
    double z = 0.0; //add by jiangxin
    eps = 1.0e-30;

    if(x<0||(x+fabs(y))<eps)                                  /* 检查自变量范围*/
    {
        printf("Parameters incorrect\n");
        return(0.0);
    }

    f = 1.0;

    if(y<0.0)
    {
        f = sqrt(x)/sqrt(x-y);
        x = x-y;
        y = -y;
    }

    do
    {
        ll = 2.0*sqrt(x)*sqrt(y)+y;
        x = (x+ll)/4.0;                                        /* 更新x,y*/
        y = (y+ll)/4.0;
        t = (x+y+z)/3.0;
        t1 = 1.0-y/t;
    }
    while(fabs(t1) > 0.0012);                                  /* 这个阈值用于判断x和y充分接近*/

    t = (1.0+t1*t1*(0.3+t1*(1.0/7.0+t1*(0.375+9.0*t1/22.0))))/sqrt(t);     /* 用泰勒展开计算积分值*/
    t = f*t;                                                    /* 乘上系数*/
    return(t);
}
