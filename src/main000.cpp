#include <iostream>

using namespace std;

int main000()
{
#ifdef __WIN32__
    cout << "WIN32" << endl;
#endif // WIN32

#ifdef __LINUX
    cout << "LINUX" << endl;
#endif // LINUX
    return 0;
}
