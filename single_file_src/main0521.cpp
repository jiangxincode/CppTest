#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

int main05211()
{
    vector<int> vec(10,1);
    vector<int>::iterator it;

    for(it=vec.begin(); it!=vec.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
    iota(vec.begin(),vec.end(),0);

    for(it=vec.begin(); it!=vec.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
    string str1 = "hello";
    string str2 = "llohe";
    cout << boolalpha << is_permutation(str1.begin(),str1.end(),str2.begin()) << endl;

    while(next_permutation(str1.begin(),str1.end()))
    {
        cout << str1 << endl;
    }

    return 0;
}

int main05212()
{
    return 0;
}
int main()
{
    main05212();
    return 0;
}
