#include <stdio.h>
#include <math.h>

int main1034()
{
    double a;
    scanf("Input annumber %ld",&a);

    if(a==0)
        printf("error,please input another number:");
    else
    {
        if(a>0)
            printf("sign:+");
        else
            printf("sign:-");

        abs((int)a);
        printf("integral part:%d",a);
        fabs(a);
        printf("decimal fraction part :%d",a);
    }
    return 0;
}
