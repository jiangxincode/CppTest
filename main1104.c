/**
 * ���ӷ�������
 */

#include <stdio.h>
#include <math.h>

int distribute(int n,int count)
{
    if(count>5)
    {
        return 1;
    }
    else if((count<=5)&&(n%5!=1))
    {
        return 0;
    }
    else
    {
        return distribute(n/5*4,count+1);
    }
}
int main1104()
{
    int n; //��������
    int count=1; //���ӵ����

    for(n=1;; n++)
    {
        if(distribute(n,count)==1)
        {
            printf("%d",n);
            break;
        }
    }

    return 0;
}



