/*
关于排序算法的一些小程序
*/


#include <iostream>
#include <cstdlib>

using namespace std;

/*冒泡排序*/
void bubblesort(int *arr, int n)
{
    bool change;
    for(int i=1;i<n;i++)
    {
        change = false;
        for(int j=n-1;j>=i;j--)
        {
            if(arr[j]<arr[j-1])
            {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
                change = true;
            }
        }
        if(change == false)
        {
            return ;
        }
    }
}

/*插入排序*/
void insertsort(int *arr, int n)
{
    for(int i=1;i<n;i++)
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
    for(int i=left+1;i<=right;i++)
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


#define NUM 20

int main0544()
{
    int arr[NUM];
    for(int i=0;i<NUM;i++)
    {
        arr[i] = rand()%100;
    }

    for(int i=0;i<NUM;i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    //quicksort(arr, 0, NUM-1);
    //bubblesort(arr, NUM);
    insertsort(arr,NUM);

    for(int i=0;i<NUM;i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}


