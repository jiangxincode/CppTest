#include <stdio.h>
#include <math.h>

/** \brief 判断一个正整数是否为素数
 *
 * \param int n 带判断的正整数
 * \return 0 不是素数
 *         1 是素数
 *
 */
int prime(int n)
{
    int flag = 0;
    int i = 0;

    if(n <= 1)
    {
        return 0;
    }

    for(i=2; i<n; i++)
    {
        if((n%i)==0)
        {
            flag++;
        }
    }

    if(flag == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main()
{
    int m,n,a;
    printf("Input two int numbers");
    scanf("%11d,%11d",&m,&n);

    for(a=m; a<=n-2; a++)
        if(prime(a)&&prime(a+2))
        {
            printf("(%d  %d)\n",a,a+2);
        }

    return 0;
}

