#include <iostream>

#include "sort.h"

/** \brief 冒泡排序
 *
 * \param arr 指向待排序数组的指针
 * \param n 待排序数组元素的个数
 * \return 无返回值
 *
 */

void bubblesort(int *arr, int n)
{
    for(int i=1; i<n; i++)
    {
        bool flag = false;

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


/** \brief 插入排序
 *
 * \param arr 指向待排序数组的指针
 * \param n 待排序数组元素的个数
 * \return 无返回值
 *
 */

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


/** \brief 快速排序的组件函数
 *
 * \param arr 指向待排序数组的指针
 * \param left 数组最左端元素序号
 * \param right 数组最右端元素序号
 * \return 数组最右端元素在排序后所在的位置
 *
 */

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

/** \brief 快速排序
 *
 * \param arr 指向待排序数组的指针
 * \param left 数组最左端元素序号
 * \param right 数组最右端元素序号
 * \return 无返回值
 *
 */

void quicksort(int *arr, int left, int right)
{
    if(left < right)
    {
        int pivotpos = partion(arr, left, right);
        quicksort(arr, left, pivotpos-1);
        quicksort(arr, pivotpos+1, right);
    }
}


/** \brief 希尔排序
 *
 * \param arr 指向待排序数组的指针
 * \param length 待排序数组元素的个数
 * \return 无返回值
 *
 */

void shellsort(int *arr, int length)
{
    int gap = length;

    do
    {
        gap = gap/3+1;

        for(int i=gap; i<length; i++)
        {
            if(arr[i] < arr[i-gap])
            {
                int temp = arr[i];
                int j = i-gap;

                do
                {
                    arr[j+gap] = arr[j];
                    j = j-gap;
                }
                while(j>=0 && temp<arr[j]);

                arr[j+gap] = temp;
            }
        }
    }
    while(gap>1);
}


/** \brief 归并排序的组件函数
 *
 * \param arr 指向待排序数组的指针
 * \param left 数组最左端元素序号
 * \param left 数组中间元素序号
 * \param right 数组最右端元素序号
 * \return 无返回值
 *
 */

void merge(int *arr, int left, int mid, int right)
{
    int *temp = (int*)malloc(sizeof(int)*(right+1)); //注意此处是right+1，不是right-left+1

    for(int i=left; i<=right; i++) //复制数组
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

    free(temp);
}

/** \brief 归并排序(递归版本)
 *
 * \param arr 指向待排序数组的指针
 * \param left 数组最左端元素序号
 * \param right 数组最右端元素序号
 * \return 无返回值
 *
 */

void mergesort_recursive(int *arr, int left, int right)
{
    if(left >= right)
    {
        return ;
    }

    int mid = (left+right)/2;
    mergesort_recursive(arr,left,mid);
    mergesort_recursive(arr,mid+1,right);
    merge(arr, left, mid, right);
}

/** \brief 归并排序(非递归版本)
 *
 * \param arr 指向待排序数组的指针
 * \param n 待排序数组元素的个数
 * \return 无返回值
 *
 */

void mergesort(int *arr, int n)
{
    int size = 1;
    while(size < n)
    {
        int low = 0;
        while(low + size < n)
        {
            int mid = low + size - 1;
            int high = mid + size;

            if(high > n-1) //第二个序列个数不足size
            {
                high = n-1;
            }

            merge(arr,low,mid,high);
            low = high + 1; //下一次归并时第一关序列的下界
        }
        size *= 2; //范围扩大一倍
    }
}

//int index = 0;
//int* temp = (int*)malloc(sizeof(int)*n);
//int sleep_sort_tool(int time)
//{
//    sleep(time);
//    temp[index++];
//}
//void sleepsort(int *arr, int n)
//{
//    for(int i=0;i<n;i++)
//    {
//        sleep_sort_tool(arr[i]);
//    }
//}
