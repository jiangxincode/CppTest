#include <stdio.h>
#include <math.h>

void fun(char op,double a,double b,double c,double d)
{
    if(op=='+')
    {
        printf("(%lf+%lf i)%c(%lf+%lf i)=(%lf+%lf i)\n",a,b,op,c,d,a+c,b+d);
    }

    if(op=='-')
    {
        printf("(%lf+%lf i)%c(%lf+%lf i)=(%lf+%lf i)\n",a,b,op,c,d,a-c,b-d);
    }

    if(op=='*')
    {
        printf("(%lf+%lf i)%c(%lf+%lf i)=(%lf+%lf i)\n",a,b,op,c,d,a*c,b*d);
    }
}
int main()
{
    double m,n,l,k;
    char p;
    printf("input a fushu :");
    scanf("%20lf%20lf%20lf%20lf%c",&m,&n,&l,&k,&p);
    fun(p,m,n,l,k);
    return 0;
}


