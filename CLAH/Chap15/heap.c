﻿/**
 * 函 数 名：heap
 * 功能描述：堆排序
 * 输入参数： x 存放待排序数据的数组
 *            n 数组长度
 * 返 回 值：无
 */
static void sift();
void heap(int *x,int n)
{
    int i,t;

    for(i=n/2-1; i>=0; i--)             /* 构建初始堆*/
    {
        sift(x,n,i);
    }

    for(i=1; i<n; i++)                  /* 依次弹出n-1个根结点，并维护堆*/
    {
        t = x[0];                       /* x[0]就是根，也是当前最大值*/
        x[0] = x[n-i];
        x[n-i] = t;
        sift(x,n-i,0);                  /* 筛x[0]*/
    }

    return;
}

static void sift(int *x,int n,int i)                        /* 对x[n]数组中x[i]元素进行筛运算，*/
                            /* 假定以x[i+1]到x[n-1]的每个元素为根的子树已经成为堆*/
{
    int j,t;
    t = x[i];                           /* 待筛结点的值*/
    j = 2*i+1;                          /* x[j]是x[i]的左孩子*/

    while(j<n)
    {
        if((j<n-1)&&(x[j]<x[j+1]))      /* 放入与较大的右孩子一边*/
        {
            j++;
        }

        if(t < x[j])
        {
            x[i] = x[j];                /* 较大的元素放在x[i]中*/
            i = j;                      /* 同时i下沉一层*/
            j = 2*i+1;                  /* 在求i的左孩子*/
        }
        else
        {
            break;    /* 此时或已经到底，或比左孩子和右孩子都大*/
        }
    }

    x[i] = t;
}
