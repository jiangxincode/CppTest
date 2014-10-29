#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <forward_list>

using namespace std;

void test_string();
void EX_9_27();
void Ex9_52();
void EX_9_41();
void EX_9_47();

void test_string()
{
    string s = "pi = 3.14";
    double d = stod(s.substr(s.find_first_of("+-.0123456789")));
    cout << d << endl;
}
void EX_9_27()
{
    forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
    auto prev = flst.before_begin();
    auto curr = flst.begin();

    while(curr != flst.end())
    {
        if((*curr)%2 != 0)
        {
            curr = flst.erase_after(prev);
        }
        else
        {
            prev = curr;
            curr ++;
        }
    }

    for(auto i : flst)
    {
        cout << i << " ";
    }
}
void EX_9_41()
{
    vector<char> vec_char = {'h','e','l','l','o'};
    string s;
    s.assign(vec_char.begin(),vec_char.end());
    cout << s;
}
void EX_9_47()
{
    string str("ab2c3d7R4E6");
    string num("0123456789");
    string alpha_1("abcdefghigklmnopqrstuvwxyz");
    string alpha_2 =("ABCDEFGHIGKLMNOPQRSTUVWXYZ");
    size_t pos = 0;

    while((pos = str.find_first_of(num,pos))!=string::npos)
    {
        cout << "Found: " << str[pos] << endl;
        pos ++;
    }
}
int main1590()
{
    test_string();
    return 0;
}
