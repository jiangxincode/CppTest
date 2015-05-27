#include "stdio.h"
#include "stdlib.h"
#include "r_mdet.c"
#include "r_mrank.c"
#include "r_chdet.c"
void main()
{
    double a[4][4] = {{2.0,1.0,3.0,5.0},    /* ����A��B��C�ֱ𸳳�ֵ*/
      {2.0,2.0,-3.0,-1.0},
      {2.0,1.0,7.0,2.},
          {4.0,2.0,10.0,7.0}};
    double b[4][4] = {{2.0,2.0,-3.0,-1.0},
        {2.0,1.0,3.0,5.0},
            {2.0,1.0,7.0,2.},
            {1.,4.0,9.0,-2.0}};
    double c[4][4]={{14.0,7.0,6.0,1.0},
      {7.0,8.0,4.0,3.0},
      {6.0,4.0,9.0,5.0},
      {1.0,3.0,5.0,10.0}};
    double det,eps = 1e-10;                 /* ��ֵ������Ϊ1e-10*/
    int n;
    n = r_mrank(a,4,4,eps);                 /* �����A���Ⱥ�����ֵ����ӡ*/
    printf("rank(a) = %d\n", n);
    det = r_mdet(a, 4,eps);
    printf("det(a) = %2.5f\n", det);
    n = r_mrank(b,4,4,eps);                 /* �����B���Ⱥ�����ֵ����ӡ*/
    printf("rank(b) = %d\n", n);
    det = r_mdet(b, 4,eps);
    printf("det(b) = %2.5f\n", det);
    n = r_mrank(c,4,4,eps);                 /* ����������C���Ⱥ�����ֵ����ӡ*/
    printf("rank(c) = %d\n", n);
    det = r_chdet(c,4,eps);
    printf("det(c) = %2.5f\n", det);
}
