#include <iostream>

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
    std::cout << "i = " << i << ", r = " << r << ", *p = " << *p << std::endl;
    testReference1(r);
    std::cout << "i = " << i << ", r = " << r << ", *p = " << *p << std::endl;
    testReference1(*p);
    std::cout << "i = " << i << ", r = " << r << ", *p = " << *p << std::endl;
}

