#include <stdio.h>

/**
 * 两个int类型的数据，不用任何的判断语句如if、switch、?:等，找出其中的大值
 */
int max1(int x,int y)
{
    int buf[2] = {x,y};
    unsigned int z;
    z = x-y;
    z >>= 31;
    return buf[z];
}

int max2(int a, int b)
{
    return (a>=b)*a + (a<b)*b;
}

int main0000()
{
    printf("%d", max1(2,3));
    printf("%d", max1(3,2));

    printf("%d", max2(2,3));
    printf("%d", max2(3,2));

    return 0;
}
