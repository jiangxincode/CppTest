#include <stdio.h>
#include "hemt.c"
#include "gasi.c"
static double f1(double);
int main8inf30()
{
    double z;
    printf("Hermite:\n");                      /* ��������-��˹�����*/
    z = hemt(f1);
    printf("t=%2.8f\n",z);
    printf("Gauss:\n");                        /* ����Ӧ��˹�����*/
    z = gasi(-1.0e35,1.0e35,1.0e-9,10,f1);
    printf("t=%2.8f\n",z);
    return 0;
}

static double f1(x)                                  /* ��������*/
double x;
{
    double y;
    y=x*x*x*x*exp(-x*x);
    return(y);
}
