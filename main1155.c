/**
 * 教材实验14，第5题
 */
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    long id;
    char name[10];
    char sex[2];
} PS;

static int detele(PS *p1,int m,PS *p2,int n)
{
    int i,j,k,p;
    p=m;

    for(i=0; i<p; i++)
    {
        for(j=0; j<n; j++)
            if(p1[i].id==p2[j].id)
                break;

        if(j<n)
        {
            for(k=i; k<p-1; k++)
                p1[k]=p1[k+1];

            m--;
            i--;
        }
    }

    return m;
}
static int merge(PS *p1,int m,PS *p2,int n)
{
    int i,j,d;
    PS pp;
    d=m;

    for(i=0; i<n; i++)
    {
        for(j=0; j<d; j++)
            if(p2[i].id==p1[j].id)
                break;

        if(j==d)
        {
            p1[m]=p2[i];
            m++;
        }
    }

    for(i=0; i<m-1; i++)
        for(j=i+1; j<m; j++)
        {
            if(p1[i].id>p1[j].id)
            {
                pp=p1[i];
                p1[i]=p1[j];
                p1[j]=pp;
            }
        }

    return m;
}
static void sort(PS *p,int n)
{
    PS pp;
    int i,j;

    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
        {
            if((strcmp(p[i].sex,p[j].sex)>0)||
                    (strcmp(p[i].sex,p[j].sex)==0&&strcmp(p[i].name,p[j].name)>0))
            {
                pp=p[i];
                p[i]=p[j];
                p[j]=pp;
            }
        }
}
static void display(PS *p,int n)
{
    int i;

    for(i=0; i<n; i++)
    {
        printf("%3ld",p[i].id);
        printf("%6s",p[i].name);
        printf("%4s",p[i].sex);
        printf("\n");
    }
}
int main1155()
{
    int d,i,j;
    PS a[5]=
    {
        {101,"tom","m"},
        {103,"marry","f"},
        {104,"mark","m"},
        {105,"julia","f"},
        {106,"sara","f"}
    };
    PS b[2]=
    {
        {102,"mark","m"},
        {104,"mark","m"}
    };
    PS p[5];
    printf("a\n");
    display(a,5);
    printf("b\n");
    display(b,2);
    d=detele(a,5,b,2);

    for(j=0; j<d; j++)
        p[j]=a[j];

    printf("a\n");
    display(a,d);
    i=merge(a,detele(a,5,b,2),b,2);
    printf("b\n");
    display(a,i-1);
    sort(p,4);
    printf("a\n");
    display(p,4);
    return 0;
}













