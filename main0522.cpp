/*
������ʱ��ĺͣ���������ʱ�䣨ʱ��ĸ�ʽΪhh:mm:ss,��֤���붼����ȷ��ʱ�䣬�����Լ����ü�������ʱ����ȷ��񣩣�����������ʱ��ĺͲ��������������
00:00:04
00:00:01
��������ʱ����00:00:05 (��ʾ����ʱ��ת��Ϊ����)
�������Ҫ��Ƶ��ַ���������ת����Ȼ��ֱ��������ʱ��������ͣ�
Ȼ�����������ת��Ϊ��ȷ��ʱ���ʽ��hh:mm:ss���Ϳ����ˣ�
Ҫע���������Сʱ����ı߽紦���Լ����������ʽ�����������ļ�������6Сʱ7��0�룬
�����ʱӦ�ð����������06��07��00���������Ļ���û��ʲô��
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main0522()
{
    string time1,time2;
    string result;
    vector<int> vec1,vec2;
    cin >> time1 >> time2;
    string::size_type pos;

    while((pos=time1.find(":"))!=string::npos)
    {
        time1.replace(pos,1," ");
    }

    while((pos=time2.find(":"))!=string::npos)
    {
        time2.replace(pos,1," ");
    }

    stringstream io1(time1);
    stringstream io2(time2);
    int temp;

    while(io1 >> temp)
    {
        vec1.push_back(temp);
    }

    while(io2 >> temp)
    {
        vec2.push_back(temp);
    }

    int second = (vec1[2]+vec2[2])%60;
    int minute = (vec1[1]+vec2[1]+(vec1[2]+vec2[2])/60)%60;
    int hour = vec1[0]+vec2[0]+(vec1[1]+vec2[1]+(vec1[2]+vec2[2])/60)/60;
    cout << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second;
    return 0;
}
