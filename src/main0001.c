#include <stdio.h>
#include <stdlib.h>

typedef struct info
{
//    char Var1;
//    int Var2;
//    short Var3;
    int Var1;
    char Var2;
    short Var3;
} INFO;

int main0001()
{
    int length = sizeof(INFO);
    printf("%d", length);
    INFO info;
    printf("%d %c %d", info.Var1, info.Var2, info.Var3);
    return 0;
}

