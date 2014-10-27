#include<stdio.h>
#include<math.h>

int main1054()
{
    int a,max,sum,n=1;
    float ave;
    printf("Input ten int number:\n");
    scanf("%11d",&a);
    max=a;
    sum=a;

    while(n<=9)
    {
        scanf("%11d",&a);

        if(a>max)
            max=a;

        sum=sum+a;
        n++;
    }

    ave=sum/10;
    printf("%d\n%.2f",max,ave);
    return 0;
}



