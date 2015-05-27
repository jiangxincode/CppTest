#include "stdio.h"
#include "math.h"
#include "bsl1.c"
#include "goldsch.c"
#include "brake.c"

void main()
{
	double a,b,c,xopt,eps,fx, xmin[50];
	int i,j,itmax = 100, nmin, iflag;
	double f(),df();
	eps = 1e-10;
	nmin = 0;
	printf("Gold Serch:\n");
	for(i=1; i<50; i++)
	{
		a = i;
		b = i+1;
		brake(&a,&b,&c,f);
		fx = goldsch(a,b,c,f,&xopt,eps,itmax);
		if(nmin == 0)
		{
			xmin[0] = xopt;
			nmin++;
			printf("num%d  x=%7.5f  f=%7.5f df=%7.5f\n", nmin,xopt,f(xopt),df(xopt));
		}
		else
		{
			iflag = 0;
			for(j=0; j<nmin; j++)                           /* Ѱ���Ƿ��Ѿ�����ͬ�ļ�Сֵ*/
			if(fabs(xopt-xmin[j]) < 0.01*xopt)
				iflag = 1;
			if(iflag==0)
			{
				xmin[nmin++] = xopt;
				printf("num%d  x=%7.5f  f=%7.5f df=%7.5f\n", nmin,xopt,f(xopt),df(xopt));
			}
		}
	}	
}

double f(double x)
{
	return bsl1(0,x);
}
double df(double x)
{
	return -bsl1(1,x);
}
