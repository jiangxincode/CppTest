#include "../utility.h"

/**
 * 函数名：interroot
 * 功能描述：求出[a,b]区间内的非线性方程f(x)的一个实根
 * 输入参数：x0（迭代初值以 * 返回值及迭代终值的初值指针）
 *          ab（未被选为初值的区间端点）
 *          f（非线性方程左端函数）
 *          eps（精度要求）
 *          max（最大迭代次数）
 * 返回值：0（迭代失败）1（迭代成功）
 */
int interroot(double *x0,double ab,double(*f)(),double eps,int max)
{
    double x,dis;
    double y0,yd,yab=f(ab);
    int num=0;

    do
    {
        y0=f(*x0);			     /* 计算函数值*/
        yd=(*x0-ab)/(y0-yab);    /* 计算函数导数值得倒数值*/
        x=*x0-yd*y0;             /* 计算新的x值*/
        num++;
        dis=fabs(x-*x0);         /* 计算精度*/

        if(dis<fabs(y0))
        {
            dis=fabs(y0);
        }

        printf("%1.7f    %1.7f    %1.7f\n",*x0,x,dis);
        *x0=x;
    }
    while(dis>eps&&num<max);     /* 判断迭代是否结束*/

    if(num==max)
    {
        return (0);    /* 迭代失败*/
    }
    else
    {
        return (1);    /* 迭代成功*/
    }
}

