/*
���Ҫ��
1.��д����void movesort(int x[],int n)����xָ�������ǰn��Ԫ�������´���:
(1)�����е����������Ƶ�����ǰ�벿�ִ洢������ż���Ƶ������벿�ִ洢��
(2)������ǰ�벿�����������������򣬺�벿������ż����������
2.��дmain����������һά����a���ò������ݳ�ʼ��������movesort������a����ȫ��Ԫ�������ݴ���
��������a������ȫ�����ݡ�
�������ݼ�������:
   ����ǰa���飺 1  2  3  4  5  6
   �����a���飺 5  3  1  2  4  6
*/
#include<stdio.h>
#include<math.h>
void movesort(int x[],int n)
{
    int i,j,t,k,count,flag,a[3]= {0},b[3]= {0};

    /*������x[6]�е������ŵ�a[3]��,ż���ŵ�b[3]��*/
    for(i=0,k=0,count=0; i<n; i++)
    {
        if(x[i]%2!=0)
        {
            a[k]=x[i];
            k++;
        }
        else
        {
            b[count]=x[i];
            count++;
        }
    }

    /*������a[3]�е�������������*/
    for(i=0; i<k-1; i++)
    {
        flag=1;

        for(j=0; j<k-i-1; j++)
            if(a[j]<a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                flag=0;
            }

        if(flag)
            break;
    }

    /*������a[3]�е����������*/
    for(i=0; i<k; i++)
        printf("%d ",a[i]);

    /*������b[3]�е�������������*/
    for(i=0; i<count-1; i++)
    {
        flag=1;

        for(j=0; j<count-i-1; j++)
            if(b[i]>b[i+1])
            {
                t=b[i];
                b[i]=b[i+1];
                b[i+1]=t;
                flag=0;
            }

        if(flag)
            break;
    }

    /*������b[3]�е����������*/
    for(i=0; i<3; i++)
        printf("%d ",b[i]);

    printf("\n");
}
int main1123(void)
{
    int x[6]= {1,2,3,4,5,6},i,n=6;

    for(i=0; i<6; i++)
        printf("%d ",x[i]);

    printf("\n");
    movesort(x,n);
}








