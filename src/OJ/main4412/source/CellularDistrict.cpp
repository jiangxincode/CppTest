#include "CellularDistrict.h"
#include <stdio.h>

void search(int x,int *ans,int **a,int *d,int &m,int n)
{
    if(d[x] == 0)
    {
        ans[++m] = x;
        return;
    }

    for(int i = 1; i <= n; i++) if(a[x][i])
        {
            a[x][i]--;
            a[i][x]--;
            d[x]--;
            d[i]--;
            search(i,ans,a,d,m,n);
        }

    ans[++m] = x;
}
/************************************************************************
Description  : һ�ʻ�������ͼ��
Prototype    :
 Input Param  : n��ʾҪ�����߶ε�����
				arrLines��ʾ�ɶ����߶���ɵ�ͼ�Σ��ɵ����߸���ָ��ķ��䣬�ͷźͱ�֤�Ϸ���
Output Param : 	aDrawline�������˳�򣬵����߱�ָ֤��Ϸ��ԣ��ɵ����߸���ָ��ķ��䣬�ͷźͱ�֤�Ϸ���
Return Value :	 �ɹ����� 0 ��ʧ�ܷ���-1
************************************************************************/
int OneLineDrawMap(int n, tLine* arrLines, int* aDrawline)
{
    aDrawline = NULL;
    int **a,*d,x,y;
    a = new int* [n + 2];
    d = new int [n + 2];

    for(int i = 1; i <= n + 1; i++)
    {
        a[i] = new int [n + 2];
    }

    for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1; j++)
        {
            a[i][j] = 0;
        }

    for(int i = 1; i <= n + 1; i++)
    {
        d[i] = 0;
    }

    for(int i = 0; i < n; i++)
    {
        x = arrLines[i].pot1;
        y = arrLines[i].pot2;
        a[x][y]++;
        a[y][x]++;
        d[x]++;
        d[y]++;
    }

    bool f = 0;
    int k = 0;

    for(int i = n + 1; i >= 1; i++) if(d[i] & 1)
        {
            x = i;
            f = 1;
            k++;
        }

    if(k == 1 || k > 2)
    {
        for(int i = 1; i <= n + 1; i++)
        {
            delete [] a[i];
        }

        delete [] a;
        delete [] d;
        return -1;
    }

    if(!f) for(int i = 1; i <= n + 1; i++) if(d[i])
            {
                x = i;
                break;
            }

    int *ans = new int [n + 2];
    int m = 0;
    search(x,ans,a,d,m,n + 1);
    aDrawline = new int[n + 1];

    for(int i = 0; i <= n; i++)
    {
        aDrawline[i] = ans[n + 1 - i];
    }

    for(int i = 0; i < n; i++)
    {
        printf("%d ",aDrawline[i]);
    }

    printf("%d\n",aDrawline[n]);

    for(int i = 1; i <= n + 1; i++)
    {
        delete [] a[i];
    }

    delete [] a;
    delete [] d;
    delete [] ans;
    return 0;
}
