/*
http://wikioi.com/problem/1204/
*/
#include <iostream>
#include <string>

using namespace std;

int main009()
{
    string str_text;
    string str_query;
    cin >> str_text >> str_query;
    string::size_type pos = str_text.find(str_query);
    cout << pos+1;
    return 0;
}
