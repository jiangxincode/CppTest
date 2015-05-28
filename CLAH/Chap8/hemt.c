#include <math.h>
/*======================================================
// 函数名：hemt
// 功能描述：埃尔米特-高斯求积法进行积分
// 输入参数：f 指向被积函数的指针
// 返回值：  积分近似值
=========================================================*/
static double hemt(f)
double(*f)();
{
    int i;
    double z;                                   /* 5阶埃尔米特多项式的零点*/
    static double t[5] = {-2.020182496984754,-0.9585724979524882,0.0,
                          0.9585724979524882, 2.020182496984754
                         };
    static double c[5] = {1.181487737274476,0.986580905130196,
                          0.945308813693166,0.986580905130196,1.181487737274476
                         };
    z = 0.0;

    for(i=0; i<5; i++)                           /* 求解积分值*/
    {
        z = z+c[i]*(*f)(t[i]);
    }

    return(z);
}
