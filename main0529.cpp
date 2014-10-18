
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

#define MAXNUM 1000

/**
���ֲ���x�Ƿ���һ�����������У������������������ȳ��ֵ�λ�ã���0��ʼ��
���磺1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 4 5
��x=3�򷵻�2
�ǵݹ飬��������̽��
*/
int bin_search(int arr[], int length, int x)
{
    int low = 0, high = MAXNUM-1;
    int mid;

    while(low <= high)
    {
        mid = (low+high)/2;

        if(arr[mid] < x)
        {
            low = mid+1;
        }
        else if(arr[mid] > x)
        {
            high = mid-1;
        }
        else
        {
            break;
        }
    }

    low = 0;
    high = mid;

    while(low <= high)
    {
        mid = (low+high)/2;

        if(arr[mid] == x)
        {
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }

    return mid;
}
int main05291()
{
    int arr[MAXNUM];

    for(int i=0; i<MAXNUM; i++)
    {
        arr[i] = i/5;
    }

    for(int i=0; i<MAXNUM; i++) //�Ը�ʽ���п��ƣ�ÿʮ���������һ�����з�
    {
        cout << arr[i] << " ";

        if(i % 10 == 9)
        {
            cout << endl;
        }
    }

    int x;
    cin >> x;
    cout << bin_search(arr,MAXNUM,x);
    return 0;
}

/**
ʹ�ö��ַ������ַ�����
����һ��������ַ������飬���������Ƿ����ָ���ַ���
�������򷵻ض�Ӧλ��
���򷵻�-1
*/
int Bin(const char* sp[],const char *str,const int n)
{
    int left = 0,right = n-1,mid;
    int pos = -1;

    while(left <= right)
    {
        mid = (left+right)/2;

        if(strcmp(str,sp[mid])<0)
        {
            right = mid -1;
        }
        else if(strcmp(str,sp[mid])>0)
        {
            left = mid +1;
        }
        else
        {
            pos = mid;
            break;
        }
    }

    return pos;
}


int main05292()
{
    const char *temp[] = {"li","qian","sun","zhao"};
    cout << Bin(temp, "sun", 4) << endl;
    return 0;
}


/**
�ݹ鷽��ʵ�ֶ��ֲ����㷨
���½�Ϊlow���Ͻ�Ϊhigh������a���۰��������Ԫ��x
*/
int BSearch(int a[],int x,int low,int high)
{
    int mid;

    if(low>high)
    {
        return -1;
    }

    mid=(low+high)/2;

    if(x==a[mid])
    {
        return mid;
    }

    if(x<a[mid])
    {
        return(BSearch(a,x,low,mid-1));
    }
    else
    {
        return(BSearch(a,x,mid+1,high));
    }
}
/**
�ǵݹ鷽��ʵ�ֶ��ֲ����㷨
*/
int BSearch(int a[],int key,int n)
{
    int low,high,mid;
    low=0;
    high=n-1;

    while(low<=high)
    {
        mid=(low+high)/2;

        if(a[mid]==key)
        {
            return mid;
        }
        else if(a[mid]<key)
        {
            low=mid+1;
        }
        else
        {
            high=mid-1;
        }
    }

    return -1;
}

int main0529()
{
    main05292();
    return 0;
}
