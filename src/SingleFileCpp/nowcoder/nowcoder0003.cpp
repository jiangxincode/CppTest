/**
 * 挑7
 * https://www.nowcoder.com/practice/ba241b85371c409ea01ac0aa1a8d957b
 * 描述:  输出7有关数字的个数，包括7的倍数，还有包含7的数字（如17，27，37...70，71，72，73...）的个数
 * 输入:  一个正整数N。(N不大于30000)
 * 输出:  不大于N的与7有关的数字个数，例如输入20，与7有关的数字包括7,14,17.
 * 样例输入: 20
 * 样例输出: 3
 */

#include <iostream>

using namespace std;

bool isProper(unsigned int n) {
    if (n % 7 == 0) {
        return true;
    }

    while (n != 0) {
        if (n % 10 == 7) {
            return true;
        }
        n /= 10;
    }
    return false;
}

int main() {
    unsigned int input;
    while (cin >> input) {
        unsigned int count = 0;
        for (unsigned int i = 1; i <= input; i++) {
            if (isProper(i)) {
                count++;
            }
        }
        cout << count << endl;
    }
    return 0;
}
