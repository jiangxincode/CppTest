#include <stdio.h>
#include <math.h>

static double f(double x)
{
    return exp(3*x)+pow(x,7);
}
double trapezoid(double x)
{
    long n,i;
    double a=1,b=3,h,s;
    scanf("%11ld",&n);
    h=(b-a)/n;
    s=(f(a)-f(b))/2;
    x=a;

    for(i=1; i<n; i++)
    {
        x+=h;
        s+=f(x);
    }

    printf("s=%f",s*h);
    return 0;
}
double rectangle(double x)
{
    long n,i;
    double a=1,b=3,h,s=0;
    scanf("%11ld",&n);
    h=(b-a)/n;
    x=a;

    for(i=1; i<n; i++)
    {
        x+=h;
        s+=f(x);
    }

    printf("s=%f",s*h);
    return 0;
}
double simpson(double x)
{
    long n,i;
    double a=1,b=3,h,s,p=0,q=0;
    scanf("%11ld",&n);
    h=(b-a)/(2*n);

    for(i=1; i<=n; i++)
    {
        p+=2*f(a+(2*i)*h);
        q+=f(a+2*i*h);
    }

    s=(b-a)/2*(((f(a)+f(b))/2)+p+q);
    printf("s=%f",s);
    return 0;
}
int main1086()
{
    int t=1;
    double x,y;
    printf("x=");
    scanf("%20lf",&x);

    while(t)
    {
        printf("1:trapezoid\n2:rectangle\n3:simpson\n4:exit");
        char c=getchar();

        switch(c)
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

    return 0;
}
