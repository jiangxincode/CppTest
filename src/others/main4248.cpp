#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    unsigned int input;
    unsigned int result = 0;
    string str = "";
    cin >> input;

    while(input != 0)
    {
        str += '0'+input%2;
        input /= 2;
    }

    string strReverse = str;
    reverse_copy(str.begin(),str.end(),strReverse.begin());

    for(string::iterator it=strReverse.begin(); it!=strReverse.end(); ++it)
    {
        if((*it) == '1')
        {
            for(string::iterator temp=it; temp!=strReverse.end(); ++temp)
            {
                if((*temp) == '0')
                {
                    result++;
                }
            }

            break ;
        }
    }

    cout << result;
    return 0;
}
