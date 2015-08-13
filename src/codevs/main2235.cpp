/**
 * 2235 机票打折
 * 时间限制: 1 s
 * 空间限制: 32000 KB
 * 题目等级 : 青铜 Bronze
 * 题目描述 Description
 * 输入机票原价（3到4位的正整数，单位：元），再输入机票打折率（小数点后最多一位数字）。
 * 编程计算打折后机票的实际价格（单位：元。计算结果要将个位数四舍五入到十位数“元”）。
 * 输入只有一行两个数（两数间用一个空格分隔），第一个为整数，表示机票原价，第二个整数或实数（如是实数，小数点后最多1位数字）表示打折率。
 * 输入样例1：
 * 888  7
 * 输出样例1：
 * 620
 * 输入样例2：
 * 1255  7
 * 输出样例2：
 * 880
 * 输入描述 Input Description
 * 输入只有一行两个数（两数间用一个空格分隔），第一个为整数，表示机票原价，第二个整数或实数（如是实数，小数点后最多1位数字）表示打折率。
 * 输出描述 Output Description
 * 输出只有一行一个正整数，表示打折后的机票价格。
 *  样例输入 Sample Input
 *  888 7
 *  样例输出 Sample Output
 *  620
 *  数据范围及提示 Data Size & Hint
 *  原机票价格大于100小于9999，打折率大于1小于9.9。
 */
#include <iostream>

using namespace std;

int main2235()
{
    int price;
    float discount;
    int result;
    cin >> price >> discount;
    //价格与折扣率计算得到结果，结果保留到10位
    result = ((int)(price*(discount/10)+5))/10*10;
    cout << result;
    return 0;
}
