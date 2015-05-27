#include "stdio.h"
#include "bmqr.c"
main5bmqr0()
{
  int i,j;
  double a[5][5]={{0.81,0.10,0.16,0.14,0.66},
    {0.91,0.28,0.97,0.42,0.04},
    {0.13,0.55,0.96,0.92,0.85},
    {0.91,0.96,0.49,0.79,0.93},
    {0.63,0.96,0.80,0.96,0.68}};
  double x[5],b[5] = {3.0,1.5,-2.5,2.0,1.0};   /* 常数向量赋值*/
  i=bmqr(a,b,x,5,1e-4,1);                     /* 调用函数求解*/
  if(i!=0)                                     /* 打印结果*/
  {
    for(i=0; i<5; i++)
      printf("x(%d) = %2.5f\n",i,x[i]);
  }
}
