/*
�ж������������Ƿ�����ͬ������
�ٶȱ�����
˼·��������Ȼ��������н϶̵������е�ÿ��Ԫ�أ��ڽϳ���������ʹ�ö��ֲ��ҡ�
*/
#include <iostream>
#include <cstdlib>

using namespace std;

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int*)b;
}
int main0535()
{
    int maxSize,minSize;
    cin >> maxSize >> minSize;
    int *maxArr = new int[maxSize];
    int *minArr = new int[minSize];

    for(int i=0; i<maxSize; i++) //�����������
    {
        maxArr[i] = rand()%50;
    }

    for(int i=0; i<minSize; i++)
    {
        minArr[i] = rand()%50;
    }

    for(int i=0; i<maxSize; i++) //���
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

    for(int i=0; i<maxSize; i++) //���
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
            return 1;
        }
    }

    delete []maxArr;
    delete []minArr;
    cout << "false";
    return 0;
}
