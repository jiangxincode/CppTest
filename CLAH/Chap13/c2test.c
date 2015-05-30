﻿/*======================================================
//函数名：c2test.c
//功能描述：用卡方分布检验随机数是否符合已知分布
//输入参数：a（简单随机样本的在每个区间内的个数）
//	    e（理想分布情况下在每个区间内的频数）
//	    r（区间的分割个数）
 *      k（已知分布所含未知参数的个数）
 *      v（统计量自由度的输出值）
 *      c2（统计量的值）
 *      alpha（显著性标准）
//返回值：1（符合分布），0（不符合分布）
=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Chap11/../utility.h"

static int c2test(a,e,r,k,v,c2,alpha)
double *c2,alpha;
int *a,*e,r,k,*v;
{
    double s;
    int i;
    *v=r-k-1;//计算自由度
    *c2=0;

    for(i=0; i<r; i++)
    {
        *c2=*c2+(double)((a[i]-e[i])*(a[i]-e[i]))/(double)(e[i]);    //计算统计量的值
    }

    s=chii(*c2,*v);//调用卡方函数计算函数值
    printf("s=%1.8f\n",s);

    if(s>alpha)//如果返回值是小值，则不符合已知分布
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



