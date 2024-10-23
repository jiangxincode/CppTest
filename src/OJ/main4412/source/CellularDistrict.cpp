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
Description  : 一笔画出给定图形
Prototype    :
 Input Param  : n表示要画的线段的条数
				arrLines表示由多条线段组成的图形，由调用者负责指针的分配，释放和保证合法性
Output Param : 	aDrawline输出画线顺序，调用者保证指针合法性，由调用者负责指针的分配，释放和保证合法性
Return Value :	 成功返回 0 ，失败返回-1
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
