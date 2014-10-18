#include <iostream>
#include <initializer_list>

using namespace std;

int test_Ex_6_27(std::initializer_list<int> li);

int main1560()
{
    cout << test_Ex_6_27({23,78,89,76,90}) << endl;
    return 0;
}

int test_Ex_6_27(initializer_list<int> li)
{
    int result = 0;

    for(auto i = li.begin(); i != li.end(); i++)
    {
        result += *i;
    }

    return result;
}

/*****************************************************************
Ex_6_28:
elem��һ����string�ĳ��������͡�

Ex_6_29:
���˾���������������������������ν�����ȼ��벻�����������ͣ��ͻ�
���������Ŀ�����������������ֿ����Ļ�������Ӧ������ȫ��ͬ�ģ���ʱ����
�����������ͣ�Ҳ����ı�initializer_list��ֵ����Ϊ������Զ�ǳ���ֵ�����ң�
���������ڲ�����������ʱ��������const�޶���
*****************************************************************/
