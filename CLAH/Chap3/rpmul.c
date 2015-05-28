#include <stdio.h>

/**
 * �� �� ����rpmul(a,n,b,m,c)
 * �������������ϵ����ʾ��ʵϵ���Ķ���ʽA��B��ˣ����ϵ������c��
 * ���������a������ʽAϵ������n��ϵ��������
 *           b������ʽBϵ������m��ϵ��������
 *            c�����صĶ���ʽC��ϵ����
 * �� �� ֵ���������֡�����ɹ��򷵻�1�����򷵻�0
 */
int rpmul(double *a,int n,double *b,int m,double *c)
{
    int i,j,k;

    if((a==NULL) || (b==NULL) || (c==NULL))
    {
        printf("rpmul)NULL pointer found.\n");
        return(0);
    }

    k = m+n-1;	 	/* ��˺��ϵ������*/

    for(i=0; i<k; i++)    /* �Ƚ�ϵ��������Ϊ0*/
    {
        c[i] = 0.0;
    }

    for(i=0; i<n; i++)    /* ���ν���˵Ľ���ۼӵ���Ӧ������*/
        for(j=0; j<m; j++)
        {
            c[i+j] += a[i]*b[j];
        }

    return(1);
}
