#include <stdio.h>
#include <stdlib.h>

/** \cond */
int main0013()
{
    /**
     * 验证是否可以通过其它指针来修改常量指针（一个指向常量的指针）
     */
    /*
        const int a = 10;
        int *ptr_a = &a; //warning: initialization discards 'const' qualifier from pointer target type
        *ptr_a = 20; //虽然之前报warning，但是依然可以修改其值
        printf("%d\n",a); //此处输出20
    */
    /**
     * 验证对指针进行sizeof()运算的值
     */
    char str[100] = "hello";
    char *p = str;
    printf("%d\n",sizeof(p));  //此处输出4
    printf("%d\n",sizeof(char));  //此处输出1
    return 0;
}
/** \endcond */
