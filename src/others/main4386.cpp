/**
 * 整型字符串排序
 * 给定字符串内有很多正整数，要求对这些正整数进行排序，然后返回排序后指定位置的正整数
 * 排序要求：按照每个正整数的后三位数字组成的整数进行从小到大排序
 * 1）如果不足三位，则按照实际位数组成的整数进行比较
 * 2）如果相等，则按照输入字符串中的原始顺序排序
 *
 * 说明（以下内容考生无须检查，调用者保证）：
 * 1) 字符串以’\0’结尾，仅包含数字、空格
 * 2) 字符串内正整数之间以单个空格分隔，字符串首尾没有空格
 * 3) 正整数格式为十进制，大小：1~1000000，正整数的数字非零开始
 *
 *
 * 示例:
 * 如字符串内容
 * 1223 22 3232 2016
 *
 * 按照规定排序后
 * 2016 22 1223 3232
 *
 * 查询排序后的第3个数是
 * 1223
 *
 */

#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

/*****************************************************************************
Description   : 根据字符串内容，输出排序后指定位置的正整数
Input Param   : input_string  输入的字符串
			    serial_number  排序后的序列号，从1开始
			    output_string_max_length  output_string的最大长度，包括'\0'
Output Param  : output_string  返回指定的字符串，必须包括'\0'，内存由调用者分配和释放
Return Value  : 成功返回0，失败返回-1（如：输入字符串是空串、输入序列号超出范围、最大长度不足）
*****************************************************************************/

bool comparator(pair<string,int> m1, pair<string,int> m2)
{
    return m1.second < m2.second;
}

int find_string(const char* input_string, int serial_number, int output_string_max_length, char* output_string)
{
    if ((input_string == NULL) || (output_string == NULL))
    {
        return -1;
    }

    map<string,int> m;
    stringstream io(input_string);
    string str_num_origin;
    while(io >> str_num_origin)
    {
        int num;
        istringstream temp(str_num_origin);
        temp >> num;
        if((num <= 0) || (num >= 1000000))
        {
            return -1;
        }
        if(num > 1000)
        {
            num %= 1000;
        }

        pair<string,int> p(str_num_origin,num);
        m.insert(p);
    }

    vector<pair<string,int>> vec;
    for(map<string,int>::iterator it=m.begin();it!=m.end();++it)
    {
        vec.push_back(*it);
    }

    sort(vec.begin(),vec.end(),comparator);

    if (serial_number > (int)vec.size())
    {
        return -1;
    }

    string str = vec.at(serial_number-1).first;
    if ((int)str.length() >= output_string_max_length)
    {
        return -1;
    }

    unsigned int i = 0;
    for(;i<str.length();i++)
    {
        output_string[i] = str[i];
    }
    output_string[i] = '\0';
    return 0;
}

int main() {
    {
        char *in_str = "1223 22 3232 2016";
        char out_str[5];

        std::cout << (0 == find_string(in_str, 3, sizeof(out_str), out_str)) << std::endl;
        std::cout << (0 == strcmp(out_str, "1223")) << std::endl;
    }



    {
        char *in_str = "1223 2223 3223 4223";
        char out_str[5];

        std::cout << (0 == find_string(in_str, 3, sizeof(out_str), out_str)) << std::endl;
        std::cout << (0 == strcmp(out_str, "3223")) << std::endl;
    }

    {
        char *in_str = "1223 2223 3223 4223 1123 2123 3123 4123";
        char out_str[5];

        std::cout << (0 == find_string(in_str, 3, sizeof(out_str), out_str)) << std::endl;
        std::cout << (0 == strcmp(out_str, "3123")) << std::endl;
    }

    {
        char *in_str = "-1 2223 3223 4223 1123 2123 3123 4123";
        char out_str[5];

        std::cout << (-1 == find_string(in_str, 3, sizeof(out_str), out_str)) << std::endl;
    }

    {
        char *in_str = "1000001 2223 3223 4223 1123 2123 3123 4123";
        char out_str[5];

        std::cout << (-1 == find_string(in_str, 3, sizeof(out_str), out_str)) << std::endl;
    }

    {
        char *in_str = "1223 2223 3223 4223 1123 2123 3123 4123";
        char out_str[5];

        std::cout << (-1 == find_string(in_str, 9, sizeof(out_str), out_str)) << std::endl;
    }
}
