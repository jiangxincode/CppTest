﻿/*=============================================================
// 函 数 名：mgst
// 功能描述：二路归并排序
// 输入参数： x 存放待排序数据的数组
//            n 数组长度
// 返 回 值：无
//==============================================================*/
#include <stdlib.h>
static void Merge();                              /* 需要调用的归并函数*/
static void mgst(x,n)
int *x;
int n;
{
    int i,flag,L,*x1;
    x1 = (int*)malloc(n*sizeof(int));
    L = 1;
    flag = 1;

    while(L<n)
    {
        if(flag)
        {
            Merge(x,x1,n,L);    /* 归并排序，结果放在x1中*/
        }
        else
        {
            Merge(x1,x,n,L);    /* 归并排序，结果放在x中*/
        }

        flag = 1-flag;
        L = 2*L;
    }

    if(flag==0)
        for(i=0; i<n; i++)
        {
            x[i] = x1[i];
        }

    free(x1);
    return;
}

static void Merge(x,x1,n,L)                       /* 把数组x中的每个长度为L的有序序列归并到x1中*/
int *x,*x1,n,L;
{
    int i,j,k,s,m,t,t2;
    s = 0;                                 /* 待归并的一对序列的第一个元素位置*/
    t2 = n-2*L+1;

    while(s < t2)
    {
        m = s+L-1;                         /* 第一个序列的末尾*/
        t = m+L;                           /* 第二个序列的末尾*/
        i = s;                             /* 第一个序列的开头位置*/
        j = m+1;                           /* 第二个序列的开头位置*/
        k = s;                             /* x1中存放归并后序列的起始位置*/

        while(i<=m && j<=t)                /* 两个序列都还有元素时，依次插入*/
            if(x[i]<x[j])
            {
                x1[k++] = x[i++];
            }
            else
            {
                x1[k++] = x[j++];
            }

        while(i<=m)
        {
            x1[k++] = x[i++];
        }

        while(j<=t)
        {
            x1[k++] = x[j++];
        }

        s = s+2*L;
    }

    if(s+L < n)                            /* 末尾的两个序列一长一短*/
    {
        m = s+L-1;                         /* 第一个序列的末尾*/
        t = n-1;                           /* 第二个序列的末尾*/
        i = s;                             /* 第一个序列的开头位置*/
        j = m+1;                           /* 第二个序列的开头位置*/
        k = s;                             /* x1中存放归并后序列的起始位置*/

        while(i<=m && j<=t)                /* 两个序列都还有元素时，依次插入*/
            if(x[i]<x[j])
            {
                x1[k++] = x[i++];
            }
            else
            {
                x1[k++] = x[j++];
            }

        while(i<=m)
        {
            x1[k++] = x[i++];
        }

        while(j<=t)
        {
            x1[k++] = x[j++];
        }

        s = s+2*L;
    }
    else
        for(i=s; i<n; i++)                  /* 末尾只有一个序列，直接拷贝*/
        {
            x1[i] = x[i];
        }
}
