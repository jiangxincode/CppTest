﻿/**
 * 函 数 名：hashpos
 * 功能描述：计算关键字元素对应的位置
 * 输入参数： str 指向字符串的指针
 *            i 选择算法，应在0~7之间
 *            m 哈希表的长度，应该为素数
 * 返 回 值：元素对应的位置
 */

int hashpos(char *str,int i,int m)
{
    unsigned int k = hashk(str,i);       /* 调用一个算法计算对应的整数*/
    return((int)(k%m));
}
