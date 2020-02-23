/**
 * 大数求和
 * 描述:
 * 给定两个非常大的正整数A和B，位数在50至100之间。求C＝A+B；
 * 输入:
 * 因为A和B很大，从高位到低位，以字符串的形式输入两行数字A和B。A和B的位数在50至100之间。
 * 输出:
 * 以字符串形式，输出一行，表示A和B的和。
 * 样例输入:
 * 11111111111111111111111111111111111111111111111111
 * 22222222222222222222222222222222222222222222222222
 * 样例输出:
 * 33333333333333333333333333333333333333333333333333
 *
 */
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string first,second;
    string result;

    while(cin >> first >> second)
    {
        int i = first.size()-1;
        int j = second.size()-1;
        int i_first = 0;
        int i_second = 0;
        int i_result = 0;
        int carry = 0; //进位

        while((i >= 0) && (j >= 0)) //由于此处原因不能将i,j设为string::size_type类型
        {
            i_first = 0+first[i]-'0';
            i_second = 0+second[j]-'0';
            i_result = i_first+i_second+carry;

            if(i_result >= 10)
            {
                i_result -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            result = string(1,(char)('0'+i_result)).append(result);
            i--;
            j--;
        }

        if(i == -1)
        {
            while(j >= 0)
            {
                i_second = 0+second[j]-'0';
                i_result = i_second+carry;

                if(i_result >= 10)
                {
                    i_result -= 10;
                    carry =1;
                }
                else
                {
                    carry = 0;
                }

                result = string(1,(char)('0'+i_result)).append(result);
                j--;
            }
        }
        else
        {
            while(i >= 0)
            {
                i_first = 0+first[i]-'0';
                i_result = i_first+carry;

                if(i_result >= 10)
                {
                    i_result -= 10;
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }

                result = string(1,(char)('0'+i_result)).append(result);
                i--;
            }
        }

        if(carry == 1)
        {
            result = string(1,'1').append(result);
        }

        cout << result << endl;
    }

    return 0;
}
