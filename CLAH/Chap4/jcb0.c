#include <stdio.h>
#include "jcb2.c"
#include "jcb1.c"
int main4jcb0()
{
    int i,itmax=60;
    double eps=1e-7, u[5],u2[5];
    double a[5][5]= { {1.0,6.0,-3.0,-1.0,7.0},
        {6.0,-15.0,18.0,5.0,4.0},
        {-3.0,18.0,9.0,15.0,20.0},
        {-1.0,5.0,15.0,30.0,-6.0},
        {7.0,4.0,20.0,-6.0,6.0}
    };
    double b[5][5]= { {1.0,6.0,-3.0,-1.0,7.0},
        {6.0,-15.0,18.0,5.0,4.0},
        {-3.0,18.0,9.0,15.0,20.0},
        {-1.0,5.0,15.0,30.0,-6.0},
        {7.0,4.0,20.0,-6.0,6.0}
    };
    i=jcb1(a,5,u,eps,100);

    if(i>0)
    {
        printf("jcb1  eigvalue:\n");

        for(i=0; i<5; i++)
        {
            printf("%9.6f \n",u[i]);
        }
    }

    i=jcb2(b,5,u2,eps,100);

    if(i>0)
    {
        printf("jcb2 eigvalue:\n");

        for(i=0; i<5; i++)
        {
            printf("%9.6f \n",u[i]);
        }
    }

    return 0;
}
