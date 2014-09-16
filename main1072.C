#include<stdio.h>
#include<math.h>
int main1072()
{
    double low,s,pi;
    int n;
    s=0;
    pi=2;
    low=0;

    while(s<=1)
    {
        low=sqrt(2+low);
        s=2/low;
        pi=pi*s;
    }

    printf("%.5f",pi);
}
