﻿#include "../utility.h"

/**
 * 函数名：randgsab
 * 功能描述：生成N~(a,b)分布的随机数
 * 输入参数：a(正态分布的均值) b(正态分布的方差)
 * 返回值：正态分布的随机数
 */
double randgsab(double a,double b)
{
    double U1,U2,G;
    srand((unsigned)time(0));/*用系统时钟做种子*/
    U1=rand()/(double)RAND_MAX;/*生成(0,1)随机数U1*/
    U2=rand()/(double)RAND_MAX;/*生成(0,1)随机数U2*/
    G=sqrt(-2*log(U1))*sin(2*PI*U2);/*生成标准正态分布随机数G*/
    G=sqrt(b)*G+a;/*生成服从N~(a,b)的随机数G*/
    return(G);
}

