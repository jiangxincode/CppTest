#include <math.h>
/*======================================================
 * 函数名：tzi1
 * 功能描述：变步长梯形求积分
 * 输入参数：a 积分下限，b 积分上限,
 *           n0 初始划分数
 *           eps 精度要求
 *           h0 最小步长
 *           f 指向被积函数的指针
 * 返回值：  积分近似值
=========================================================*/
static double tzi1(double a,double b,int n0,double eps,double h0,double(*f)(double))
{
    int n,k;
    double z,z2,h,d,x,t;
    n = n0;                            /* 初始的划分数*/
    h = (b-a)/n;                       /* 求得初始步长*/
    z = ((*f)(a)+(*f)(b))/2.0;         /* 计算初始的积分值*/

    for(k=1; k<n; k++)
    {
        x = a+k*h;
        z = z+(*f)(x)*h;                   /* 累次求和*/
    }

    z = z*h;                           /* 尽量减少乘法次数*/

    do
    {
        t = 0.0;

        for(k=0; k<n; k++)
        {
            x = a+(k+0.5)*h;
            t = t+(*f)(x);
        }

        z2 = (z+h*t)/2.0;                /* 计算新的积分值*/
        d = fabs(z2-z);                  /* 计算两次积分值的差*/
        z = z2;                          /* 更新积分值*/
        h = h/2.0;                       /* 更新步长*/
        n = 2*n;                         /* 更新划分数*/
    }
    while((d>eps)&&(h>h0));

    return(z);
}
