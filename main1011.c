#include <stdio.h>
#include<math.h>

int main10111(void)
{
    printf("\n");
    printf("***\n");
    printf("* *\n");
    printf("* *\n");
    printf("* *\n");
    printf("***\n");
    return 0;
}

int main10112(void) //��ӡ�˷���
{
    int row,col,result;
    for(row=1; row<10; row++)
    {
        for(col=1; col<=row; col++)
        {
            result=row*col;
            printf("%d*%d=%-5d",row,col,result);
        }
        printf("\n");
    }
    return 0;
}

int main10113(void)
{
    int a,b,c;
    scanf("%d,%d",&a,&b);
    c=a*b;
    printf("%d*%d=%d",a,b,c);
    return 0;
}

float main10114()
{
    float a,b;
    scanf("%f",&a);
    b=sqrt(a);
    printf("%f��ƽ�����ǣ�%f",a,b);
    return 0;
}

int main10115()
{
    float a,b,c,d;
    scanf("%f,%f,%f",&a,&b,&c);

    if(a>b)
        d=a;
    else
        d=b;

    if(d>c)
        printf("%f",d);
    else
        printf("%f",c);
    return 0;
}

int main10117()
{
    int i,s=1,n;
    scanf("%d",&n);

    for(i=1; i<=n; i++)
        s=s*i;

    printf("%d=%d!",s,n);
    return 0;
}

int main1011()
{
    main10112();
    return 0;
}
