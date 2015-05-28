#include <stdio.h>
#include <stdlib.h>

#include "c_comp.h"

/**
 * ��������c_comp_plus.c
 * ���������������ļӷ�
 * ���������a1����һ������a�Ľṹ�壩
 *            a2���ڶ�������b�Ľṹ�壩
 *            c���������Ľṹ�壩
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */
int c_comp_plus(struct c_comp *a1,struct c_comp *a2,struct c_comp *c)
{
    if(a1 == NULL || a2 == NULL || c == NULL)
    {
        printf("(c_comp_plus)The c_comp pointer is NULL!\n");
        return(0);
    }

    c->rmz = a1->rmz + a2->rmz;
    c->imz = a1->imz + a2->imz;
    return(1);
}
