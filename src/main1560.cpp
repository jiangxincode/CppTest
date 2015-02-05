#include <iostream>
#include <initializer_list>

using namespace std;

int test_Ex_6_27(std::initializer_list<int> li);

int main1560()
{
    cout << test_Ex_6_27({23,78,89,76,90}) << endl;
    return 0;
}

int test_Ex_6_27(initializer_list<int> li)
{
    int result = 0;

    for(auto i = li.begin(); i != li.end(); i++)
    {
        result += *i;
    }

    return result;
}

/*****************************************************************
Ex_6_28:
elem是一个对string的常引用类型。

Ex_6_29:
个人觉得声明不声明成引用类型无所谓，首先加入不采用引用类型，就会
产生拷贝的开销，如果不考虑这种开销的话，两者应该是完全相同的，及时我们
采用引用类型，也不会改变initializer_list的值，因为它们永远是常量值，而且，
我们我们在采用引用类型时常常加上const限定。
*****************************************************************/
