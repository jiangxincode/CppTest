#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main0556()
{
    vector<int> vec;
    back_insert_iterator<vector<int>> it1 = back_inserter(vec);
    front_insert_iterator<vector<int>> it2 = front_inserter(vec);
    insert_iterator<vector<int>> it3 = inserter(vec,vec.begin());
    *it1 = 42;
    *it1 = 43;

    cout << vec.size() << endl;
    vector<int>::iterator it4 = vec.begin();
    return 0;
}
