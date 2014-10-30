
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

static const int MAXNUM = 1000;

/**
二分查找x是否在一个有序数组中，返回其在数组中最先出现的位置（从0开始）
比如：1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 4 5
若x=3则返回2
非递归，不能左右探测
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

    for(int i=0; i<MAXNUM; i++) //对格式进行控制，每十个数字输出一个换行符
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
使用二分法查找字符串：
给定一个有序的字符串数组，查找其中是否包含指定字符串
若存在则返回对应位置
否则返回-1
*/
int Bin(const char* sp[],const char *str,const int n)
{
    int left = 0,right = n-1;
    int pos = -1;

    while(left <= right)
    {
        int mid = (left+right)/2;

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
递归方法实现二分查找算法
在下届为low，上界为high的数组a中折半查找数据元素x
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
非递归方法实现二分查找算法
*/
int BSearch(int a[],int key,int n)
{
    int low,high;
    low=0;
    high=n-1;

    while(low<=high)
    {
        int mid=(low+high)/2;

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
