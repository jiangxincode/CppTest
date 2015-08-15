/*
判断两个数组中是否有相同的数字
百度笔试题
思路：先排序，然后遍历其中较短的数组中的每个元素，在较长的数组中使用二分查找。
*/
#include <iostream>
#include <cstdlib>

using namespace std;

static int comp(const void *a, const void *b)
{
    return *(int *)a - *(int*)b;
}
int main0535()
{
    int maxSize,minSize;
    cin >> maxSize >> minSize;
    int *maxArr = new int[maxSize];
    int *minArr = new int[minSize];

    for(int i=0; i<maxSize; i++) //生成随机数据
    {
        maxArr[i] = rand()%50;
    }

    for(int i=0; i<minSize; i++)
    {
        minArr[i] = rand()%50;
    }

    for(int i=0; i<maxSize; i++) //输出
    {
        cout << maxArr[i] << " ";
    }

    cout << endl;

    for(int i=0; i<minSize; i++)
    {
        cout << minArr[i] << " ";
    }

    cout << endl;
    qsort(maxArr,maxSize,sizeof(int),comp);
    qsort(minArr,minSize,sizeof(int),comp);

    for(int i=0; i<maxSize; i++) //输出
    {
        cout << maxArr[i] << " ";
    }

    cout << endl;

    for(int i=0; i<minSize; i++)
    {
        cout << minArr[i] << " ";
    }

    cout << endl;

    for(int i=0; i<minSize; i++)
    {
        if(bsearch((minArr+i),maxArr,maxSize,sizeof(int),comp))
        {
            cout << "True";
            delete []maxArr;
            delete []minArr;
            return 1;
        }
    }

    delete []maxArr;
    delete []minArr;
    cout << "false";
    return 0;
}
