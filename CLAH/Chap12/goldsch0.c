#include "../utility.h"

static	double f();
static double df();

int glodch0()
{
    double a,b,c,xopt,eps, xmin[50];
    int i,j, nmin, iflag;
    eps = 1e-10;
    nmin = 0;
    printf("Gold Serch:\n");

    for(i=1; i<50; i++)
    {
        a = i;
        b = i+1;
        brake(&a,&b,&c,f);
        goldsch(a,b,c,f,&xopt,eps);

        if(nmin == 0)
        {
            xmin[0] = xopt;
            nmin++;
            printf("num%d  x=%7.5f  f=%7.5f df=%7.5f\n", nmin,xopt,f(xopt),df(xopt));
        }
        else
        {
            iflag = 0;

            for(j=0; j<nmin; j++)                           /* 寻找是否已经有相同的极小值*/
                if(fabs(xopt-xmin[j]) < 0.01*xopt)
                {
                    iflag = 1;
                }

            if(iflag==0)
            {
                xmin[nmin++] = xopt;
                printf("num%d  x=%7.5f  f=%7.5f df=%7.5f\n", nmin,xopt,f(xopt),df(xopt));
            }
        }
    }

    return 0;
}

static double f(double x)
{
    return bsl1(0,x);
}
static double df(double x)
{
    return -bsl1(1,x);
}
