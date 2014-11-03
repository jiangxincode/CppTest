#include <iostream>
#include <string>

using namespace std;

int main0512()
{
    string s1 = "abcdefg";
    const char *s2 = s1.c_str();
    const char *s3 = s1.data();
    char *s4 = new char[s1.length()+1];
    s1.copy(s4,s1.length(),0);
    cout << "s1 is: " << s1 << "s2 is: " << s2 << "s3 is: " << s3 << "s4 is: " << s4 << endl;
    return 0;
}
