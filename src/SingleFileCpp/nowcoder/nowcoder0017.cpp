/**
 * 坐标移动
 * https://www.nowcoder.com/practice/119bcca3befb405fbe58abe9c532eb29
 * 描述:
 * 开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。
 * 从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。
 * 输入：
 * 合法坐标为A(或者D或者W或者S) + 数字（两位以内），坐标之间以;分隔。非法坐标点需要进行丢弃。
 * 如AA10;  A1A;  $%$;  YAD; 等。
 * 下面是一个简单的例子 如：
 * A10;S20;W10;D30;X;A1A;B10A11;;A10;
 * 处理过程：
 * 起点（0,0）
 * +   A10   =  （-10,0）
 * +   S20   =  (-10,-20)
 * +   W10  =  (-10,-10)
 * +   D30  =  (20,-10)
 * +   x    =  无效
 * +   A1A   =  无效
 * +   B10A11   =  无效
 * +  一个空 不影响
 * +   A10  =  (10,-10)
 * 结果 （10， -10）
 * 输入:
 * 一行字符串
 * 输出:
 * 最终坐标，以,分隔
 * 样例输入:
 * A10;S20;W10;D30;X;A1A;B10A11;;A10;
 * 样例输出:
 * 10,-10
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

bool isProper(string str);

int main() {
    string input;
    while (cin >> input) {
        vector<string> vec;
        int result_x = 0, result_y = 0;


        string::size_type pos = input.find(";");
        while (pos != string::npos) {
            string temp = input.substr(0, pos);
            if (isProper(temp)) {
                vec.push_back(temp);
            }
            input = input.substr(pos + 1);
            pos = input.find(";");
        }

        for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
            string str_temp = *it;
            int i_temp = 0;

            istringstream iss(str_temp.substr(1));
            iss >> i_temp;

            /*A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动*/
            switch (str_temp[0]) {
                case 'A':
                    result_x -= i_temp;
                    break;
                case 'D':
                    result_x += i_temp;
                    break;
                case 'W':
                    result_y += i_temp;
                    break;
                case 'S':
                    result_y -= i_temp;
                    break;
                default:
                    break;
            }
        }

        cout << result_x << "," << result_y << endl;
    }
    return 0;
}

bool isProper(string str) {
    if ((str.length() < 2) || (str.length() > 3)) {
        return false;
    }
    if ((str[0] != 'A') && (str[0] != 'D') && (str[0] != 'W') && (str[0] != 'S')) {
        return false;
    }
    if ((str[1] < '0') || (str[1] > '9')) {
        return false;
    }
    if ((str.length() == 3) && ((str[2] < '0') || (str[2] > '9'))) {
        return false;
    }
    return true;
}
