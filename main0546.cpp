/**
һ��������3�η�����λ�����Ĵη�����λ����
��֪������������3�η���4�η��ñ���0��9ʮ�����֡�
��дһ��������˵�������
*/

#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main0546()
{
    for(int i=1; i<200; i++) //�����������Ϊ200��
    {
        int t_age = i*i*i; //��������η�
        int temp;

        if(t_age<1000 || t_age>9999)
        {
            continue;
        }

        int q_age = t_age*i; //������Ĵη�

        if(q_age<100000 || q_age>999999)
        {
            continue;
        }

        map<int,int> age_map;

        for(int j=0; j<10; j++)
        {
            age_map.insert(make_pair(j,0));
        }

        temp = t_age;

        while(temp > 0)
        {
            age_map[temp%10] ++;
            temp /= 10;
        }

        temp = q_age;

        while(temp > 0)
        {
            age_map[temp%10] ++;
            temp /= 10;
        }

        map<int,int>::iterator it;

        for(it=age_map.begin(); it!=age_map.end(); it++)
        {
            pair<int,int> temp = *it;

            if(temp.second == 0)
            {
                break;
            }
        }

        if(it == age_map.end())
        {
            cout << t_age << " " << q_age << " " << i << endl;
        }
    }

    return 0;
}
