﻿/*=============================================================
 * 函 数 名：popo
 * 功能描述：冒泡排序
 * 输入参数： x 存放待排序数据的数组
 *            n 数组长度
 * 返 回 值：无
//==============================================================*/
static void popo(x,n)
int *x;
int n;
{
    int head,tail,i,j,t,flag;
    head = 0;
    tail = n-1;
    flag = 1;

    while((head<tail)&&(flag==1))
    {
        flag = 0;
        j = tail;

        for(i=head; i<j; i++)             /* 从头向后扫描*/
            if(x[i]>x[i+1])
            {
                t = x[i];
                x[i] = x[i+1];
                x[i+1] = t;
                tail = i;                  /* 当前交换到的最大值位置*/
                flag = 1;                  /* 若有交换，则说明还未完全有序*/
            }

        j = head;

        for(i=tail; i>j; i--)          /* 从后向头扫描*/
            if(x[i-1]>x[i])
            {
                t = x[i];
                x[i] = x[i-1];
                x[i-1] = t;
                head = i;                  /* 交换到的最小值位置*/
                flag = 1;                  /* 若有交换，则说明还未完全有序*/
            }
    }

    return;
}
