#include <iostream>
#include <string>

using namespace std;
/*
���Ա�׼����cin���ļ�������
����ƽ̨��Windows
*/
int test_string_one();
int test_string_two();
int test_string_three();

int main0502()
{
    //test_string_one();
    test_string_two();
    return 0;
}
int test_string_one() //��һ�����������������
{
    int num;
    while(cin>>num)
        cout << num << " ";
    return 0;
}
/*
���룺1 2 3 4 5 Ctrl+d Enter
�����1 2 3 4 5
�˴�֮����ѭ��ֹͣ������Ϊ����һ����Ч���루Ctrl+d�����������������ļ���������
��Ϊ��windowsƽ̨����������Ctrl+z��Ȼ��Enter��
�������룺1 2 3 4 5 a Enter
������ǣ�1 2 3 4 5
��Ȼ����ò�����������Linux�£���ô����ϵͳ�Ľ�������Ctrl+d��������Ȼ���һ����
����֮����ѭ��ֹͣ������Ϊ�������ļ������������ǵõ���һ����Ч���롣
*/


int test_string_two() //�ڶ���������������ַ���
{
    string word;
    while(cin>>word)
        cout << word << " ";
    return 0;
}
/*
���룺hello world Ctrl+z �س�
�����hello world
�˴�֮����ѭ��ֹͣ������Ϊ����һ���ļ���������
��Ϊ��windowsƽ̨����������Ctrl+z��Ȼ��Enter��
*/

