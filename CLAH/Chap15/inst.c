﻿/**
 * 函 数 名：inst
 * 功能描述：直接插入排序
 * 输入参数： x 存放待排序数据的数组
 *            n 数组长度
 * 返 回 值：无
 */
void inst(int *x,int n)
{
    int i,j,t;

    for(i=1; i<n; i++)                  /* i表示插入次数，共进行n-1次插入*/
    {
        t = x[i];

        for(j=i-1; j>=0; j--)           /* 寻找要插入t的位置*/
            if(t < x[j])                /* 后移，空出位置*/
            {
                x[j+1] = x[j];
            }
            else
            {
                break;    /* 找到位置时，退出循环*/
            }

        x[j+1] = t;                      /* 直接插入*/
    }

    return;
}
