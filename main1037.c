#include <stdio.h>
#include <math.h>
int main1037()
{
    float a,b,c,s,S;
    scanf("%f,%f,%f",&a,&b,&c);

    if(a+b>c&&a+c>b&&b+c>a)
    {
        s=(a+b+c)/2;
        S=sqrt(s*(s-a)*(s-b)*(s-c));
        printf("S=%f",S);
    }
    else
        printf("error");
    return 0;
}
