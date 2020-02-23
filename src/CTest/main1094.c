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


int  guest(int t)
{
    int p;

    for(p=2; p<(t/2); p++)
    {
        if(prime(p)==1&&prime(t-p)==1&&p!=(t-p))
        {
            printf("%d=%d+%d   ",t,p,t-p);
        }
    }

    return 0;
}
int main()
{
    int d;

    for(d=6; d<51; d=d+2)
    {
        if(guest(d)!=0)
        {
            printf("%d  ",guest(d));
        }
    }

    return 0;
}
