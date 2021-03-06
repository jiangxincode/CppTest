﻿#include "../utility.h"

static double f();
static void df();
int cggm0()
{
    double  eps,fopt,x[3],xm[3];
    int itmax = 50, n = 3,it;
    eps = 1e-7;
    x[0] = x[1] = x[2] = 6.0;
    printf("Fletcher-Reeves  ");
    it = cggm1(x, xm, n, &fopt, f, df, eps, itmax);
    printf("iterations = %d:\n x0=%f,x1=%f,x2=%f\nfopt=%f\n",it,xm[0],xm[1],xm[2],fopt);
    printf("Polak-Ribire  ");
    it = cggm2(x, xm, n, &fopt, f, df, eps, itmax);
    printf("iterations = %d:\n x0=%f,x1=%f,x2=%f\nfopt=%f\n",it,xm[0],xm[1],xm[2],fopt);
    return 0;
}

static double f(double *x, int n)
{
    double y;

    if(n!=3)
    {
        return(0.0);
    }

    y = (x[0]-1.0)*(x[0]-1.0)+(x[1]-2.0)*(x[1]-2.0)+(x[2]-3.0)*(x[2]-3.0);
    return y;
}
void df(double *x, double *g, int n)
{
    if(n!=3)
    {
        return;
    }
    g[0] = (2*(x[0]-1.0));
    g[1] = (2*(x[1]-2.0));
    g[2] = (2*(x[2]-3.0));
}
