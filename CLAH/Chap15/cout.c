﻿/*=============================================================
 * 函 数 名：cout
 * 功能描述：计数排序
 * 输入参数： x 存放待排序数据的数组
 *            y 存放输入的有序序列
 *            n 数组长度
 *            k 数据的范围在[0,k]之间
 * 返 回 值：无
//==============================================================*/
#include <stdlib.h>
static void cout(x,y,n,k)
int *x,*y;
int n,k;
{
    int i,j,*c;
    c = (int*)malloc((k+1)*sizeof(int));

    for(i=0; i<=k; i++)                     /* 设置初值*/
    {
        c[i] = 0;
    }

    for(i=0; i<n; i++)                      /* 统计个数*/
    {
        j = x[i];
        c[j] = c[j]+1;
    }

    for(i=1; i<=k; i++)                     /* 计数，用于计算位置*/
    {
        c[i] = c[i]+c[i-1];
    }

    for(i=n-1; i>=0; i--)                   /* 直接各归其位*/
    {
        j = x[i];
        y[c[j]-1] = j;
        c[j] = c[j] - 1;
    }

    free(c);
    return;
}
