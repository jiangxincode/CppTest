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


int qiusushu(int n)
{
    for(n=n+1;; n++)
        if(prime(n))
        {
            return n;
        }
        else
        {
            continue;
        }
}
int main(void)
{
    int a[4][4]= {{3,6,4,17},{8,5,9,10},{9,19,7,20},{4,14,21,23}},
    b[4][4],count=0,i,j;

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            b[i][j]=a[i][j];
        }

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            if(i>=j)
            {
                if(prime(b[i][j]))
                {
                    b[i][j]=qiusushu(b[i][j]);
                    count++;
                }
                else
                {
                    b[i][j]=0;
                }
            }

    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            printf("%4d",b[i][j]);
        }

        printf("\n");
    }

    printf("count=%d\n",count);
    return 0;
}



