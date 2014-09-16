#include <stdio.h>
#include <math.h>

int main1036()
{
    float a,b,c,d,e,f,g;
    scanf("%f,%f",&a,&b);
    c= sin(a);
    d= cos(b);
    e=fabs(a);
    f=exp(a);
    g=pow(a,b);
    printf("sin%d=%l\ncos%d=%l\n|%d|=%l/ne^%d=%l/n%d^%d=%l",a,c,b,d,a,e,a,f,a,b,g);
    return 0;
}
