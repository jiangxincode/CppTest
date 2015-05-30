#include<stdio.h>
void main0033()
{
    int a[10];
    int i,j,t,*p;

    for(p=a; p<a+10; p++)
    {
        scanf("%d",p);
    }

    p=a;

    for(i=0; i<10; i++)
    {
        for(j=i+1; j<10; j++)
        {
            if(*(p+i)>*(p+j))
            {
                t=*(p+i);
                *(p+i)=*(p+j);
                *(p+j)=t;
            }
        }
    }

    for(p=a; p<a+10; p++)
    {
        printf("%2d	",*p);
    }
}
