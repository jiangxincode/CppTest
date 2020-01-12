﻿#include "../utility.h"

#define EPS 1.0e-6                    /* 使用不完全贝塔函数需要的数据*/

/**
 * 函 数 名：studf
 * 功能描述：求解学生分布函数的值
 * 输入参数：x 自变量x的值。
 *           n 自变量n的值
 * 返 回 值：学生分布函数的值
 */
double studf(double x,int n)
{
    double t;
    t = 1.0-beta2(n/2.0,0.5,n/(n+x*x),EPS);
    return(t);
}
