/*
 *  2010年09月无线底软技能鉴定试题
 *  将一个字符串一分为二，左边部分按ASCII值降序排序，右边部分按ASCII值升值排序
 */
#include <string.h>
#include <stdio.h>

void sort(char *str) {
    for (int i = 0; i < strlen(str) / 2; i++) {
        for (int j = i + 1; j < strlen(str) / 2; j++)
            if (str[i] < str[j]) {
                int temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
    }

    for (int i = strlen(str) / 2; i < strlen(str); i++) {
        for (int j = i + 1; j < strlen(str); j++) {
            if (str[i] > str[j]) {
                int temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    char test[256] = "abcdefghijklmn";
    printf("%s\n", test);
    sort(test);
    printf("%s\n", test);
}

