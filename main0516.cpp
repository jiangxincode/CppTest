/*
��Ϊ��˾2014��У԰��Ƹ������ϻ���������
һ������������װ��n(1 �� n �� 65535)յ��ƣ���ͷ��β���1��2��3����n-1��n��
ÿյ�����һ�����߿��ؿ��ơ���ʼ�����ȫ�����š���n��ѧ���ӳ��ȴ�����
��һ��ѧ���Ѻ��뷲��1�ı����ĵ�ƵĿ�����һ�£�
���ŵڶ���ѧ���Ѻ��뷲��2�ı����ĵ�ƵĿ�����һ�£�
���ŵ�����ѧ���Ѻ��뷲��3�ı����ĵ�ƵĿ�����һ�£�
��˼�����ȥ������n��ѧ���Ѻ��뷲��n�ı����ĵ�ƵĿ�����һ�¡�
n��ѧ�����˹涨����󣬳��������м�յ���š�
ע���������ѧ����һ�¡�

���룺��Ƶ�����
��������ŵĵ������
�������룺3
���������1
*/

#include <iostream>
#include <utility>
#include <map>

using namespace std;

int main0516()
{
    map<int,bool> map_lamp;
    int num;
    cin >> num;
    for(int i=1;i<=num;i++)
    {
        map_lamp.insert(pair<int,bool>(i,false));
    }
    for(int i=1;i<=num;i++)
    {
        for(int j=1;j<=num;j++)
        {
            if(j%i == 0)
            {
                if(map_lamp[j] == false)
                {
                    map_lamp[j] = true;
                }
                else if(map_lamp[j] == true)
                {
                    map_lamp[j] = false;
                }
            }
        }
    }

    int result = 0;
    for(int i=1;i<=num;i++)
    {
        if(map_lamp[i] == true)
        {
            result ++;
        }
    }
    cout << result;
    return 0;
}
