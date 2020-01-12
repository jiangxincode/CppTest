﻿#include "../utility.h"

/**
 * 函数名：c_comp_divide.c
 * 功能描述：求复数的除法
 * 输入参数：a1（被除数a的结构体）
 *            a2（除数b的结构体）
 *            c（计算结果的结构体）
 * 返回值：0（失败），1（成功）
 */
int c_comp_divide(const struct c_comp *a1,const struct c_comp *a2,struct c_comp *c)
{
    if(a1 == NULL || a2 == NULL || c == NULL)
    {
        printf("(c_comp_divide)The c_comp pointer is NULL!\n");
        return 0;
    }

    double R2 = (a2->rmz)*(a2->rmz) + (a2->imz)*(a2->imz);
    c_comp_product(a1,a2,c);
    c->rmz = c->rmz/R2;
    c->imz = c->imz/R2;
    return 1;
}
