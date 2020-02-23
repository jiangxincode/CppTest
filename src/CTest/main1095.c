#include <stdio.h>
#include <math.h>

int f1095(int n)
{
    int a,b,c;

    if(n<1000&&n>100)
    {
        a=n/100%10;
        b=n/10%10;
        c=n%10;

        if(a*a+b*b==c*c&&a!=0&&b!=0&&c!=0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(n>=1000&&n<10000)
    {
        a=n/1000%10;
        b=n/100%10;
        c=n%100;

        if(a*a+b*b==c*c&&a!=0&&b!=0&&c!=0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
int main()
{
    int i,m,n;
    printf("input two numbers 100<m<10000,100<n<10000,m<n");
    scanf("%11d%11d",&m,&n);

    for(i=m; i<=n; i++)
    {
        if(f1095(i))
        {
            printf("%d  ",i);
        }
    }

    return 0;
}












