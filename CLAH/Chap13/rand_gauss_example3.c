#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "randgsab.c"
void main13rand_gauss_example3()
{
    double a,b,G;
	int i;
    a=3.0;                          /* ��ֵ*/
    b=2.2;                          /* ����*/
	for(i=0; i<5; i++)
	{
		G = randgsab(a,b);          /* ���ú���*/
		printf("%5.4f ",G);            /* ������*/
	}
	printf("\n");
}
