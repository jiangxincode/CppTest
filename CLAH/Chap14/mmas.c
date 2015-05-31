﻿/**
 * 函 数 名：mmas
 * 功能描述：寻找第m大的元素，运行结束后，第m大的元素就在第m个位置上
 * 输入参数： x 存放无序数据的数组
 *            n 数组的长度
 *            m 要找第m大的元素
 * 返 回 值：无
 */
void mmas(int *x,int n,int m)
{
    int i,j,s,t,flag,tmp;
    s = 0;                           /* 查找区间的首和尾*/
    t = n-1;

    do
    {
        if(t <= s+1)                        /* 区间只有一个或两个元素时*/
        {
            if((t==s+1) && x[t] < x[s])     /* 两个元素时，将小的交换到前面*/
            {
                tmp = x[t];
                x[t] = x[s];
                x[s] = tmp;
            }

            return;
        }

        i = s+1;                             /* 对i,j赋初值*/
        j = t;
        flag = x[s];                         /* 选取第一个值做岗哨*/

        do
        {
            while(x[i] < flag)
            {
                i++;    /* 扫描搜索需要交换的数据*/
            }

            while(x[j] > flag)
            {
                j--;    /* 扫描搜索需要交换的数据*/
            }

            if(i<j)
            {
                tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;
            }
        }
        while(i<j);                          /* 对当前排序区间进行划分*/

        x[s] = x[j];
        x[j] = flag;

        if(j < m-1)                            /* 第m小的元素在后面的子空间内*/
        {
            s = j+1;
        }
        else if(j >= m)                         /* 第m小的元素在前面的子空间内*/
        {
            t = j-1;
        }
        else
        {
            return;
        }
    }
    while(1);
}
