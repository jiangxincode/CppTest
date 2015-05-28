#include "something.h"

#define EPS 1.0e-6                    /* ʹ�ò���ȫ����������Ҫ������*/

/**
 * �� �� ����studf
 * �������������ѧ���ֲ�������ֵ
 * ���������x �Ա���x��ֵ��
 *           n �Ա���n��ֵ
 * �� �� ֵ��ѧ���ֲ�������ֵ
 */
double studf(double x,int n)
{
    double t;
    t = 1.0-beta2(n/2.0,0.5,n/(n+x*x),EPS);
    return(t);
}
