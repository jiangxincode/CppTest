/*=============================================================
// �� �� ����c2p (a,n,y)
// ����������������ʽ��ϵ����ʾת��Ϊ���ʾ
// ���������a������ʽϵ������n��ϵ����������y��������ĵ�ֵ��
// �� �� ֵ���������֡�����ɹ��򷵻�1�����򷵻�0
//==============================================================*/
#include"stdio.h"
#include"math.h"
#include"c_comp.c"

int c2p(a,n,y)
int n;
struct c_comp *a,*y;
{
	int i,k,nn;
	int c2p0();
	k = log(n-0.5)/log(2.0)+1;        /* ���k��ʹ2^k>=n>2^(k-1) */ 
	nn = 1;
	for(i=0; i<k; i++)          	/* �ж�n�Ƿ���2�������ݣ����ǵĻ��˳�����*/
		nn = nn<<1;
	if(nn != n)
	{
		printf("n should be 2^k.\n");
		return(0);
	}
	k = c2p0(a,n,y);
	return(k);
}

int c2p0(a,n,y)
int n;
struct c_comp *a,*y;
{
  int i,j,k;
  struct c_comp xn,x,t;
  struct c_comp *a0,*a1,*y0,*y1;

  if(n==1)                   
  {			    /* ��ֻ��һ��ϵ��ʱ������ֵ�������ϵ��*/
    y[0].rmz = a[0].rmz;
    y[0].imz = a[0].imz;
    return(1);
  }
  
  k = n>>1;		    /* k��n��һ�룬������С��ģ������Ҫ����ռ��С*/
  a0 = (struct c_comp*)malloc(k*sizeof(struct c_comp));
  a1 = (struct c_comp*)malloc(k*sizeof(struct c_comp));
  y0 = (struct c_comp*)malloc(k*sizeof(struct c_comp));
  y1 = (struct c_comp*)malloc(k*sizeof(struct c_comp));
  if((a0==NULL)||(a1==NULL)||(y0==NULL)||(y1==NULL))
  {
    printf("(c2p0)memory alloc failed.\n");
    return(0);
  }
  for(i=0; i<k; i++) 			    /* ������ʽ�ֳ�����*/
  {
    j=2*i;
    a0[i].rmz = a[j].rmz;
    a0[i].imz = a[j].imz;
    a1[i].rmz = a[j+1].rmz;
    a1[i].imz = a[j+1].imz;
  }
  i = c2p0(a0,k,y0);			    /* �ݹ���ô˺���*/
  j = c2p0(a1,k,y1);
  if(i && j) 			            /* ���õ��������ֺ���ֵ�ۺ�����*/
  {
    xn.rmz = cos(2*PI/n);
    xn.imz = sin(2*PI/n);
    x.rmz = 1.0;
    x.imz = 0.0;
    for(i=0; i<k;i++)
    {
      c_comp_product(&x,&y1[i],&t); 			    /* һ��һ��������˺���ֵ���ۺ�*/
      c_comp_plus(&y0[i],&t,&y[i]);
      c_comp_sub(&y0[i],&t,&y[i+k]); 
      c_comp_product(&xn,&x,&x);    /* x��xn��ˣ��������x�У���k���ۺ�ʱ��x����xn^k*/
    }
  }
  free(y0);
  free(y1);
  free(a0);
  free(a1);
  return(1);
}
