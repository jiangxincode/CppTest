﻿#include <stdio.h>
#include "spl.c"
#include "sple.c"
int main7spl0()
{
    int n;
    double t,z;
    double x[10]= {0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00};
    double y[10]= {2.1152,2.2614,2.4399,2.6518,2.8987,
                   3.1821,3.5038,3.8655,4.2696,4.7183
                  };
    n=10;
    printf("f(0.20):\n");
    t=0.20;                                          /* 求解在0.20处的插值*/
    z = spl(x,y,n,t,1e-12);                          /* 调用插值函数求值*/
    printf("spl:  x=%2.5f,f(x)=%2.5f\n",t,z);        /* 打印结果*/
    z = sple(x[0],0.1,y,n,t,1e-12);                  /* 调用等距插值函数求值*/
    printf("sple: x=%2.5f,f(x)=%2.5f\n",t,z);        /* 打印结果*/
    printf("f(0.55):\n");
    t = 0.55;                                        /* 求解在0.55处的插值*/
    z = spl(x,y,n,t,1e-12);                          /* 调用插值函数求值*/
    printf("spl:  x=%2.5f,f(x)=%2.5f\n",t,z);        /* 打印结果*/
    z = sple(x[0],0.1,y,n,t,1e-12);                  /* 调用等距插值函数求值*/
    printf("sple: x=%2.5f,f(x)=%2.5f\n",t,z);        /* 打印结果*/
    return 0;
}
