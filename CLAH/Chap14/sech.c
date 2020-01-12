﻿/**
 * 函 数 名：sech
 * 功能描述：无序结构体数组中查找
 * 输入参数： x 指向无序结构体数组的指针
 *            n 数组长度
 *            k 在数组x中查找的开始位置
 *            a 存放要查找的关键字的值
 * 返 回 值：第一个满足要求的成员位置，如果没有找到则返回-1
 */
#include "../utility.h"
int sech(struct student *x,int n,int k,int a)
{
    int i;
    i = k;

    while(i<n &&(x[i].KEY != a))
    {
        i++;
    }

    if(i==n)
    {
        return(-1);
    }

    return(i);
}
