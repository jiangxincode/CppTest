﻿#include "../utility.h"

/**
 * 函 数 名：Fsech
 * 功能描述：磁盘文件中记录的顺序查找
 * 输入参数： fp 指向文件的指针
 *            a 存放要查找的关键字的值
 *            str 指向用于存放记录的结构体
 * 返 回 值：找到则返回1，如果没有找到则返回0
 */

int Fsech(FILE *fp,int a,struct student *str)
{
    int flag,q;
    long int k;
    k = sizeof(struct student);
    flag = 1;

    while(flag)
    {
        if(fread(str,k,1,fp) == 0)       /* 已经到达文件尾，什么都没找到*/
        {
            flag = 0;
            q = 0;
        }
        else                                 /* 找到一条记录*/
        {
            if(str->KEY == a)                 /* 这条记录满足要求*/
            {
                flag = 0;
                q = 1;
            }
        }
    }

    return(q);
}
