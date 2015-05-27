#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * ��������c_comp_sin.c
 * ��������������������
 * ���������a������Ľṹ�壩
 *            c���������Ľṹ�壩
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */
int c_comp_sin(struct c_comp *a,struct c_comp *c)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_sin)The c_comp pointer is NULL!\n");
        return(0);
    }

    double tmp1 = exp(a->imz);
    double tmp2 = exp(-a->imz);
    c->rmz = sin(a->rmz)*(tmp1+tmp2)/2;
    c->imz = cos(a->rmz)*(tmp1-tmp2)/2;

    return(1);
}
