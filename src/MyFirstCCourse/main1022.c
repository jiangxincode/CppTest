#include <stdio.h>

int main()
{
    int a,b,add,minus,multiply,divide;
    printf("input two intergers: ");
    scanf("%11d%11d",&a,&b);
    add = a + b;
    minus = a - b;
    multiply = a * b;

    if(b == 0)
    {
        printf("error!");
    }
    else
    {
        divide = a / b;
    }

    printf("%d+%d=%d,%d-%d=%d,%d*%d=%d,%d/%d=%d",a,b,add,a,b,minus,a,b,multiply,a,b,divide);
    return 0;
}
