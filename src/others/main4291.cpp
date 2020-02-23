/**
 * 简单错误记录
 * 描述：
 * 开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。
 * 处理：
 * 1.记录最多8条错误记录，循环记录，对相同的错误记录（净文件名称和行号完全匹配）只记录一条，
 * 错误计数增加；
 * 2.超过16个字符的文件名称，只记录文件的最后有效16个字符；
 * 3.输入的文件可能带路径，记录文件名称不能带路径。
 * 输入:
 * 一行或多行字符串。每行包括带路径文件名称，行号，以空格隔开。
 * 如：E:\V1R2\product\fpgadrive.c   1325
 * 输出:
 * 将所有的记录统计并将结果输出，格式：文件名 代码行数 数目，一个空格隔开，如：
 * fpgadrive.c 1325 1
 * 样例输入:
 * E:\V1R2\product\fpgadrive.c   1325
 * E:\V1R2\product\fpgadrive.c   1325
 * E:\V1R2\product\abc.c   345
 * E:\V1R2\product\fpgadrive.c   999
 * E:\V1R2\product\fpgadrive.c   999
 * E:\V1R2\product\gadrive.c   1325
 * E:\V1R2\product\fpgive.c   1325
 * E:\V1R2\product\ac.c   345
 * E:\V1R2\product\fprive.c   999
 * E:\V1R2\product\fpgadive.c   999
 * 样例输出:
 * fpgadrive.c 1325 2
 * abc.c 345 1
 * fpgadrive.c 999 2
 * gadrive.c 1325 1
 * fpgive.c 1325 1
 * ac.c 345 1
 * fprive.c 999 1
 * fpgadive.c 999 1
 *
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>

using namespace std;

int main()
{
    char s[BUFSIZ];
    char store[8][17] = {{0}};
    int counts[8] = {0};
    int rows[8] = {0};
    int row = 0; //行数
    int amount = 0; //一共有多少条记录

    string input;

    /*其实可以不判断input，因为在OJ中一旦读入文件末尾就getline失效了 */
    while((getline(cin,input)) && (amount<8))
    {
        if(input.size() <= 1)
        {
            break;
        }
        stringstream io(input);
        io >> s >> row;
        int pos = 0;

        for(int i = 15; i >= 0; i--)
        {
            if(s[i] == '\\')
            {
                pos = i;
                break;
            }
        }

        int isEqual = 0;

        for(int j = 0; j < amount; j++)
        {
            if(strcmp(store[j],&(s[pos+1])) == 0 && row == rows[j])
            {
                isEqual = 1;
                counts[j]++;
                break;
            }
        }

        if(!isEqual)
        {
            strcpy(store[amount], &s[pos+1]);
            rows[amount] = row;
            counts[amount]++;
            amount ++;
        }
    }

    for(int j = 0; j < amount; j++)
    {
        cout << store[j] << " " << rows[j] << " " << counts[j] << endl;
    }

    return 0;
}
