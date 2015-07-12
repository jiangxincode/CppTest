#include "../utility.h"

/**
 * 函数名：c_comp_power.c
 * 功能描述：求复数的乘幂
 * 输入参数：a（底数的结构体）
 *            n（指数）
 *            c（计算结果的结构体）
 * 返回值：0（失败），1（成功）
 */

int c_comp_power(const struct c_comp *a,struct c_comp *c,const int n)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_power)The c_comp pointer is NULL!\n");
        return 0;
    }

    double theta = atan2(a->imz,a->rmz);
    double R = sqrt(a->rmz*a->rmz + a->imz*a->imz);
    theta = n*theta;
    R = pow(R,n);
    c->rmz = R*cos(theta);
    c->imz = R*sin(theta);
    return 1;
}
