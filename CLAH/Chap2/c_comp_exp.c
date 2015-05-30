#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../utility.h"

/**
 * 函数名：c_comp_pow.c
 * 功能描述：求复数指数
 * 输入参数：a（输入的结构体）
 *            c（计算结果的结构体）
 * 返回值：0（失败），1（成功）
 */
int c_comp_exp(struct c_comp *a,struct c_comp *c)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_exp)The c_comp pointer is NULL!\n");
        return(0);
    }

    double R = exp(a->rmz);
    c->rmz = R*cos(a->imz);
    c->imz = R*sin(a->imz);
    return(1);
}
