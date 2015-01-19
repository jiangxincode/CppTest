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
    return 0;
}

