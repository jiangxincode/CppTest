#include <stdio.h>
#include <stdlib.h>

#include "../utility.h"

/**
 * 函数名：c_comp_plus.c
 * 功能描述：求复数的加法
 * 输入参数：a1（第一个加数a的结构体）
 *            a2（第二个加数b的结构体）
 *            c（计算结果的结构体）
 * 返回值：0（失败），1（成功）
 */
int c_comp_plus(struct c_comp *a1,struct c_comp *a2,struct c_comp *c)
{
    if(a1 == NULL || a2 == NULL || c == NULL)
    {
        printf("(c_comp_plus)The c_comp pointer is NULL!\n");
        return(0);
    }

    c->rmz = a1->rmz + a2->rmz;
    c->imz = a1->imz + a2->imz;
    return(1);
}
