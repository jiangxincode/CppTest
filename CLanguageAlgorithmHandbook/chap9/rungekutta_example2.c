/*======================================================
//����������3��rungekutta������΢�ַ�����ĳ�ֵ���������
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "rungekuttainvh.c"
#include "rungekuttavh.c"
#include "gillvh.c"


void main()
{
    double h=0.01,a=0,eps=0.000000001;
    int n=3,m=10,i,j;
    double *y;                       /* ������к���ֵ��ָ��*/
    void f(double*,double*,double);
    y=(double*)malloc(n*(m+1)*sizeof(double));
    for(i=0;i<n*(m+1);i++)                    /* ��ʼ��*/
	   y[i]=0.0;
    y[0]=-1.0;                                /* ��ֵ*/
    y[1]=0.0;
    y[2]=1.0;
	if(rungekuttainvh(y,n,f,h,m,a))
    {
		printf("��������������㷨��ֵ\n");
        for(i=0;i<=m;i++)
        {
            printf("x=%1.2f ",a+h*i);
            for(j=0;j<n;j++)
				printf("y[%d]=%1.9f  ",j,y[3*i+j]);   /* ���*/
			printf("\n");
        }
    }
    else
    printf("failed!\n");

    if(rungekuttavh(y,n,f,h,m,a,eps))
    {
		printf("�䲽������-�����㷨��ֵ\n");
        for(i=0;i<=m;i++)
        {
            printf("x=%1.2f ",a+h*i);
            for(j=0;j<n;j++)
				printf("y[%d]=%1.9f  ",j,y[3*i+j]);    /* ���*/
			printf("\n");
        }
    }
    else
    printf("failed!\n");

	if(gillvh(y,n,f,h,m,a,eps))
    {
		printf("�䲽�������㷨��ֵ\n");
        for(i=0;i<=m;i++)
        {
            printf("x=%1.2f ",a+h*i);
            for(j=0;j<n;j++)
				printf("y[%d]=%1.9f  ",j,y[3*i+j]);    /* ���*/
			printf("\n");
        }
    }
    else
    printf("failed!\n");
	free(y);
}
 
void f(y,F,x)
double *y,*F,x;
{
    F[0]=5*x+1;
    F[1]=x+y[0];
    F[2]=-1*y[2];
    return;
}





