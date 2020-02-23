#include <stdio.h>
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


int countvalue(int aa[])
{
    int i,k=0;

    for(i=500; i<=800; i++)
        if(prime(i))
        {
            aa[k]=i;
            k++;
        }

    return k;
}
int main()
{
    int aa[150],cnt,k;
    cnt=countvalue(aa);

    for(k=0; k<cnt; k++)
        if(aa[k]!=0)
        {
            printf("%6d",aa[k]);

            if((k+1)%10==0)
            {
                printf("\n");
            }
        }

    return 0;
}


