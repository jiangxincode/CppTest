/*
http://wikioi.com/problem/1205/
*/
#include <iostream>
#include <sstream> //ע����sstream������stringstring
#include <string>
#include <vector>

using namespace std;

int main010()
{
    string word, str_input;
    getline(cin, str_input); //ע��getline���÷�
    vector<string> vec;
    stringstream strstr_input(str_input);

    while(strstr_input >> word)
    {
        vec.push_back(word);
    }

    //ע���Ȼ����Ҫʹ�÷������������������ҲҪ����Ϊ���������
    vector<string>::reverse_iterator pos;

    for(pos=vec.rbegin(); pos!=vec.rend(); ++pos) //��Ҫ���������һ��Ҫ++����--
    {
        cout << *pos << " ";
    }

    return 0;
}
