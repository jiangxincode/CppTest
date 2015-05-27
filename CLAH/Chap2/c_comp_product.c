#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * ��������c_comp_product.c
 * ���������������ĳ˷�
 * ���������a1����һ������a�Ľṹ�壩
 *            a2���ڶ�������b�Ľṹ�壩
 *            c���������Ľṹ�壩
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */
int c_comp_product(struct c_comp *a1,struct c_comp *a2,struct c_comp *c)
{
    if(a1 == NULL || a2 == NULL || c == NULL)
    {
        printf("(c_comp_product)The c_comp pointer is NULL!\n");
        return(0);
    }
    double p = (a1->rmz)*(a2->rmz);
    double q = (a1->imz)*(a2->imz);
    double s = (a1->rmz + a1->imz)*(a2->rmz + a2->imz);
    c->rmz = p - q;
    c->imz = s - p - q;
    return(1);
}
