#include<stdio.h>
int main1048()
{
    int i=100,n1,n2,n3,c,b;

    while(i<=999)
    {
        if(i%37==0)
        {
            n1=i/100;
            n2=(i-n1*100)/10;
            n3=i-n1*100-n2*10;
            c=n2*100+n3*10+n1;
            b=n3*100+n1*10+n2;

            if(c%37==0&&b%37==0)
            {
                printf("%d ",i);
            }
            else
            {
                printf("wrong");
            }
        }

        i++;
    }

    return 0;
}




