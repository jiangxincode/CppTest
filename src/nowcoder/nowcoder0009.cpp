/**
 * 英文句子单词翻转
 * https://www.nowcoder.com/practice/8a4ce890ed764de3adda860695a3ac57
 * 原地翻转句子中单词的顺序，但单词内字符的顺序不变。要求：空间复杂度O(1)，时间复杂度O(n)。
 * 输入描述：
 * 英文句子中单词以一个空格符隔开。为简单起见，标点符号和普通字母一样处理。
 * 输出描述：
 * 翻转之后的英文句子，单词内字符的顺序不变，以一个空格隔开。
 * 示例1
 * 输入
 * I am a student.
 * 输出
 * student. a am I
 */
#include<iostream>

#include "stdio.h"
#include "string.h"

using namespace std;

void reverseStr(char *str, size_t i, size_t j) {
    while (i < j) {
        char tmp;
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}


int main(int argc, char **argv) {
    char str[1024];
    // 由于gets是非安全函数，可能导致内存溢出，在Linux平台上已经废弃使用，所以使用scanf替代
    // fgets和gets虽然都是读取一行，但是前者会把换行符读到，后者不会
    while (fgets(str, sizeof(str) - 1, stdin) != NULL) {
        // 处理多读取的'\n'
        str[strlen(str) - 1] = '\0';
        reverseStr(str, 0, strlen(str) - 1);
        size_t i = 0;
        while (str[i] != '\0') {
            if (str[i] == ' ') {
                i++;
                continue;
            }
            size_t start = i;
            while (str[i] != ' ' && str[i] != '\0') {
                i++;
            }
            size_t end = i - 1;
            reverseStr(str, start, end);
        }
        printf("%s\n", str);
    }
    return 0;
}





