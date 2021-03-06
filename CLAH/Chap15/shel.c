﻿/**
 * 函 数 名：shel
 * 功能描述：希尔排序
 * 输入参数： x 存放待排序数据的数组
 *            n 数组长度
 * 返 回 值：无
 */
void shel(int *x,int n)
{
    int i,j,d,t;
    d = n/2;                                    /* 初始步长是n/2*/

    while(d>0)                                  /* 按不同步长进行排序*/
    {
        for(i=d; i<n; i++)                      /* 将x[i]插入到对应分组的合适位置中*/
        {
            t = x[i];
            j = i-d;

            while((j>=0)&&(x[j]>t))              /* 比较和移动*/
            {
                x[j+d] = x[j];
                j = j-d;
            }

            x[j+d] = t;			                 /* 找到了位置*/
        }

        d = d/2;                                 /* 步长减半*/
    }

    return;
}
