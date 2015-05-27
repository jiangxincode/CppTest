#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * ��������c_comp_power.c
 * ���������������ĳ���
 * ���������a�������Ľṹ�壩
 *            n��ָ����
 *            c���������Ľṹ�壩
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */

int c_comp_power(struct c_comp *a,struct c_comp *c,int n)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_power)The c_comp pointer is NULL!\n");
        return(0);
    }

    double theta = atan2(a->imz,a->rmz);
    double R = sqrt(a->rmz*a->rmz + a->imz*a->imz);

    theta = n*theta;
    R = pow(R,n);

    c->rmz = R*cos(theta);
    c->imz = R*sin(theta);

    return(1);
}
