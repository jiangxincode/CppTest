/*判断一个数的奇偶性*/
#include <stdio.h>
int main1039()
{
    int a;
    scanf("%d",&a);

    if(a%2==0)
        printf("%d is even number",a);
    /*even number:偶数*/
    else
        printf("%d is odd number",a);

    /*odd number:奇数*/
    return 0;
}
