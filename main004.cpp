/*
http://wikioi.com/problem/1201/
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main004()
{
    int input_num;
    int input_temp;
    vector<int> vec;
    cin >> input_num;

    for(int i=0; i<input_num; i++)
    {
        cin >> input_temp;
        vec.insert(vec.end(),input_temp);
    }

    int min = *min_element(vec.begin(),vec.end());
    int max = *max_element(vec.begin(),vec.end());
    cout << min << " " << max;
    return 0;
}
