﻿/*=============================================================
 * 函 数 名：hashsch
 * 功能描述：在哈希表中查找一个元素
 * 输入参数： HD 哈希表数组的指针
 *            m 哈希表的长度，应该为素数
 *            a 待查找的元素的关键字
 * 返 回 值：若找到则返回其位置,否则返回-1
//==============================================================*/
#include "../utility.h"
int hashsch(hashlist HT,int m,KeyType a)
{
    int temp,d,i;
    d = hashpos(a, 0, m);
    temp = d;
    i = 1;

    while(!KeyEqu(HT[d].KEY,NULLTag))              /* 常量NULLTag是空标志，需要自己定义*/
    {
        if(KeyEqu(HT[d].KEY, a))              /* 已经找到，返回位置*/
        {
            return(d);
        }

        d = (d+2*i-1)%m;                         /* 不为空且不相等，说明已经被其它元素占据，向后探查*/
        i++;

        if(d == temp)                            /* 这时查找失败*/
        {
            return(-1);
        }
    }

    return(-1);                                    /* 这时查找失败*/
}
