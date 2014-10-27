#include <stdio.h>
int main1033()
{
    unsigned int a,b,n,mode;
    scanf("%10u",&a);
    n=16;
    b=a;
    mode=0x8000;
    printf("%u in binary is :",a);

    while(n>0)
    {
        printf("%d",b/mode);
        b=b%mode;
        mode=mode/2;
        n=n-1;
    }

    return 0;
}
