// sstring的使用解析
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
    cout << name2 << " " << age2 << endl; //从stringstream中解析对象的时候，以空格和回车键为分隔符
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
    io.clear(); //注意：如果做多次数据转换；必须调用clear()来设置转换模式
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
    io >> buf;  // 直接将数输出到buf字符数组中

    for(int i=0; buf[i]!='\0'; i++)
    {
        cout << buf[i];
    }

    cout << endl;
    return 0;
}

int main05145() //读取以逗号为分隔符的数值
{
    string input = "23,45,78,90,89";
    int temp;
    vector<int> vec;
    /*
    不能使用：
    stringstream io(input.replace(input.begin(),input.end(),',',' '));
    原因可以查下replace的用法，它不是将制定字符串转换为另一个字符串，而是
    将制定范围的字符串转化为另一个字符串。
    也不能使用：
    replace(input.begin(),input.end(),string(","),string(" "));
    algorithm不支持replace
    */
    string::size_type pos;

    while((pos = input.find(","))!=string::npos) //此处逗号和空格也必须使用字符串，而不能是字符，因为没有重载。
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
