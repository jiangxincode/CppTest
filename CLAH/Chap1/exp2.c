﻿#include <stdio.h>
#include <math.h>

int main1exp2()
{
    double x1,x2;
    x1 = (pow(10,18)+1 + sqrt((pow(10,18)+1)*(pow(10,18)+1) - 4*1*pow(10,18)))/2;
    x2 = (pow(10,18)+1 - sqrt((pow(10,18)+1)*(pow(10,18)+1) - 4*1*pow(10,18)))/2;
    printf("x1=%e\n",x1);
    printf("x2=%e\n",x2);
    return 0;
}
