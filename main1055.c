#include<stdio.h>
#include<math.h>
int main1055()
{
    int a,b,c,d,*p;
    scanf("%d",&a);
    p=&a;

    if(a<1000&&a>99)
    {
        b=a/100;
        d=a%10;
        c=(a-100*b-d)/10;

        if(a==(pow(b,3)+pow(c,3)+pow(d,3)))
            printf("%d is a Armstrong number",*p);
        else
            printf("%d is not a Armstrong number",*p);
    }
    else
        printf("Please input another int number");
}




