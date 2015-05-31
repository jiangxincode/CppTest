﻿#include "../utility.h"

/**
 * 函数名：ddirmin
 * 功能描述：带导数的一维搜索
 * 输入参数：x[n] 输入搜索的出发点
 *           p[n] 搜索的方向
 *           xmin[n] 返回找到的最优点
 *           n 初始区间的另一个端点
 *           f 多元函数指针
 *           eps 精度限度
 *           itmax 最大迭代次数
 * 返回值：  函数的极小值
 */

static double dfdim(double t);
static double fdim_jiang();

int _ndir_;
double *_pdir_, *_xdir_, *_xtdir_, *_dxtdir_;             /* 需要全局变量*/
double(*_myfc_)();
void (*_mydfc_)();                             /* 需要全局变量*/

double ddirmin(double *x, double *p, double *xmin, int n, double (*f)(double),double (*df)(double), double eps, int itmax)
{
    int i;
    double ax, bx, cx, fopt, xopt;
    _ndir_ = n;
    _pdir_ = (double*)malloc(_ndir_*sizeof(double));
    _xdir_ = (double*)malloc(_ndir_*sizeof(double));
    _xtdir_ = (double*)malloc(_ndir_*sizeof(double));
    _dxtdir_= (double*)malloc(_ndir_*sizeof(double));
    _myfc_ = f;                                            /* 全局变量指向函数*/
    _mydfc_ = df;

    for(i=0; i<n; i++)
    {
        _pdir_[i] = p[i];
        _xdir_[i] = x[i];
    }

    ax = 0.0;                                             /* 初始猜想范围*/
    bx = 0.5;
    brake(&ax, &bx, &cx, fdim);                          /* 找一个极小值区间*/
    fopt = dbrent(ax, bx, cx, fdim_jiang, dfdim, &xopt, eps, itmax);     /* 用brent算法找极小值*/

    for(i=0; i<n; i++)                                    /* 找到了最优点x*/
    {
        p[i] = xopt*p[i];
        xmin[i] = x[i]+p[i];
    }

    free(_pdir_);
    free(_xdir_);
    free(_xtdir_);
    free(_dxtdir_);
    return(fopt);
}

static double fdim_jiang(t)                                     /* 求f在这个方向上行进t时的值*/
double t;
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

static double dfdim(double t)                                     /* 求f在这个方向行进到t处的导数值*/
{
    int i;
    double df;

    for(i=0; i<_ndir_; i++)
    {
        _xtdir_[i] = _xdir_[i] + t*_pdir_[i];
    }

    _mydfc_(_xtdir_, _dxtdir_, _ndir_);
    df = 0.0;

    for(i=0; i<_ndir_; i++)
    {
        df = df + _dxtdir_[i]*_pdir_[i];
    }

    return(df);
}
