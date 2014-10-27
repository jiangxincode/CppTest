/**
 * 关于排序算法的一些小程序
 */


#include <iostream>
#include <cstdlib>
#include <iomanip>

#define NUM 20

using namespace std;

/*冒泡排序*/
void bubblesort(int *arr, int n)
{
    bool flag;

    for(int i=1; i<n; i++)
    {
        flag = false;

        for(int j=n-1; j>=i; j--)
        {
            if(arr[j]<arr[j-1])
            {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
                flag = true;
            }
        }

        if(flag == false)
        {
            return ;
        }
    }
}

/*插入排序*/
void insertsort(int *arr, int n)
{
    for(int i=1; i<n; i++)
    {
        if(arr[i] < arr[i-1])
        {
            int temp = arr[i];
            int j = i-1;

            while(arr[j]>temp && j>=0)
            {
                arr[j+1] = arr[j];
                j --;
            }

            arr[j+1] = temp;
        }
    }
}
/*快速排序*/
int partion(int *arr, const int left, const int right)
{
    int pivotpos = left;
    int pivot = arr[left];

    for(int i=left+1; i<=right; i++)
    {
        if(arr[i]<pivot)
        {
            pivotpos ++;

            if(i!=pivotpos)
            {
                int temp = arr[i];
                arr[i] = arr[pivotpos];
                arr[pivotpos] = temp;
            }
        }
    }

    arr[left] = arr[pivotpos];
    arr[pivotpos] = pivot;
    return pivotpos;
}
void quicksort(int *arr, int left, int right)
{
    if(left < right)
    {
        int pivotpos = partion(arr, left, right);
        quicksort(arr, left, pivotpos-1);
        quicksort(arr, pivotpos+1, right);
    }
}

/*希尔排序*/
void shellsort(int *arr, int length)
{
    int gap = length;
    do {
        gap = gap/3+1;
        for(int i=gap;i<length;i++)
        {
            if(arr[i] < arr[i-gap])
            {
                int temp = arr[i];
                int j = i-gap;
                do {
                    arr[j+gap] = arr[j];
                    j = j-gap;
                }while(j>=0 && temp<arr[j]);
                arr[j+gap] = temp;
            }
        }
    } while(gap>1);

}

/*归并排序*/
void merge(int *arr, int left, int mid, int right)
{
    int temp[NUM];
    for(int i=left;i<=right;i++) //复制数组
    {
        temp[i] = arr[i];
    }
    int s1 = left;
    int s2 = mid+1;
    int t = left;
    while((s1<=mid) && (s2<=right))
    {
        if(temp[s1]<=temp[s2])
        {
            arr[t++] = temp[s1++];
        }
        else
        {
            arr[t++] = temp[s2++];
        }
    }
    while(s1 <= mid)
    {
        arr[t++] = temp[s1++];
    }
    while(s2 <= right)
    {
        arr[t++] = temp[s2++];
    }
}
void mergesort(int *arr, int left, int right)
{
    if(left >= right)
    {
        return ;
    }
    int mid = (left+right)/2;
    mergesort(arr,left,mid);
    mergesort(arr,mid+1,right);
    merge(arr, left, mid, right);
}


int main0544()
{
    int arr[NUM];

    for(int i=0; i<NUM; i++)
    {
        arr[i] = rand()%100;
    }

    for(int i=0; i<NUM; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
    //quicksort(arr, 0, NUM-1);
    //bubblesort(arr, NUM);
    //insertsort(arr,NUM);
    //shellsort(arr,NUM);
    mergesort(arr,0,NUM-1);

    for(int i=0; i<NUM; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}


