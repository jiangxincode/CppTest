﻿/**
 * 函 数 名：bist
 * 功能描述：二分查找
 * 输入参数： x 存放有序序列的数组
 *            n 数组长度
 *            a 待查找的元素
 * 返 回 值：待查找元素的位置，若此元素不存在，则返回-1
 */
int bist(int *x,int n,int a)
{
    int s,t,k;
    s = 0;                             /* 设置初值*/
    t = n-1;

    do
    {
        if(t==s)                      /* 只有一个元素*/
        {
            if(x[t] == a)
            {
                return(t);
            }
            else
            {
                return(-1);
            }
        }

        k = (s+t)/2;                  /* 二分*/

        if(x[k] < a)                  /* 比较*/
        {
            s = k;
        }
        else if(x[k] > a)
        {
            t = k;
        }
        else
        {
            return(k);    /* 已经找到*/
        }
    }
    while(1);
}
