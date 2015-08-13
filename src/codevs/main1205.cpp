/**
 * 1205 单词翻转






 时间限制: 1 s



 空间限制: 128000 KB



 题目等级 : 青铜 Bronze

题目描述 Description


给出一个英语句子，希望你把句子里的单词顺序都翻转过来


 输入描述 Input Description


输入包括一个英语句子。


 输出描述 Output Description


按单词的顺序把单词倒序输出


 样例输入 Sample Input


I love you


样例输出 Sample Output


you love I


数据范围及提示 Data Size & Hint


简单的字符串操作

*/
#include <iostream>
#include <sstream> //注意是sstream，不是stringstring
#include <string>
#include <vector>

using namespace std;

int main1205()
{
    string word, str_input;
    getline(cin, str_input); //注意getline的用法
    vector<string> vec;
    stringstream strstr_input(str_input);

    while(strstr_input >> word)
    {
        vec.push_back(word);
    }

    //注意既然下面要使用反向迭代器，所以类型也要声明为方向迭代器
    vector<string>::reverse_iterator pos;

    for(pos=vec.rbegin(); pos!=vec.rend(); ++pos) //主要反向迭代器一定要++不是--
    {
        cout << *pos << " ";
    }

    return 0;
}
