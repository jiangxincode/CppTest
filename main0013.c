#include <stdio.h>
#include <stdlib.h>

int main0013()
{
    /**
     * ��֤�Ƿ����ͨ������ָ�����޸ĳ���ָ�루һ��ָ������ָ�룩
     */
    /*
        const int a = 10;
        int *ptr_a = &a; //warning: initialization discards 'const' qualifier from pointer target type
        *ptr_a = 20; //��Ȼ֮ǰ��warning��������Ȼ�����޸���ֵ
        printf("%d\n",a); //�˴����20
    */
    /**
     * ��֤��ָ�����sizeof()�����ֵ
     */
    char str[100] = "hello";
    char *p = str;
    printf("%d\n",sizeof(p));  //�˴����4
    printf("%d\n",sizeof(char));  //�˴����1
    return 0;
}
