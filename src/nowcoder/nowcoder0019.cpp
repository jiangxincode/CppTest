/**
 * 水仙花数
 * https://www.nowcoder.com/practice/11c9f023a9f84418a15b48792a5f7c70
 * https://www.nowcoder.com/practice/dc943274e8254a9eb074298fb2084703
 * 题目描述
 * 春天是鲜花的季节，水仙花就是其中最迷人的代表，数学上有个水仙花数，他是这样定义的：“水仙花数”是指一个三位数，它的各位数字的立方和等于其本身，比如：153=1^3+5^3+3^3。 现在要求输出所有在m和n范围内的水仙花数。
 * 输入描述:
 * 输入数据有多组，每组占一行，包括两个整数m和n（100<=m<=n<=999）。
 * 输出描述:
 * 对于每个测试实例，要求输出所有在给定范围内的水仙花数，就是说，输出的水仙花数必须大于等于m,并且小于等于n，如果有多个，则要求从小到大排列在一行内输出，之间用一个空格隔开;如果给定的范围内不存在水仙花数，则输出no;每个测试实例的输出占一行。
 * 示例1
 * 输入
 * 100 120
 * 300 380
 * 输出
 * no
 * 370 371
 */
#include <iostream>

using namespace std;

/**
 * 水仙花数
 * 水仙花数又称阿姆斯特朗数。
 * 水仙花数是指一个n 位数( n≥3 )，它的每个位上的数字的n 次幂之和等于它本身。（例如：1^3 + 5^3 + 3^3 = 153）
 * 求输入的数字是否为水仙花数
 */
int isArmstrong(int num) {
    int temp = num;
    int result = 0;
    int bit_count = 0; //数字的位数
    int bit[1024]; //存放各位数字

    if (num <= 0) //只对正整数进行判断
    {
        return 0;
    }

    for (int i = 0; i < 1024; i++) //初始化
    {
        bit[i] = -1;
    }

    while (temp) {
        bit[bit_count++] = temp % 10;
        temp /= 10;
    }

    for (int i = 0; bit[i] != -1; i++) {
        int itemp = 1;
        for (int j = 0; j < bit_count; j++) {
            itemp *= bit[i];
        }
        result += itemp;
    }

    if (result == num) {
        return 1;
    } else return 0;
}

/**
 * 阿姆斯特朗数
 * 如果一个正整数等于其各个数字的立方和，则该数称为阿姆斯特朗数(亦称为自恋性数)，1除外，如407 = 43+03+73就是一个阿姆斯特朗数。试编程求n(n ≤ 65536)以内的所有阿姆斯特朗数。
 * 接口说明
 * 原型：int CalcArmstrongNumber(int n);
 * 输入参数：int n: n ≤ 65536
 * 返回值：n以内的阿姆斯特朗数的数量
 */
int CalcArmstrongNumber(int n) {
    int result = 0;
    for (int i = 2; i < n; i++) {
        if (isArmstrong(i)) {
            result++;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    //cout << CalcArmstrongNumber(400) << endl; // 3
    //cout << isArmstrong(153) << endl; // 1
    //cout << isArmstrong(151) << endl; // 0

    size_t begin;
    size_t end;
    while (scanf("%u %u", &begin, &end) > 0) {
        bool isFirst = true;
        for (size_t i = begin; i <= end; i++) {
            if (isArmstrong(i) == 1) {
                if (isFirst) {
                    cout << i;
                    isFirst = false;
                } else {
                    cout << " " << i;
                }
            }
        }
        if (isFirst) {
            cout << "no" << endl;
        } else {
            cout << endl;
        }
    }
}
