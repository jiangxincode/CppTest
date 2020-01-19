/**
 * 字符逆序（字符串反转）
 * https://www.nowcoder.com/practice/cc57022cb4194697ac30bcb566aeb47b
 * https://www.nowcoder.com/practice/e45e078701ab4e4cb49393ae30f1bb04
 * 将一个字符串str的内容颠倒过来，并输出。str的长度不超过100个字符。 如：输入“I am a student”，输出“tneduts a ma I”。
 * 输入参数：
 * inputString：输入的字符串，可以有空格
 * 返回值：
 * 输出转换好的逆序字符串
 * 需要注意的是，该题和单词翻转之间的区别！单词翻转输入“I am a student.”，则输出“student.a am I”。
 */

#include <stdio.h>
#include <string.h>

/**
 * 反转字符串
 *
 * @param str 要反转的字符串
 * @param length 字符串长度（不含结束符）
 */
void reverseStr(char *str, size_t length) {
    for (int i = 0, j = length - 1; i < j; i++, j--) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    return;
}

int main(int argc, char **argv) {
    char str[1024];
    // 由于gets是非安全函数，可能导致内存溢出，在Linux平台上已经废弃使用，所以使用scanf替代
    // fgets和gets虽然都是读取一行，但是前者会把换行符读到，后者不会
    while (fgets(str, sizeof(str) - 1, stdin) != NULL) {
        // 如果不让使用任何系统函数，包括strlen，可以通过遍历字符串数组找到'\0'的位置来确定length
        size_t length = strlen(str);

        // 处理多读取的'\n'
        if (str[length - 1] == '\n') {
            str[length - 1] = '\0';
            length--;
        }

        reverseStr(str, length);
        printf("%s\n", str);
    }
    return 0;
}





