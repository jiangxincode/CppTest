#include<stdio.h>
#include<math.h>

int main1061()
{
    unsigned int a,s,n=2;
    printf("Please input a int number;\n");
    scanf("%d",&a);

    if(a>=100)
        printf("Please input another smaller int number:\n");
    else
    {
        s=a;

        while(n<=a)
        {
            if(s%n==0)
            {
                printf("%d\n",n);
                s=s/n;
            }
            else
                n++;
        }
    }

    return 0;
}




