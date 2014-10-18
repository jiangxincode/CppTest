#include <iostream>
#include <map>
#include <set>

using namespace std;

void test_map()
{
    // ͳ��ÿ�������������г��ֵĴ���
    map<string,size_t> word_count;
    string word;

    while(cin >> word)
    {
        ++word_count[word];
    }

    for(const auto w : word_count)
    {
        cout << w.first << " occurs " << w.second << ((w.second>1)?" times":" time") << endl;
    }
}

void test_set()
{
    // ͳ���������ų��ض����ʵ�ÿ�����ʳ��ֵĴ���
    map<string,size_t> word_count;
    set<string> exclude = {"The","But","And","Or","An","A","the","but","and","or","an","a"};
    string word;

    while(cin >> word)
    {
        if(exclude.find(word) == exclude.end())
        {
            ++word_count[word];
        }
    }

    for(const auto w : word_count)
    {
        cout << w.first << " occurs " << w.second << ((w.second>1)?" times":" time") << endl;
    }
}
int main1610()
{
    test_set();
    return 0;
}
