#include <stdio.h>
#include <math.h> // for fabs
#include <stdlib.h> //for abs

/**
 * ����һ�������������������ֵ
 */
int main1034()
{
    double a;
    scanf("%lf",&a);

    if(a>0)
        printf("sign:+\n");
    else
        printf("sign:-\n");

    abs((int)a); //���������͸������ľ���ֵ
    printf("%d, %lf\n",abs((int)a), fabs(a));
    return 0;
}
