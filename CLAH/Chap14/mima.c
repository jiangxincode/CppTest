﻿/**
 * 函 数 名：mima
 * 功能描述：同时求出序列中的最大值和最小值
 * 输入参数： x 存放无序序列的数组
 *            n 数组长度
 *            mi,ma 返回最小值和最大值
 * 返 回 值：无
 */
void mima(int *x,int n,int *mi,int *ma)
{
    int i;

    if(n%2 == 0) //设定初值，n为偶数的情况
    {
        if(x[0] < x[1])                     /* 选取较小的一个作为mi,较大的作ma*/
        {
            *mi = x[0];
            *ma = x[1];
        }
        else
        {
            *mi = x[1];
            *ma = x[0];
        }

        i = 2;                              /* 已经有2个元素参与过比较*/
    }
    else //n为奇数的情况，已经有1个元素参与过比较*/
    {
        *mi = x[0];
        *ma = x[0];

        i = 1;
    }

    while(i<n)                              /* 每次取两个元素递推*/
    {
        if(x[i] < x[i+1])                   /* 比较出较大者和较小者*/
        {
            *mi = (x[i]<(*mi))?x[i]:(*mi);
            *ma = (x[i+1]>(*ma))?x[i+1]:(*ma);
        }
        else
        {
            *mi = (x[i+1]<(*mi))?x[i+1]:(*mi);
            *ma = (x[i]>(*ma))?x[i]:(*ma);
        }

        i = i+2;                            /* 又有两个元素参与过比较*/
    }

    return;
}