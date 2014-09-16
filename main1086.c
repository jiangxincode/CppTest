#include <stdio.h>
#include <math.h>
#include <conio.h>
double f(double x)
{
    return exp(3*x)+pow(x,7);
}
double trapezoid(double x)
{
    long n,i;
    double a=1,b=3,h,s;
    scanf("%ld",&n);
    h=(b-a)/n;
    s=(f(a)-f(b))/2;
    x=a;

    for(i=1; i<n; i++)
    {
        x+=h;
        s+=f(x);
    }

    printf("s=%f",s*h);
}
double rectangle(double x)
{
    long n,i;
    double a=1,b=3,h,s=0;
    scanf("%ld",&n);
    h=(b-a)/n;
    x=a;

    for(i=1; i<n; i++)
    {
        x+=h;
        s+=f(x);
    }

    printf("s=%f",s*h);
}
double simpson(double x)
{
    long n,i;
    double a=1,b=3,h,s,p=0,q=0;
    scanf("%ld",&n);
    h=(b-a)/(2*n);

    for(i=1; i<=n; i++)
    {
        p+=2*f(a+(2*i)*h);
        q+=f(a+2*i*h);
    }

    s=(b-a)/2*(((f(a)+f(b))/2)+p+q);
    printf("s=%f",s);
}
int main1086()
{
    char c;
    int t=1;
    double x,y;
    printf("x=");
    scanf("%lf",&x);

    while(t)
    {
        printf("1:trapezoid\n2:rectangle\n3:simpson\n4:exit");

        switch(c=getch())
        {
        case'1':
            y=trapezoid(x);
            break;

        case'2':
            y=rectangle(x);
            break;

        case'3':
            y=simpson(x);
            break;

        case'4':
            t=0;
            break;

        default:
            printf("wrong commend!Input again!");
        }

        printf("x=%f,y=%f",x,y);
    }
}
