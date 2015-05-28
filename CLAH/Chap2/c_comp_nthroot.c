#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c_comp.h"

/**
 * ��������c_comp_nthroot.c
 * ����������������n�η���
 * ���������a����֪������
 *            n��n�η�����
 *            c���������Ľṹ�壬��һ�����飬��n����
 * ����ֵ��0��ʧ�ܣ���1���ɹ���
 */
int c_comp_nthroot(struct c_comp *a,struct c_comp *c,int n)
{
    if(a == NULL || c == NULL)
    {
        printf("(c_comp_nthroot)The c_comp pointer is NULL!\n");
        return(0);
    }

    double theta = atan2(a->imz,a->rmz);
    double R = sqrt(a->rmz*a->rmz + a->imz*a->imz);
    R = pow(R,1.0/n);

    for(int i=0; i<n; i++)
    {
        c[i].rmz = R*cos((theta+2*i*PI)/n);
        c[i].imz = R*sin((theta+2*i*PI)/n);
    }

    return(1);
}
