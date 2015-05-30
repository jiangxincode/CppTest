#include <stdio.h>
#include <stdlib.h>

int my_convert(char *s);

int main0030(int argc, char *argv[])
{
    int a, b, c;

    if(argc != 3)
    {
        return -1;
    }

    a = my_convert(argv[1]);
    b = my_convert(argv[2]);
    c = a + b;
    printf("%d\n",c);
    return c;
}

int my_convert(char *s)
{
    return atoi(s);
}


