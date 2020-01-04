/**
 * 最大递减数
 * 给出一个非负整数，找到这个非负整数中包含的最大递减数。一个数字的递减数是指相邻的数位从大到小排列的数字。
 * 如： 95345323，递减数有：953,95,53,53,532,32, 那么最大的递减数为953。
 * 如果输入的数字为负数，返回-1。
 */

#include <string>
#include <sstream>
#include <iostream>
#include <climits>

using namespace std;

int getMaxDegressiveNum(int num) {
    if (num < 0) {
        return -1;
    }
    stringstream ss = stringstream();
    string str;
    ss << num;
    ss >> str;

    int max = INT_MIN;

    for (unsigned int i = 0; i < str.length(); i++) {
        int temp = str[i] - '0';
        while ((i + 1 < str.length()) && (str[i] > str[i + 1])) {
            i++;
            temp = temp * 10 + str[i] - '0';
        }
        if (temp > max) {
            max = temp;
        }
    }
    return max;
}

int main() {
    cout << getMaxDegressiveNum(95345323) << endl; // 953
    cout << getMaxDegressiveNum(234565432) << endl; // 65432
    cout << getMaxDegressiveNum(-11) << endl; // -1
    cout << getMaxDegressiveNum(0) << endl; // 0
    return 0;
}
