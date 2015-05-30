#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../utility.h"

/**
 * 函数名：c_comp_nthroot.c
 * 功能描述：求复数的n次方根
 * 输入参数：a（已知复数）
 *            n（n次方根）
 *            c（计算结果的结构体，是一个数组，共n个）
 * 返回值：0（失败），1（成功）
 */
int c_comp_nthroot(struct c_comp *a,struct c_comp *c,int n)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_nthroot)The c_comp pointer is NULL!\n");
        return(0);
    }

    double theta = atan2(a->imz,a->rmz);
    double R = sqrt(a->rmz*a->rmz + a->imz*a->imz);
    R = pow(R,1.0/n);

    for(int i=0; i<n; i++)
    {
        c[i].rmz = R*cos((theta+2*i*PI)/n);
        c[i].imz = R*sin((theta+2*i*PI)/n);
    }

    return(1);
}
