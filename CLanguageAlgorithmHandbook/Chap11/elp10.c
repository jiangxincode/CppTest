#include "stdio.h"
#include "RF.c"
main()
{
	int i;
    double f,sf,cf,y,k;
    for(i=0; i<=10; i++)
      { 
		f=i*3.1415926/10.0;                           /* ����phi*/
		sf = sin(f);                         
		cf = cos(f);
        k=0.5;
		y = sf*RF(cf*cf,(1.0+k*sf)*(1.0-k*sf),1.0);   /* ���ú�����ֵ����ӡ���*/
        printf("F1(%3.2f, %6.5f)=%6.5f     ",k,f,y);
        k=1.0; 
		y = sf*RF(cf*cf,(1.0+k*sf)*(1.0-k*sf),1.0);  /* ���ú�����ֵ����ӡ���*/
        printf("F1(%3.2f, %6.5f)=%6.5f\n",k,f,y);
      }
}
