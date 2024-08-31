/**
 * 判断任意两台计算机的IP地址是否属于同一子网络
 * 子网掩码是用来判断任意两台计算机的IP地址是否属于同一子网络的根据。
 * 最为简单的理解就是两台计算机各自的IP地址与子网掩码进行AND运算后，如果得出的结果是相同的，则说明这两台计算机是处于同一个子网络上的，可以进行直接的通讯。就这么简单。
 * 请看以下示例：
 * 运算演示之一：
 * IP地址:192.168.0.1
 * 子网掩码:255.255.255.0
 * AND运算
 * 转化为二进制进行运算：
 * IP地址:11010000.10101000.00000000.00000001
 * 子网掩码:11111111.11111111.11111111.00000000
 * AND运算:11010000.10101000.00000000.00000000
 * 转化为十进制后为： 192.168.0.0
 *
 * 运算演示之二：
 * IP地址:192.168.0.254
 * 子网掩码:255.255.255.0
 * AND运算
 * 转化为二进制进行运算：
 * IP地址:11010000.10101000.00000000.11111110
 * 子网掩码:11111111.11111111.11111111.00000000
 * AND运算:11010000.10101000.00000000.00000000
 * 转化为十进制后为：192.168.0.0
 *
 * 通过以上对两台计算机IP地址与子网掩码的AND运算后，我们可以看到它运算结果是一样的。均为192.168.0.0，所以这二台计算机可视为是同一子网络。
 *
 * 接口说明
 * 原型：
 *     int IsSameSubNetwork(char * pcIp1, char * pcIp2, char * pcSubNetworkMask);
 * 输入参数：
 *     char * pcIP1: 计算机1的IP地址，格式：“192.168.0.254”
 *     char * pcIP2: 计算机2的IP地址，格式：“192.168.0.1”
 *     char * pcSubNetworkMask: 子网掩码，格式：“255.255.255.0”
 * 返回值：
 *     0：IP1与IP2不属于同一子网络。
 *     1：IP1与IP2属于同一子网络。
 *
 */

#include <sstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
功能: 判断两台计算机IP地址是同一子网络。
原型：
    int IsSameSubNetwork(char * pcIp1, char * pcIp2, char * pcSubNetworkMask);

输入参数：
    char * pcIP1: 计算机1的IP地址，格式：“192.168.0.254”；
    char * pcIP2: 计算机2的IP地址，格式：“192.168.0.1”；
    char * pcSubNetworkMask: 子网掩码，格式：“255.255.255.0”；

返回值：
    0：IP1与IP2不属于同一子网络；
    1：IP1与IP2属于同一子网络；
*/

int IsSameSubNetwork(char * pcIp1, char * pcIp2, char * pcSubNetworkMask)
{
    /*在这里实现功能*/
    vector<unsigned int> pcIpVec1;
    vector<unsigned int> pcIpVec2;
    vector<unsigned int> pcSubNetworkMaskVec;
    vector<unsigned int> pcSubNetworkVec1;
    vector<unsigned int> pcSubNetworkVec2;

    string str;
    string::size_type pos;
    unsigned int temp;


    str = string(pcIp1);
    while((pos=str.find(".")) != string::npos)
    {
        str.replace(pos,1," ");
    }
    istringstream ss1(str);
    while(ss1 >> temp)
    {
        pcIpVec1.push_back(temp);
    }

    str = string(pcIp2);
    while((pos=str.find(".")) != string::npos)
    {
        str.replace(pos,1," ");
    }
    istringstream ss2(str);
    while(ss2 >> temp)
    {

        pcIpVec2.push_back(temp);
    }

    str = string(pcSubNetworkMask);
    while((pos=str.find(".")) != string::npos)
    {
        str.replace(pos,1," ");
    }
    istringstream ss(str);
    while(ss >> temp)
    {
        pcSubNetworkMaskVec.push_back(temp);
    }

    for(unsigned int i=0;i<4;i++)
    {
        pcSubNetworkVec1.push_back(pcIpVec1[i] & pcSubNetworkMaskVec[i]);
        pcSubNetworkVec2.push_back(pcIpVec2[i] & pcSubNetworkMaskVec[i]);
    }
    if(equal(pcSubNetworkVec1.begin(),pcSubNetworkVec1.end(),pcSubNetworkVec2.begin()))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int iRet;

    iRet = IsSameSubNetwork("192.168.0.1", "192.168.0.254", "255.255.255.0");

    std::cout << (iRet == 1) << std::endl;
}
