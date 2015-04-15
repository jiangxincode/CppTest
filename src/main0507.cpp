#include <stdio.h>

static long A(long m, long n)
{
    if(m == 0)
    {
        return 2*n;
    }
    else if((m>=1) && (n==0))
    {
        return 0;
    }
    else if((m>=1) && (n==1))
    {
        return 2;
    }
    else
    {
        return A(m-1, A(m, n-1));
    }
}

int main0507()
{
    printf("%ld\n", A(1,0));
    printf("%ld\n", A(0,1));
    printf("%ld\n", A(1,1));
    printf("%ld\n", A(2,2));
    printf("%ld\n", A(2,3));
    printf("%ld\n", A(3,3));
    printf("%ld\n", A(3,4));
    return 0;
}

