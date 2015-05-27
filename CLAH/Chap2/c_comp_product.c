#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * 函数名：c_comp_product.c
 * 功能描述：求复数的乘法
 * 输入参数：a1（第一个乘数a的结构体）
 *            a2（第二个乘数b的结构体）
 *            c（计算结果的结构体）
 * 返回值：0（失败），1（成功）
 */
int c_comp_product(struct c_comp *a1,struct c_comp *a2,struct c_comp *c)
{
    if(a1 == NULL || a2 == NULL || c == NULL)
    {
        printf("(c_comp_product)The c_comp pointer is NULL!\n");
        return(0);
    }
    double p = (a1->rmz)*(a2->rmz);
    double q = (a1->imz)*(a2->imz);
    double s = (a1->rmz + a1->imz)*(a2->rmz + a2->imz);
    c->rmz = p - q;
    c->imz = s - p - q;
    return(1);
}
