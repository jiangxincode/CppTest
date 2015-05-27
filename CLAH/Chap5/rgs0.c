#include "stdio.h"
#include "r_gaus.c"
#include "r_gsjd.c"
main5rgs0()
{
    int i;
    double a1[4][4]=                         /* 调用函数会破坏矩阵数据，因此需要两份*/
    {
        {0.2368,0.2471,0.1324,0.0531},
        {0.1968,0.2071,1.2168,0.0120},
        {0.1682,1.1675,0.1768,0.1871},
        {0.2104,0.1045,0.1397,0.1490}
    };
    double a2[4][4]=
    {
        {0.2368,0.2471,0.1324,0.0531},
        {0.1968,0.2071,1.2168,0.0120},
        {0.1682,1.1675,0.1768,0.1871},
        {0.2104,0.1045,0.1397,0.1490}
    }; /* 调用函数会破坏常数向量数据，因此需要两份*/
    double b1[4]= {1.8471,1.7471,1.6471,1.5471},b2[4]= {1.8471,1.7471,1.6471,1.5471};
    double x1[4],x2[4];
    printf("GAUSS:\n");
    if(r_gsjd(a2,b2,x2,4,1e-16)!=0)           /* 调用高斯消去法*/
        for(i=0; i<4; i++)                     /* 打印结果*/
            printf("x2(%d)=%7.5f\n",i,x2[i]);
    printf("\n");
    printf("GAUSS JORDAN:\n");
    if(r_gsjd(a1,b1,x1,4,1e-16)!=0)           /* 调用高斯－约当消去法*/
        for(i=0; i<4; i++)                     /* 打印结果*/
            printf("x1(%d)=%7.5f\n",i,x1[i]);
}
