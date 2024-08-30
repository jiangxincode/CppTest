#include <iostream>

using namespace std;

void testReference1(int &r);
void testReference2();

int main(int argc, char *argv[])
{
    testReference2();
}

void testReference1(int &r) {
    r += 10;
}

void testReference2() {
    int i = 10;
    int &r = i;
    int *p = &i;
    testReference1(i);
    cout << "i = " << i << ", r = " << r << ", *p = " << *p << endl;
    testReference1(r);
    cout << "i = " << i << ", r = " << r << ", *p = " << *p << endl;
    testReference1(*p);
    cout << "i = " << i << ", r = " << r << ", *p = " << *p << endl;
}

