#include <stdio.h>

enum color {red,green,blue};
int main1042()
{
    enum color *p1,*p2,*p3;
    enum color R,G,B;
    R=red;
    G=green;
    B=blue;
    p1=&R;
    p2=&G;
    p3=&B;
    printf("%d,%d,%d",*p1,*p2,*p3);
    return 0;
}

