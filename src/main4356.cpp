
#include "OJ.h"

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

int IsSameSubNetwork(const char * pcIp1, const char * pcIp2, const char * pcSubNetworkMask)
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

    for(unsigned int i=0; i<4; i++)
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

int main4536()
{
    cout << IsSameSubNetwork("192.168.0.1", "192.168.0.254", "255.255.255.0") << endl;
    return 0;
}
