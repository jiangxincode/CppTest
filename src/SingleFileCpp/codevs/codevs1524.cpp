/**
 * 1524 残缺的数字
 * 时间限制: 1 s
 * 空间限制: 1000 KB
 * 题目等级 : 黄金 Gold
 * 题目描述 Description
 * 可怜的小小在数数字……。本来有1..n这n个数，但是她一不小心数没了一个数X。如果这个事情被残酷的Evil Zig 发现，那么这个可怜的小女孩将会……。为了拯救小小我们必须找到那个失踪的数X！现在我们现在只知道 0..9个十个数字在这剩下的N-1个数中分别出现的次数，你必须以次求出N和X。若有多组解，则全部输出，每行一组。
 * 输入描述 Input Description
 * 仅有一行，包含10个数，分别表示0 .. 9在n-1个数字中出现的次数。( 每个数均不大于300 )
 * 输出描述 Output Description
 * 输入所有可能的N和X，每组一行。按从小到大的顺序排序（N为第一关键字，X为第二关键字）。若无解，输出“NO ANSWER”。
 * 样例输入 Sample Input
 * 0 1 1 0 1 1 1 1 1 1
 * 样例输出 Sample Output
 * 9 3
 * 数据范围及提示 Data Size & Hint
 */
#include <iostream>

int main() {
    int inputDigitCount[10];
    for (int i=0;i<10;i++) {
        std::cin >> inputDigitCount[i];
    }
    for (int i=1;i<=3000;i++) {
        int sumDigitCount[10] = {0};
        for (int j=1;j<=i;j++) {
            int tmp = j;
            while (tmp > 0) {
                sumDigitCount[tmp % 10]++;
                tmp /= 10;
            }
        }
        bool isTooBig = false;
        for (int j=0;j<10;j++) {
            if (sumDigitCount[j] > 300) {
                isTooBig = true;
            }
        }
        if (isTooBig) {
            continue;
        }


        for (int j=1;j<=i;j++) {
            int specialDigitCount[10] = {0};
            int tmp = j;
            while (tmp > 0) {
                specialDigitCount[tmp % 10]++;
                tmp /= 10;
            }
            bool jIsX = true;
            for (int k=0;k<10;k++) {
                if (inputDigitCount[k] != sumDigitCount[k]-specialDigitCount[k]) {
                    jIsX = false;
                    break;
                }
            }
            if (jIsX) {
                std::cout << i << " " << j << std::endl;
                return 0;
            }
        }

    }
    std::cout << "NO ANSWER" << std::endl;
}

