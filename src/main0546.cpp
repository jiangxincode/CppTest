/**
一人岁数的3次方是四位数，四次方是六位数，
并知道此人岁数的3次方和4次方用遍了0～9十个数字。
编写一程序求此人的岁数。
*/

#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main0546()
{
    for(int i=1; i<200; i++) //假设最大年龄为200岁
    {
        int t_age = i*i*i; //年龄的三次方
        int temp;

        if(t_age<1000 || t_age>9999)
        {
            continue;
        }

        int q_age = t_age*i; //年龄的四次方

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

        for(it=age_map.begin(); it!=age_map.end(); ++it)
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
