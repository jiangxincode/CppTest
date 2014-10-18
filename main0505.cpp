/*
    author:
        jiangxin
    Blog:
        http://blog.csdn.net/jiangxinnju
    function:
    int A[nSize]����������������0�������0������
    дһ������int Func(int* A, int nSize)��
    ʹA��0�������棬��0������������ǰ�沢��������
    ����ֵΪԭ�����е�һ��Ԫ��Ϊ0���±ꡣ
    (�����ܲ�ʹ�ø����ռ��ҿ���Ч�ʼ��쳣���⣬ע�͹淶�Ҹ������˼·)

*/
#include <iostream>
#include <random>

using namespace std;

#define ARRAYSZIE 100
int Func(int* A,int nSize)
{
    int *p_zero = A; //ָ���ʼ����ֵ
    int *p_unzero = A; //ָ�����ķ���ֵ

    while(1)
    {
        for(int i=(p_zero-A); i<nSize; i++)
        {
            if(A[i] == 0) //�ҵ���һ����ֵ
            {
                p_zero = &A[i];
                break;
            }

            if(i == nSize-1) //û���ҵ���ֵ��˵��ȫ��Ϊ����ֵ
            {
                return -1;
            }
        }

        for(int i=(p_zero-A+1); i<nSize; i++)
        {
            if(A[i] != 0) //�ҵ���ֵ֮��ĵ�һ������ֵ
            {
                p_unzero = &A[i];
                break;
            }

            if(i == nSize-1) //û���ҵ���һ������ֵ��˵��ȫ��Ϊ��ֵ�������Ѿ��������
            {
                return (p_zero-A);
            }
        }

        *p_zero = *p_unzero;
        *p_unzero = 0;
        p_zero++;
    }
}
void main0505()
{
    int A[ARRAYSZIE];
    default_random_engine e;
    uniform_int_distribution<> d(0,1);

    for(int i=0; i<ARRAYSZIE; i++)
    {
        A[i] = d(e); //�������0��1ֵ
    }

    for(int i=0; i<ARRAYSZIE; i++)
    {
        cout << A[i] << " ";
    }

    cout << "\nThe position of the first zero is: " << Func(A,ARRAYSZIE) << endl;

    for(int i=0; i<ARRAYSZIE; i++)
    {
        cout << A[i] << " ";
    }
}
