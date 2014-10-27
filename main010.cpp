/*
http://wikioi.com/problem/1205/
*/
#include <iostream>
#include <sstream> //注意是sstream，不是stringstring
#include <string>
#include <vector>

using namespace std;

int main010()
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
