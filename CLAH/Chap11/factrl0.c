#include "stdio.h"
#include "math.h"
#include "something.h" /* ��Ҫ٤������֧��*/
#include "factrl.c"
void main11factrl0()
{
  int n;
  double x;
  printf("factorial(x): \n");
  for(n=18; n<25; n++)
  {
    x = factrl(n);                                /* ���ú�����⣬����ӡ���*/
    printf("n=%d, factorial(n)=%e\n",n,x);
  }
  getchar();
}
