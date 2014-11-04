#include <iostream>

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
    int *temp = new int[right-left+1];

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

    delete []temp;
}

/** \brief 归并排序
 *
 * \param arr 指向待排序数组的指针
 * \param left 数组最左端元素序号
 * \param right 数组最右端元素序号
 * \return 无返回值
 *
 */

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

/** \brief 测试本文件中的所有排序函数
 *
 * \param 无
 * \return 成功返回0
 *
 */

int main0544()
{
    const int NUM = 20;
    int arr[NUM];

    for(int i=0; i<NUM; i++)
    {
        arr[i] = rand()%100;
    }

    for(int i=0; i<NUM; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
    //quicksort(arr, 0, NUM-1);
    //bubblesort(arr, NUM);
    //insertsort(arr,NUM);
    //shellsort(arr,NUM);
    //mergesort(arr,0,NUM-1);

    for(int i=0; i<NUM; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}


