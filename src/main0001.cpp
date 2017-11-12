#include <stdio.h>
#include <stdlib.h>

struct my_struct1
{
    char var1;
    int var2;
    short var3;
};

struct my_struct2
{
    int var1;
    char var2;
    short var3;
};

int main()
{
    printf("%d\n", sizeof(struct my_struct1));
    printf("%d\n", sizeof(struct my_struct2));
    struct my_struct2 info;
    printf("%d %c %d", info.var1, info.var2, info.var3);
    return 0;
}

