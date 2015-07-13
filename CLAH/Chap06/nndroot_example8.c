#include "../utility.h"

static void f(double*,double*,double*,double);
int nndroot8()
{
    double eps=0.000001,h=0.1,t=0.5;
    int n=3,max=600,i;
    double *x0;
    x0=(double*)malloc(n*sizeof(double));
    x0[0]=1;                                 /* 初值*/
    x0[1]=-3;
    x0[2]=5;

    if(nndroot(x0,n,f,eps,max,h,t))
    {
        for(i=0; i<n; i++)
        {
            printf("x[%d]=%1.7f\n",i,x0[i]);    /* 输出*/
        }
    }
    else
    {
        printf("failed!\n");
    }

    return 0;
}

static void f(x,f0,fi,h)							/*方程组函数*/
double *x,*f0,*fi;
double h;
{
    double tmp;
    int i;
    f0[0]=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]-40;
    f0[1]=x[0]*x[0]+7*x[0]*x[1]+3*x[2]+14;
    f0[2]=5*x[0]*x[2]+x[1]*x[2]-24;

    for(i=0; i<3; i++)
    {
        tmp=x[i];
        x[i]=x[i]+h;
        fi[i]=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]-40;
        fi[3+i]=x[0]*x[0]+7*x[0]*x[1]+3*x[2]+14;
        fi[6+i]=5*x[0]*x[2]+x[1]*x[2]-24;
        x[i]=tmp;
    }

    return;
}

