#include <stdio.h>
#include <math.h>

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
    int i=0;

    while(i<10000&&fanxushu(n)!=n)
    {
        i++;
        n=n+fanxushu(n);
    }

    return i;

    if(i>10000)
    {
        return -1;
    }
}
int main()
{
    int c;
    long b,a;
    scanf("%11ld",&a);
    c=f1098(a,&b);
    printf("%11ld  %11d ",b,c);
    return 0;
}


