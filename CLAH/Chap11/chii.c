#include <stdio.h>
#include <math.h>

#include "something.h"

#define EPS 1.0e-6                    /* ʹ�ò���ȫ٤������Ҫ������*/
#define DMIN 1.0e-30

/**
 * �� �� ����chii
 * ������������⿨���ֲ�������ֵ
 * ���������x �Ա���x��ֵ��
 *            n ����
 * �� �� ֵ�������ֲ�������ֵ
 */
double chii(double x,int n)
{
    double t;
    if(x<0)                             /* ��x<0�����ܼ���*/
    {
        printf("negative x\n");
        return(0.0);
    }
    t = gamm2(n/2.0,x/2.0,EPS,DMIN);    /* ���ò���ȫ٤������ֵ*/
    return(t);
}
