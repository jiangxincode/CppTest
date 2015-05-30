/*======================================================
//函数名：Tminv
//功能描述：Toeplitz矩阵快速求逆
//输入参数：t1 双精度实型一维数组的指针?
            数组中存放n阶T型矩阵第一个元素及上三角元素
            t2 双精度实型一维数组的指针?
            其中后n-1个元素存放n阶T型矩阵中的下三角元素
            n 矩阵阶数
            mat 返回的逆矩阵存放位置
            eps 精度要求，绝对值小于此数的值认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

static int Tminv(t1,t2,n,mat,eps)
double *t1, *t2;
int n;
double *mat;
double eps;
{
    int i,j,k,l;
    double a,tmp,*c,*r,*p;

    c = (double *)malloc(n*sizeof(double));    /* 为临时变量分配空间*/
    r = (double *)malloc(n*sizeof(double));
    p = (double *)malloc(n*sizeof(double));

    if (fabs(t1[0]) < eps)                     /* 检查首项是否为0*/
    {
        free(c);                                 /* 若首项为0，则释放空间并退出*/
        free(r);
        free(p);
        printf("Fail to invert\n");
        return(0);
    }

    a = t1[0];                                /* 计算初值*/
    c[0] = t2[1]/t1[0];
    r[0] = t1[1]/t1[0];

    for(k=0; k<n-2; k++)                      /* k从0到n-3做如下的循环*/
    {
        tmp = 0.0;
        for(j=1; j<k+2; j++)                  /* 求第一个累加和*/
            tmp = tmp + c[k+1-j]*t2[j];
        tmp=(tmp-t2[k+2])/a;

        for(i=0; i<k+1; i++)              /* 先存放在p中，因为c[i]的原值还要使用*/
            p[i] = c[i] + tmp*r[k-i];
        c[k+1] = -tmp;                    /* 新求出c[k+1]的值*/

        tmp = 0.0;
        for(j=1; j<k+2; j++)              /* 第二个累加和*/
            tmp = tmp + r[k+1-j]*t1[j];
        tmp = (tmp-t1[k+2])/a;

        for(i=0; i<k+1; i++)
        {
            r[i] = r[i] + tmp*c[k-i];     /* 更新r[i]的值*/
            c[k-i] = p[k-i];              /* c[k-i]的值不再使用，用p中的数据更新*/
        }
        r[k+1] = -tmp;                    /* 新求出r[k+i]的值*/

        a = 0.0;
        for(j=1; j<k+3; j++)              /* 更新a的值*/
            a = a+ t1[j]*c[j-1];
        a = t1[0]-a;
        if(fabs(a) < eps)                 /* 若a过小，则退出函数。求逆过程不能继续*/
        {
            free(c);                      /* 释放空间*/
            free(r);
            free(p);
            printf("Fail to invert\n");
            return(0);
        }
    }

    mat[0] = 1.0/a;                      /* 利用求得的r,c,a构造逆矩阵*/
    for(i=0; i<n-1; i++)
    {
        k = i+1;
        mat[k] = -r[i]/a;                /* 逆矩阵的第一行*/
        mat[k*n] = -c[i]/a;              /* 逆矩阵的第一列*/
    }
    for(i=0; i<n-1; i++)                 /* 逆矩阵的其他元素*/
        for(j=0; j<n-1; j++)
        {
            l = (i+1)*n+j+1;
            k = i*n+j;
            mat[l] = mat[k]+(c[i]*r[j] - r[n-2-i]*c[n-2-j])/a;
        }
    free(c);                            /* 释放空间*/
    free(r);
    free(p);
    return(1);
}
