/*
实现、调试使用二分法查找字符串的函数功能
（给定一个有序的字符串数组，查找其中是否包含指定字符串）。
请设计实现函数，并设计简单的例子以进行测试。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
char* Bin(char* sp[],char *str,int n,int *addr);
int main2592()
{
    int cn;
    char *cp;
    char *temp[] = {"li","qian","sun","zhao"};
    cp = Bin(temp,"sun",4,&cn);
    if(cp!=0)
        printf("%d\n",cn+1);
    return 0;
}
char* Bin(char* sp[],char *str,int n,int *addr)
{
    int left,right,mid;
    left = 0;
    right = n-1;
    while(left<=right)
    {
        mid = (left+right)/2;
        if(strcmp(str,sp[mid]<0))
            right = mid -1;
        else if(strcmp(str,sp[mid])>0)
            left = mid +1;
        else
        {
            *addr = mid;
            return (sp[mid]);
        }
    }
}
