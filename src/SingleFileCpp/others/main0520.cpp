/**
 * 有9个整数｛1，2，3，4，5，6，7，8，9｝在中间任何位置加上‘+’或者‘-’号使成为一个表达式，
 * 这个表达式的值要等于你输入的一个整数，
 * 要你输出有多少种这样的表达式它的值等于你输入的这个数
 * 例如：
 * 123-4+56-78+9=106
 * XXXXXXXXXXX=106
 * .........
 * XXXXXXXXXXX=106
 * 最后输出表达式的个数
 * 可以参见如下讨论：https://bbs.csdn.net/topics/390592099
 */
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int calcExpress(string express) {
    int result = 0;
    for (size_t i=0;i<express.size();i++) {
        char ch = express.at(i);
        if (ch == '+') {
            int num = 0;
            i++;
            while (i < express.size() && express.at(i) >= '1' && express.at(i) <= '9') {
                num = num * 10 + express.at(i) - '0';
                i++;
            }
            i--;
            result += num;
        } else if (ch == '-') {
            int num = 0;
            i++;
            while (i+1 < express.size() && express.at(i) >= '1' && express.at(i) <= '9') {
                num = num * 10 + express.at(i) - '0';
                i++;
            }
            i--;
            result -= num;
        }
    }
    return result;
}

void constructVec(vector<string> &stringVec, string currentExpress, string remainExpress) {
    if (remainExpress.empty()) {
        stringVec.push_back(currentExpress);
        return;
    }
    string first = remainExpress.substr(0, 1);
    remainExpress = remainExpress.substr(1, remainExpress.size() - 1);
    constructVec(stringVec, currentExpress + first, remainExpress);
    constructVec(stringVec, currentExpress + "+" + first, remainExpress);
    constructVec(stringVec, currentExpress + "-" + first, remainExpress);
}

int main() {
    vector<string> stringVec;
    constructVec(stringVec, "1", "23456789");
    int targetValue;
    cin >> targetValue;
    for (size_t i=0;i<stringVec.size();i++) {
        string tmp = stringVec.at(i);
        if (calcExpress("+" + tmp) == targetValue) {
            std::cout << tmp << std::endl;
        }
    }
    return 0;
}

