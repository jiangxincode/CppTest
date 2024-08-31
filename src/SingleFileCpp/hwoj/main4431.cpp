/**
 * IP地址判断有效性 IPAddressValid
 * 题目标题：
 * 判断输入的字符串是不是一个有效的IP地址
 * 详细描述：
 * 请实现如下接口
 * bool isIPAddressValid(const char* pszIPAddr)
 * 输入：pszIPAddr 字符串
 * 输出：true 有效的IP地址，false，无效的IP地址
 * 约束
 * 输入IP为XXX.XXX.XXX.XXX格式
 * 字符串两端含有空格认为是合法IP
 * 字符串中间含有空格认为是不合法IP
 * 类似于 01.1.1.1， 1.02.3.4  IP子段以0开头为不合法IP
 * 子段为单个0 认为是合法IP，0.0.0.0也算合法IP
 */
#include <cctype>
#include <string>
#include <cstring>
#include <iostream>


using namespace std;

bool isIPAddressValid(const char* pszIPAddr)
{
    if (pszIPAddr == NULL || pszIPAddr[0] == '\0')
    {
        return false;
    }

    const char *p = pszIPAddr;
    int i_start = 0, i_end = strlen(pszIPAddr)-1;
    while (p[i_start] == ' ')
    {
        i_start++;
    }
    while (p[i_end] == ' ')
    {
        i_end--;
    }
    int dot_count = 0; //记录小数点的个数
    int dot_pos[3] = {0}; //记录小数点的位置
    for(int i=i_start;i<=i_end;i++)
    {
        if (p[i] == '.')
        {
            dot_pos[dot_count++] = i;
        }
        else if (!isdigit(p[i]))
        {
            return false;
        }
    }
    if (dot_count != 3)
    {
        return false;
    }
    if ((i_start==dot_pos[0]) || (dot_pos[0]+1==dot_pos[1]) || (dot_pos[1]+1==dot_pos[2]) || (dot_pos[2]==i_end))
    {
        return false; //小数点在开头或者末尾，或者小数点相邻
    }
    else if ((dot_pos[0]-i_start>3) || (dot_pos[1]-dot_pos[0]>4) || (dot_pos[2]-dot_pos[1]>4) || (i_end-dot_pos[2]>3))
    {
        return false; //小数点之间的数字位数过多
    }
    else if(
            (p[i_start]=='0' && isdigit(p[i_start+1])) ||
            (p[dot_pos[0]+1]=='0' && isdigit(p[dot_pos[0]+2])) ||
            (p[dot_pos[1]+1]=='0' && isdigit(p[dot_pos[1]+2])) ||
            (p[dot_pos[2]+1]=='0' && isdigit(p[dot_pos[2]+2])))
    {
        return false;
    }
    return true;
}

int main()
{
    const char *pazIPAddress = "127.0.0.1";
    bool isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == true) << std::endl;

    pazIPAddress = "01.1.1.1";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == false) << std::endl;

    pazIPAddress = "1.02.3.4";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == false) << std::endl;

    pazIPAddress = "0.0.0.0";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == true) << std::endl;

    pazIPAddress = "    0.0.0.0    ";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == true) << std::endl;

    pazIPAddress = "a.0.0.0";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == false) << std::endl;

    pazIPAddress = "0 .0.0.0";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == false) << std::endl;

    pazIPAddress = "";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == false) << std::endl;

    pazIPAddress = "1234.123.123.0";
    isIP = isIPAddressValid(pazIPAddress);
    std::cout << (isIP == false) << std::endl;
}

//bool isIPAddressValid(const char* pszIPAddr)
//{
//    // 请在此处实现
//
//    const char *p = pszIPAddr;
//
//    int index = 0; //偏移索引
//    int count_slice = 0; //统计子段数目
//
//
//    /* 过滤掉开始的空格*/
//    while(p[index] == ' ')
//    {
//        index++;
//    }
//
//    /*处理前三个IP子段*/
//    while(count_slice < 3)
//    {
//        int count_num = 0; //统计每个子段的数字个数
//        while((p[index] != '.') && (p[index] != '\0'))
//        {
//            if(!isdigit(p[index])) //非数字
//            {
//                return false;
//            }
//            if((p[index] == '0') && (count_num == 0) && (p[index+1] != '.')) //IP子段以0开头
//            {
//                return false;
//            }
//
//            count_num++;
//            if(count_num > 3) //数字过多
//            {
//                return false;
//            }
//
//            index++;
//        }
//
//        if(p[index] == '.') //处理下一个IP子段
//        {
//            index++;
//            count_slice++;
//        }
//        else //字符串到达末尾
//        {
//            return false;
//        }
//    }
//
//    /*处理最后一个IP子段*/
//    int count_num = 0;
//    while((p[index] != ' ') && (p[index] != '\0'))
//    {
//        if(!isdigit(p[index])) //非数字
//        {
//            return false;
//        }
//        if((p[index] == '0') && (count_num == 0) && (p[index+1] != ' ') && (p[index+1] != '\0')) //IP子段以0开头
//        {
//            return false;
//        }
//
//        count_num++;
//        if(count_num > 3) //数字过多
//        {
//            return false;
//        }
//
//        index++;
//    }
//
//    /*处理之后的字符*/
//    while(p[index] != '\0')
//    {
//        if(p[index] != ' ') //出现异常字符
//        {
//            return false;
//        }
//        index++;
//    }
//
//    return true;
//}
