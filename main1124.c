/*
Լɪ�����⣺
n���ˣ����1 ~ n��Χ��һȦ, �ӵ�һ���˿�ʼ˳��������1����m, ����m���˳���,�ӳ��е���һ���˿�ʼ���±���������m�����ֳ��С�
����ظ�ֱ�������˳���Ϊֹ���ʣ������е����Ǽ��ţ�
���Ҫ��
1. ��д����void  joseph(int n,int m,int x[])ģ��Լɪ�����ⱨ�����̣������γ��е������˱�Ű�����˳�����α��浽xָ���һά�����С�
2. ��дmain������ ����һά����c����������������(����n��m)�ֱ��ͱ���a��b���棬�ñ���a��b������c��ʵ�ε���joseph���������c���������ݡ�
�������ݼ�������:
    �� n=10,m=3ʱ���Ϊ��
    3    6    9    2    7    1    8    5    10    4 �����γ��е���Ա��ţ�
*/
#include<stdio.h>
void joseph(int n,int m,int x[])
{
    int a[100],i,*p,c=0,j=0;

    /*��a[]�е������и�ֵ*/
    for(i=0; i<n; i++) a[i]=i+1;

    p=a;

    while(*p!=0)
    {
        for(i=1; i<=m; i++)
        {
            if(i==m)
            {
                x[j++]=*p;
                *p=0;
                c++;
            }

            do
            {
                p++;

                if(p>a+n-1) p=a;

                if(c==n)
                    break;
            }
            while(*p==0);
        }
    }
}
main1124()
{
    int a[100],n,m,i;
    printf("input the number of persons");
    scanf("%d",&n);
    printf("input the number of counter:");
    scanf("%d",&m);
    joseph(n,m,a);

    for(i=0; i<n; i++)
        printf("%d ",a[i]);
}

