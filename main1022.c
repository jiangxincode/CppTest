#include<stdio.h>
int main1022()
{
    int a,b,c,d,e,f;
    printf("input 2 interger");
    scanf("%11d%11d",&a,&b);
    c=a+b;
    d=a-b;
    e=a*b;

    if(b==0)
        printf("error!");
    else
        f=a*b;

    printf("%d+%d=%d,%d-%d=%d,%d*%d=%d,%d/%d=%d",a,b,c,a,b,d,a,b,e,a,b,f);
    return 0;
}
