# include <stdio.h>

int main0029()
{
    int max(int x, int y);
    int a, b, c,i=1;

    while(i!=0)
    {
        printf("Please input the numbers that you want to compare:\n");
        scanf("%d%d", &a, &b);
        c = max(a, b);
        printf("max = %d\n",c);
        printf("Continue?\nyes press 1\nno press 0\n");
        scanf("%d",&i);
    }

    return 0;
}

// 求两个整数中的较大者的max 函数
int max(int x, int y)
{
    int z;

    if(x > y)
    {
        z = x;
    }
    else
    {
        z = y;
    }

    return (z);
}
