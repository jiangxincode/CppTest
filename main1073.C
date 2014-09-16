#include<stdio.h>
#include<math.h>
int main1073()
{
    double x,eps,s=1,term=1,hx,g,f;
    int n;
    printf("x=");
    scanf("%lf",&x);
    printf("eps=");
    scanf("%lf",&eps);
    hx=exp(-x);
    g=(x*x+1+(1/x))*hx-(1/x);

    while(fabs(s)>eps)
    {
        term=(-1)*term*(x/(n+1));
        s=s*term*n*n*n;
        f=f+s;
        n++;
    }

    if(fabs(f-g)/(fabs(f)+fabs(g))<1e-6)
        printf("right x=%f f=%.5f g=%.5f",x,f,g);
    else
        printf("wrong x=%f f=%.5f g=%.5f",x,f,g);

    return 0;
}
