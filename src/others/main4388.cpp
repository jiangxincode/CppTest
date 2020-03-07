/**
 * 指定字符删除
 * 题目描述：
 * 输入字符串s和字符c，要求去掉s中所有的c字符，并输出结果。
 * 接口说明：
 * 原型：
 * int removechars(char *in, char c, char *out);
 * 输入参数：
 *      char *in 输入字符串
 *         char c
 * 输出参数：
 *       char *out 输出处理后的字符串
 * 返回值：0：
 */
#include "iostream"
#include "cstring"
/*
功能: 字符串中删除指定字符

输入: in, c

输出: out

返回: 0

*/

int removechars(char *in, char c, char *out)
{
    int index_in = 0;
    int index_out = 0;
    while(in[index_in] != '\0')
    {
        if(in[index_in] != c)
        {
            out[index_out++] = in[index_in];
        }
        index_in++;
    }
    out[index_out] = '\0';
    return 0;
}

int main()
{
    char str[256];

    removechars("helloworld", 'c', str);

    std::cout << (0 == strcmp(str, "helloworld")) << std::endl;

    removechars("ccccccccc", 'c', str);

    std::cout << (0 == strcmp(str, "")) << std::endl;
}
