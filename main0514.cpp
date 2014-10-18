// sstring��ʹ�ý���
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main05141()
{
    string name1 = "Zeta";
    int age1 = 16;
    ostringstream os;
    os << name1 << " " << age1;
    cout << os.str() << endl;
    string name2;
    int age2;
    istringstream is(os.str());
    is >> name2 >> age2;
    cout << name2 << " " << age2 << endl; //��stringstream�н��������ʱ���Կո�ͻس���Ϊ�ָ���
    return 0;
}

int main05142()
{
    string name1 = "12345";
    int age1;
    stringstream io1; //string to int
    io1 << name1;
    io1 >> age1;
    cout << age1 << endl;
    string name2;
    int age2 = 16;
    stringstream io2; //int to string
    io2 << age2;
    io2 >> name2;
    cout << name2 << endl;
    return 0;
}

int main05143()
{
    int i;
    stringstream io;
    io << "345";
    io >> i;
    cout << i << endl;
    io.clear(); //ע�⣺������������ת�����������clear()������ת��ģʽ
    io << true;
    io >> i;
    cout << i << endl;
    return 0;
}

int main05144()
{
    char buf[20];
    stringstream io;
    io << 888;
    io >> buf;  // ֱ�ӽ��������buf�ַ�������

    for(int i=0; buf[i]!='\0'; i++)
    {
        cout << buf[i];
    }

    cout << endl;
    return 0;
}

int main05145() //��ȡ�Զ���Ϊ�ָ�������ֵ
{
    string input = "23,45,78,90,89";
    int temp;
    vector<int> vec;
    /*
    ����ʹ�ã�
    stringstream io(input.replace(input.begin(),input.end(),',',' '));
    ԭ����Բ���replace���÷��������ǽ��ƶ��ַ���ת��Ϊ��һ���ַ���������
    ���ƶ���Χ���ַ���ת��Ϊ��һ���ַ�����
    Ҳ����ʹ�ã�
    replace(input.begin(),input.end(),string(","),string(" "));
    algorithm��֧��replace
    */
    string::size_type pos;

    while((pos = input.find(","))!=string::npos) //�˴����źͿո�Ҳ����ʹ���ַ��������������ַ�����Ϊû�����ء�
    {
        input.replace(pos,1," ");
    }

    stringstream io(input);

    while(io >> temp)
    {
        vec.push_back(temp);
    }

    for(vector<int>::iterator it=vec.begin(); it!=vec.end(); it++)
    {
        cout << *it << " ";
    }

    return 0;
}
int main0514()
{
    main05145();
    return 0;
}
