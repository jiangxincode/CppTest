#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * ��������c_comp_pow.c
 * ��������������ָ��
 * ���������a������Ľṹ�壩
 *            c���������Ľṹ�壩
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */
int c_comp_exp(struct c_comp *a,struct c_comp *c)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_exp)The c_comp pointer is NULL!\n");
        return(0);
    }

    double R = exp(a->rmz);
    c->rmz = R*cos(a->imz);
    c->imz = R*sin(a->imz);
    return(1);
}
