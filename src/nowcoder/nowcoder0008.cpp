/**
 * 字符逆序
 * https://www.nowcoder.com/practice/cc57022cb4194697ac30bcb566aeb47b
 * 将一个字符串str的内容颠倒过来，并输出。str的长度不超过100个字符。 如：输入“I am a student”，输出“tneduts a ma I”。
 * 输入参数：
 * inputString：输入的字符串，可以有空格
 * 返回值：
 * 输出转换好的逆序字符串
 * 需要注意的是，该题和单词翻转之间的区别！单词翻转输入“I am a student.”，则输出“student.a am I”。
 */

#include "stdio.h"
#include "string.h"

using namespace std;

void reverseStr(char *str, int i, int j) {
    for (; i < j; i++, j--) {
        char tmp;
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    return;
}

int main(int argc, char **argv) {
    char str[1024];
    while (gets(str)) {
        reverseStr(str, 0, strlen(str) - 1);
        printf("%s\n", str);
    }
    return 0;
}





