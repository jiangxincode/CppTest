/*
已知一段英文密文的加密方法为：对原文中的每个字母，分别用字母表中该字母之后的第5个字母替换
比如：
“I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME”
的密文为
“N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ”
编写解密函数
*/

#include <iostream>
#include <string>

using namespace std;

int main2583()
{
    string str_src("N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ");

    for(auto &ch : str_src)
    {
        if(islower(ch))
        {
            auto diff = ch - 'a' - 5;
            ch = (diff>0)?(ch-5):(ch-5+26);
        }
        else if(isupper(ch))
        {
            auto diff = ch - 'A' - 5;
            ch = (diff>0)?(ch-5):(ch-5+26);
        }
    }

    cout << str_src << endl;
    return 0;
}
