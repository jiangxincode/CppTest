﻿#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../utility.h"

/**
 * 函数名：c_comp_sin.c
 * 功能描述：求复数的正弦
 * 输入参数：a（输入的结构体）
 *            c（计算结果的结构体）
 * 返回值：0（失败），1（成功）
 */
int c_comp_sin(struct c_comp *a,struct c_comp *c)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_sin)The c_comp pointer is NULL!\n");
        return(0);
    }

    double tmp1 = exp(a->imz);
    double tmp2 = exp(-a->imz);
    c->rmz = sin(a->rmz)*(tmp1+tmp2)/2;
    c->imz = cos(a->rmz)*(tmp1-tmp2)/2;
    return(1);
}
