#include<stdio.h>
#include<math.h>
int main1053()
{
    int x,a,b,c,t,max,min,s=1;
    printf("input a number:");
    scanf("%d",&x);

    if(x<100||x>1000)
        printf("you can't do that");
    else
    {
        do
        {
            a=x/100%10;
            b=x/10%10;
            c=x/1%10;

            if(a<=b)
            {
                t=a;
                a=b;
                b=t;
            }

            if(a<=c)
            {
                t=a;
                a=c;
                c=t;
            }

            if(b<=c)
            {
                t=b;
                b=c;
                c=t;
            }

            max=a*100+b*10+c;
            min=c*100+b*10+a;
            s++;
            printf("%d ",x);
            x=max-min;

            if(x==495)
            {
                printf("%d",x);
                break;
            }
        }
        while(x%111!=0||s<8);
    }

    return 0;
}










