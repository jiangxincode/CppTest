#include "../utility.h"

/* 使用不完全贝塔函数需要的数据*/

/**
 * 函 数 名：cbdf
 * 功能描述：求解累积二项式分布函数的值
 * 输入参数：x 自变量x的值。
 *           n 自变量n的值
 * 返 回 值：累积二项式分布函数的值
 */
double cbdf(double p,int n,int k)
{
    double t;
    t = beta2((double)k,n+1.0-k,p,EPS);
    return(t);
}
