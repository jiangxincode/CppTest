/*
求两个时间的和，输入两个时间（时间的格式为hh:mm:ss,保证输入都是正确的时间，所以自己不用检查输入的时间正确与否），计算这两个时间的和并输出，例如输入
00:00:04
00:00:01
最后输出的时间是00:00:05 (提示：将时间转化为秒数)
这道题主要设计到字符串和整数转换，然后分别计算两个时间的秒数和，
然后将这个秒数和转换为正确的时间格式（hh:mm:ss）就可以了，
要注意的是最后的小时和秒的边界处理以及最后的输出格式（例如你最后的计算结果是6小时7分0秒，
你输出时应该按照这样输出06：07：00），其他的话就没有什么了
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
