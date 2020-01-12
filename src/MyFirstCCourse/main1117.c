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


int f1117(int a[],int n,int *x,int *y)
{
    int i,j;

    for(i=0; i<n-1; i++)
        for(j=1; j<n; j++)
            if(a[j]-a[i]==1898)
            {
                *x=i, *y=j;
                return 1;
            }

    return 0;
}

int main()
{
    int a[1000]= {0};
    int i,k=0,flag,m,n;

    for(i=7; i<2000; i+=2)
        if(prime(i))
        {
            a[k++]=i;
        }

    flag=f1117(a,k,&m,&n);

    if(flag)
    {
        printf("%d-%d=%d\n",a[n],a[m],a[n]-a[m]);
    }
    else
    {
        printf("not found!\n");
    }

    return 0;
}


