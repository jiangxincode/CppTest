﻿/*======================================================
 * 函数名：dirmin
 * 功能描述：一维搜索
 * 输入参数：x[n] 输入搜索的出发点
 *           p[n] 搜索的方向
 *           xmin[n] 返回找到的最优点
 *           n 初始区间的另一个端点
 *           f 多元函数指针
 *           eps 精度限度
 *           itmax 最大迭代次数
 * 返回值：  函数的极小值
=========================================================*/
#include "../utility.h"

int _ndir_;
double *_pdir_, *_xdir_, *_xtdir_,(*_myfc_)();              /* 需要全局变量*/

double dirmin(double *x, double *p, double *xmin, int n, double (*f)(), double eps, int itmax)
{
    int i;
    double fdim(), ax, bx, cx, fopt, xopt;
    _ndir_ = n;
    _pdir_ = (double*)malloc(_ndir_*sizeof(double));
    _xdir_ = (double*)malloc(_ndir_*sizeof(double));
    _xtdir_ = (double*)malloc(_ndir_*sizeof(double));
    _myfc_ = f;                                            /* 全局变量指向函数*/

    for(i=0; i<n; i++)
    {
        _pdir_[i] = p[i];
        _xdir_[i] = x[i];
    }

    ax = 0.0;                                             /* 初始猜想范围*/
    bx = 0.5;
    brake(&ax, &bx, &cx, fdim);                          /* 找一个极小值区间*/
    fopt = brent(ax, bx, cx, fdim, &xopt, eps, itmax);     /* 用brent算法找极小值*/

    for(i=0; i<n; i++)                                    /* 找到了最优点x*/
    {
        p[i] = xopt*p[i];
        xmin[i] = x[i]+p[i];
    }

    free(_pdir_);
    free(_xdir_);
    free(_xtdir_);
    return(fopt);
}

static double fdim_jiang(double t)                                     /* 求f在这个方向上行进t时的值*/
{
    int i;
    double y;

    for(i=0; i<_ndir_; i++)
    {
        _xtdir_[i] = _xdir_[i] + t*_pdir_[i];
    }

    y = _myfc_(_xtdir_, _ndir_);
    return(y);
}
