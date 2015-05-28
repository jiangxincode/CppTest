#include <stdio.h>
#include <math.h>
#include <string.h>
/*
实现精确计算浮点数的幂,比如求95.123^12的精确值:
548815620517731830194541.899025343415715973535967221869852721
*/
void jx_float_exp(char *str,int n)
{
    char a[10000];
    long int b[10000];
    int k,h,m,i,j,z,g,t,q;
    long int c=0;
    strcpy(a,str);

    for(i=0; a[i]; i++)
        if(a[i]=='.')
        {
            k=i;
        }

    m=i-k-1;

    for(i=k; i<k+m; i++)  //95.123>>95123
    {
        a[i]=a[i+1];
    }

    h=i;//h代表总的位数

    for(i=0; i<h; i++) //转换成long int
    {
        b[i]=a[i]-48;
    }

    for(i=0; i<h; i++) //将b数组的各位数字组成一个long int整数
    {
        c=c*10+b[i];
    }

    for(i=0; i<h/2; i++) //将b[]反转
    {
        t=b[i];
        b[i]=b[h-1-i];
        b[h-1-i]=t;
    }

    for(int e=1; e<n; e++)
    {
        for(i=0; i<h; i++)
        {
            b[i]=b[i]*c;
        }

        for(j=0; j<h-1; j++)
            if(b[j]>=10)
            {
                t=b[j];
                b[j]=t%10;
                b[j+1]+=t/10;
            }

        if(b[h-1]>=10)
        {
            t=b[h-1];
            q=b[h-1];
            z=1;

            while(t>=10)
            {
                t=t/10;
                z++;
            }

            g=z;

            while(z>=1)
            {
                b[h+g-z-1]=q/(int)(pow(10,(g-z)))%10;
                z--;
            }

            h=h+g-1;
        }
    }

    if(h<m*n) //m代表小数的位数，n代表幂次
    {
        printf(".");

        for(j=m*n-1; j>h-1; j--)
        {
            printf("0");
        }

        for(j=0; ; j++)
        {
            if(b[j]!=0)
            {
                break;
            }
        }

        for(i=h-1; i>=j; i--)
        {
            printf("%ld",b[i]);
        }
    }

    if(h==m*n)
    {
        for(j=0; ; j++)
            if(b[j]!=0)
            {
                break;
            }

        printf(".");

        for(i=h-1; i>=j; i--)
        {
            printf("%ld",b[i]);
        }
    }

    if(h>m*n)
    {
        for(j=0; ; j++)
            if(b[j]!=0)
            {
                break;
            }

        if(j<m*n-1&&b[h-1]==0)
        {
            printf(".");

            for(i=m*n-1; i>=j; i--)
            {
                printf("%ld",b[i]);
            }
        }

        if(j<=m*n-1&&b[h-1]!=0)
        {
            for(i=h-1; i>=m*n; i--)
            {
                printf("%ld",b[i]);
            }

            printf(".");

            for(i=m*n-1; i>=j; i--)
            {
                printf("%ld",b[i]);
            }
        }

        if(j>=m*n)
        {
            for(i=h-1; i>=m*n; i--)
            {
                printf("%ld",b[i]);
            }
        }
    }
}

/** \cond */
int main0003()
{
    jx_float_exp("95.123",12);
    return 0;
}
/** \endcond */
