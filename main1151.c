#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "jiangxin.h"
int *stoi(char*str)
{
	int a[100]={0},i;
	for(i=0;a[i]!=0;i++)
	{
		a[i]=str[i]-32;

	}
	return a;
}

int main1151(int argc,char*argv[])
{
	int a[100],i;
	for(i=0;i<argc;i++)
	{
		a[i]=stoi(argv);
		printf("%d",a[i]);
	}
	printf("\n");
	for(i=0;a[i]!=0;i++)
	{
		if(prime(i))
			printf("%d",a[i]);
			printf("\n");
	}
	for(i=0;a[i]!=0;i++)
	{
		if(!prime(i))
			printf("%d",a[i]);
			printf("\n");
	}
}
