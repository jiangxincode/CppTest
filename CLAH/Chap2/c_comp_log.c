#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * ��������c_comp_log.c
 * ���������������Ķ���
 * ���������a������Ľṹ�壩
 *            c���������Ľṹ�壩
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */
int c_comp_log(struct c_comp *a,struct c_comp *c)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_log)The c_comp pointer is NULL!\n");
        return(0);
    }

    c->rmz = log(sqrt(a->rmz*a->rmz + a->imz*a->imz));
    c->imz = atan2(a->imz,a->rmz);
    return(1);
}
