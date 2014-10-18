#include <iostream>
#include <map>
#include <set>

using namespace std;

void test_map()
{
    // 统计每个单词在输入中出现的次数
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
    // 统计输入中排除特定单词的每个单词出现的次数
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
