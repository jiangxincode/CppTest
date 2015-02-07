#include<stdio.h>

int main1047()
{
    int n1,n2,n3,n=3,a;
    printf("input numbers:");
    scanf("%11d%11d%11d",&n1,&n2,&a);
    printf("%d %d ",n1,n2);

    while(n<=a)
    {
        if(n%2==0)
            n3=n1-n2;
        else
            n3=n1+n2;

        printf("%d ",n3);
        n1=n2;
        n2=n3;
        n++;
    }

    return 0;
}



