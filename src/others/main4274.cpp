/**
 * 字符变换
 * 描述:
 * 输入一个字符串，将其中大写字母转换为对应小写字母之后的第五个字母，
 * 若原始大写字母为V～Z, 则转换为对应小写字母的值减21。
 * 其他字符不变，输出转换后的字符串。
 * 例如，对于字母A，则转换为小写字母f；若形参是字母W，则转换为小写字母b。
 * 输入:
 * 字符串
 * 输出:
 * 转换后的字符串
 * 样例输入: Axs3mWss
 * 样例输出: fxs3mbss
 *
 */
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string strInput;
    cin >> strInput;

    for(string::iterator it=strInput.begin(); it!=strInput.end(); ++it)
    {
        char ch = *it;

        if((ch>='A') && (ch<'V'))
        {
            *it = *it+'a'-'A'+5;
        }
        else if((ch>='V') && (ch<='Z'))
        {
            *it = *it+'a'-'A'-21;
        }
    }

    cout << strInput;
    return 0;
}
