#include <stdio.h>
#include <math.h> // for fabs
#include <stdlib.h> //for abs

/**
 * 输入一个浮点数，计算其绝对值
 */
int main1034()
{
    double a;
    scanf("%20lf",&a);

    if(a>0)
        printf("sign:+\n");
    else
        printf("sign:-\n");

    printf("%d, %lf\n",abs((int)a), fabs(a));
    return 0;
}
