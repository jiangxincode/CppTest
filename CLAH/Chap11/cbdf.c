#include "something.h"

#define EPS 1.0e-6                    /* ʹ�ò���ȫ����������Ҫ������*/

/**
 * �� �� ����cbdf
 * ��������������ۻ�����ʽ�ֲ�������ֵ
 * ���������x �Ա���x��ֵ��
 *           n �Ա���n��ֵ
 * �� �� ֵ���ۻ�����ʽ�ֲ�������ֵ
 */
double cbdf(double p,int n,int k)
{
    double t;
    t = beta2((double)k,n+1.0-k,p,EPS);
    return(t);
}
