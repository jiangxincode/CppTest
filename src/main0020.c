
#include <stdio.h>

int main25191()

{
    double c,mj,C;
    scanf("%20lf",&c);
    mj=3.14*c*c;
    C=6.28*c;
    printf("%.2f,%.2f",mj,C);
    return 0;
}

int main25192()

{
    static const double PI = 3.14159;
    double r, s, l;
    printf("Please input the radius of a circle(cm):");
    scanf("%20lf", &r);
    s = PI * r * r;
    l = 2 * PI * r;
    printf("The area of the circle is %.2f cm2 and the perimeter is %.2f cm.", s, l);
    //The area and perimeter are rounded to the nearest hundredth.
    return 0;
}
int main0020()
{
    return 0;
}
