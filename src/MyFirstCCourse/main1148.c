#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * 在一段语句中查找特定单词出现的次数
 */
int count(char sentence[], char words[][10], size_t n, size_t b[]) {
    size_t j, k;

    for (size_t p = 0; p < n; p++)
        for (size_t i = 0; sentence[i] != '\0'; i++) {
            for (k = 0, j = i; words[p][k] != '\0' && words[p][k] == sentence[j]; k++, j++);

            if (k > 0 && words[p][k] == '\0' && !isalpha(sentence[i - 1])) {
                b[p]++;
                i = i + strlen(words[p]);
            }
        }

    return 0;
}

int main() {
    char sentence[50] = {"this is sentence book, that is an apple"};
    char words[][10] = {"is", "that"};
    size_t b[20] = {0};
    count(sentence, words, 2, b);

    for (size_t i = 0; i < 2; i++) {
        printf("%s, %d\n", words[i], b[i]);
    }

    return 0;
}



