/**
 * 密码验证合格程序
 * 描述:
 * 密码要求:
 * 1.长度超过8位
 * 2.包括大小写字母.数字.其它符号,以上四种至少三种
 * 3.不能有相同长度超2的子串重复
 * 说明:长度超过2的子串
 * 输入:
 * 一组或多组长度超过2的子符串。每组占一行
 * 输出:
 * 如果符合要求输出：OK，否则输出NG
 * 每行输出对应一组输入的结果；
 * 样例输入:
 * 021Abc9000
 * 021Abc9Abc1
 * 021ABC9000
 * 021$bc9000
 * 样例输出:
 * OK
 * NG
 * NG
 * OK
 *
 */
#include <iostream>
#include <cctype>
#include <cstdio>
#include <string>

using namespace std;

int main()
{
    string password;

    while(cin >> password)
    {
        int up_letter = 0;
        int low_letter = 0;
        int digit = 0;
        int other = 0;

        string::size_type len = password.size();

        if(password.size() <= 8)
        {
            cout << "NG" << endl;
            continue;
        }

        for(string::size_type i=0; i<len; i++)
        {
            char ch = password.at(i);

            if(isdigit(ch))
            {
                digit = 1;
            }
            else if(islower(ch))
            {
                low_letter = 1;
            }
            else if(isupper(ch))
            {
                up_letter = 1;
            }
            else if(isprint(ch))
            {
                other = 1;
            }
        }

        if(digit + low_letter + up_letter + other <  3)
        {
            cout<<"NG"<<endl;
            continue;
        }

        int same_len = 0;

        for(string::size_type j = 0; j < password.size(); j++)
        {
            string::size_type tmp = j;

            for(string::size_type k = 0; k < j; k++)
            {
                if(password[tmp] == password[k])
                {
                    same_len++;
                    tmp++;

                    if(same_len > 2)
                    {
                        break;
                    }
                }
                else
                {
                    same_len = 0;
                    tmp = j;
                }
            }

            if(same_len > 2)
            {
                break;
            }
        }

        if(same_len > 2)
        {
            cout << "NG" << endl;
        }
        else
        {
            cout << "OK" << endl;
        }
    }

    return 0;
}
