﻿#include <stdio.h>
#include "../utility.h"

int main12s2implex0()
{
    int i,j,n,m1,m2,m3,ixr[9],ixc[9];
    double eps=1.0e-10;
    double a[8][10] = {{0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
        {0.5, 1.0,0.0,1.0,0.0,1.0,0.0,1.0,0.0,1.0},
        {0.5, 0.0,1.0,1.0,0.0,1.0,0.0,1.0,0.0,1.0},
        {0.5, 0.0,1.0,0.0,1.0,1.0,0.0,1.0,0.0,1.0},
        {0.5, 0.0,1.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0},
        {0.5, 0.0,1.0,0.0,1.0,0.0,1.0,0.0,1.0,1.0},
        {1.0, 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0}
    };
    n = 9;
    m1 = 5;
    m2 = 1;
    m3 = 0;
    i = simplex(a,n,m1,m2,m3,ixr,ixc,eps);               /* 调用函数*/
    printf("aaa:: %d\n", i);

    for(j=1; j<=n; j++)                               /* 提取出值为0的x标号*/
    {
        if(ixr[j] < n)
        {
            printf("x%d = 0.00\n", ixr[j]);
        }
    }

    for(i=1; i<=n; i++)                              /* 提取出值不为0的x标号*/
    {
        if(ixc[i] <n)
        {
            printf("x%d =%5.2f\n", ixc[i], a[i][0]);
        }
    }

    printf("fopt = %5.2f\n", a[0][0]);                /* 函数的极小值*/
    printf("\nlast simplex:\n");                      /* 打印最终的单纯形表*/
    printf("      b    ");

    for(j=1; j<9; j++)
    {
        if(ixr[j] < n+m1+m2)                         /* 跳过辅助问题的变量z*/
        {
            printf("x%d    ",ixr[j]);
        }
    }

    printf("\n");
    printf("f  ");

    for(j=0; j<9; j++)
    {
        if(ixr[j] < n+m1+m2)                         /* 跳过辅助问题的变量z*/
        {
            printf("%5.2f ",a[0][j]);
        }
    }

    printf("\n");

    for(i=1; i<7; i++)
    {
        printf("x%d ", ixc[i]);                      /* 本行对应的变量标号*/

        for(j=0; j<9; j++)
        {
            if(ixr[j] < n+m1+m2)                     /* 跳过辅助问题的变量z*/
            {
                printf("%5.2f ",a[i][j]);
            }
        }

        printf("\n");
    }

    return 0;
}
