/**
 * 1212 最大公约数
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 白银 Silver
 * 题目描述 Description
 * 求两个数A和B的最大公约数。 1<=A,B<=2^31-1
 * 输入描述 Input Description
 * 两个整数A和B
 * 输出描述 Output Description
 * 最大公约数gcd(A,B)
 * 样例输入 Sample Input
 * 8 12
 * 样例输出 Sample Output
 * 4
 * 数据范围及提示 Data Size & Hint
 */
#include <iostream>
#include <algorithm>

using namespace std;

static int gcd(int min, int max) {
    if (max % min == 0) {
        return min;
    } else {
        return gcd(max % min, min); //牛顿迭代相除法
    }
}

int main() {
    int A, B;
    cin >> A >> B;
    cout << gcd(min(A, B), max(A, B));
    return 0;
}
