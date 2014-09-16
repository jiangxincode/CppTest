#include<stdio.h>
#include<math.h>
#include<conio.h>
int fanxushu(int p)
{
    int d;

    for(d=0; p>0; p=p/10)
    {
        d=d*10+p%10;
    }

    return d;
}
int f1098(long n,long *hw)
{
    int i=0,m;

    while(i<10000&&fanxushu(n)!=n)
    {
        i++;
        m=n+fanxushu(n);
        n=m;
    }

    return i;

    if(i>10000)
        return -1;
}
main1098()
{
    int c;
    long b,a;
    scanf("%ld",&a);
    c=f1098(a,&b);
    printf("%ld  %d ",b,c);
    getch();
}


