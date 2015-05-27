#include "math.h"
/*======================================================
// ��������tzi2
// ��������������Ӧ���������
// ���������a �������ޣ�b ��������,
//           n0 ��ʼ������
//           eps ����Ҫ��
//           h0 ��С����
//           f ָ�򱻻�������ָ��
// ����ֵ��  ���ֽ���ֵ
=========================================================*/
static double subtz(double x0,double x1,double y0,double y1,double h,double t,double eps,double h0,double (*f)(double));
double tzi2(double a,double b,int n0,double eps,double h0,double (*f)(double))
{
  int n,k;
  double z,h,t;
  double x0,x1,y0,y1;

  n = n0;                                  /* ��ʼ�Ļ�����*/
  h = (b-a)/n;                             /* ��ó�ʼ����*/
  z = 0.0;
  for(k=0; k<n; k++)
  {
    x0 = a+k*h;                            /* �����������������˵�*/
    x1 = a+(k+1)*h;
    y0 = (*f)(x0);                         /* ��������������˵ĺ���ֵ*/
    y1 = (*f)(x1);
    t =  h*(y0+y1)/2.0;                    /* �����������ϵĻ��ֽ���ֵ*/
    t = subtz(x0,x1,y0,y1,h,t,eps/n,h0,f); /* �����Ӻ������������ϵĻ��ֽ���ֵ*/
    z = z+t;
  }
  return(z);
}

static double subtz(double x0,double x1,double y0,double y1,double h,double t,double eps,double h0,double (*f)(double))
{
  double x,y,t1,t2,d,z;
  x = x0+h/2.0;                            /* ������е�*/
  y = (*f)(x);                             /* �����е�ĺ���ֵ*/
  t1 = h*(y0+y)/4.0;
  t2 = h*(y+y1)/4.0;                       /* ����������Ļ��ֽ���ֵ*/
  d = fabs(t-(t1+t2));
  if((d<eps)||(h>h0))
    z = t1+t2;                             /* �Ѿ����㾫��Ҫ��������������*/
  else
  {
    t1 = subtz(x0,x,y0,y,h/2.0,t1,eps/2.0,h0,f);
    t2 = subtz(x,x1,y,y1,h/2.0,t2,eps/2.0,h0,f);
    z = t1+t2;                             /* ��������������Ļ��ֽ���ֵ֮��*/
  }
  return(z);
}
