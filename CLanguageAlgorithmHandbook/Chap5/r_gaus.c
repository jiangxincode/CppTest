/*======================================================
// ��������r_gaus
// �����������ø�˹��ȥ�������Է�����
// ���������a ��ϵ������b ��������x���صĽ�����
//           n δ֪��������eps ����Ҫ��С��eps��ֵ����Ϊ��0��
// ����ֵ�����͡����гɹ��򷵻�1,ʧ���򷵻�0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int r_gaus(a,b,x,n,eps)
double *a,*b,*x,eps;
int n;
{
    int i,j,k,l,v,exis,*exjs;
    double tmp,d;
    if((a==NULL)||(b==NULL)||(x==NULL))             /* ��������ָ���Ƿ�Ϊ��*/
    {
        printf("The pointer exis NULL\n");
        return(0);
    }
    exjs = malloc(n*sizeof(int));          /* Ϊ�н�����¼����ռ䲢����Ƿ�ɹ�*/
    if(exjs == NULL)
    {
        printf("Memory alloc failed\n");
        return(0);
    }
    for(k=0; k<n; k++)
    {
      d = 0.0;
      for(i=k; i<n; i++)                              /* ��ѭ������ѡȡ��Ԫ*/
      for(j=k; j<n; j++)
      {
        l = i*n + j;
        tmp = fabs(a[l]);                             /* ��Ԫ�صľ���ֵ*/
        if(tmp>d)
        {
          d = tmp;
          exis = i;
          exjs[k] = j;
        }
      }
      if(d < eps)                                     /* �ж���Ԫ�Ƿ��С*/
      {
        free(exjs);
        printf("failed.\n");
        return(0);                                    /* ����Ԫ��С���˳�����*/
      }
      if(exis!=k)                                       /* �ж��Ƿ���Ҫ�н���*/
      {
        for(j=0; j<n; j++)                            /* �����н���*/
        {
          l = k*n + j;
          v = exis*n + j;
          tmp = a[l];
          a[l] = a[v];
          a[v] = tmp;
        }
        tmp = b[k];                                  /* ��������ҲҪ�����н���*/
        b[k] = b[exis];
        b[exis] = tmp;
      }
      if(exjs[k]!=k)                                   /* �ж��Ƿ���Ҫ�н���*/
      for(i=0; i<n; i++)                             /* �����н���*/
      {
        l = i*n + k;
        v = i*n + exjs[k];
        tmp = a[l];
        a[l] = a[v];
        a[v] = tmp;
      }
      l = k*n + k;
      a[l] = 1.0/a[l];                              /* ȡ����������ת��Ϊ�˷�*/
      for(j=k+1; j<n; j++)                          /* ��һ������*/
      {
        v = k*n + j;
        a[v] = a[l]*a[v];
      }
      b[k] *= a[l];                             /* ���������Ĺ�һ������*/
      for(i=k+1; i<n; i++)                          /* ��Ԫ����*/
      {
        for(j=k+1; j<n; j++)
          a[i*n+j] -= a[i*n+k]*a[k*n+j];
        b[i] -= a[i*n+k]*b[k];                     /* ��������ҲҪ������Ԫ����*/
      }
    }
    x[n-1] = b[n-1];                               /* ��һ�����ֱ�Ӷ���*/
    for(i=n-2; i>=0; i--)                          /* �������лش������������*/
    {
      tmp = 0.0;
      for(j=i+1; j<n; j++)
        tmp = tmp + a[i*n+j]*x[j];
      x[i] = b[i] - tmp;
    }
    for(k=n-1; k>=0; k--)                      /* �����н�������ʷ���н���ָ�*/
    {
      if(exjs[k]!=k)                             /* �ж��Ƿ���Ҫ�ָ�*/
      {
        tmp = x[k];                            /* �ָ����˳��*/
        x[k] = x[exjs[k]];
        x[exjs[k]] = tmp;
      }
    }
    free(exjs);                                  /* �ͷŷ���Ŀռ�*/
    return(1);                                 /* ���ɹ�������1*/
}
