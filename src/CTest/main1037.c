#include <stdio.h>
#include <math.h>
int main()
{
    float a,b,c;
    scanf("%20f%20f%20f",&a,&b,&c);

    if(a+b>c&&a+c>b&&b+c>a)
    {
        float s=(a+b+c)/2;
        printf("S=%f",sqrt(s*(s-a)*(s-b)*(s-c)));
    }
    else
    {
        printf("error");
    }

    return 0;
}
