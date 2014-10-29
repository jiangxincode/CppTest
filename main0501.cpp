#include <iostream>
#include <cstdio>
using namespace std;

#define MAXINPUTLENGTH 256
//在一个字符串中找到所有只出现一次的字符,采用hash表，复杂的为O(n)
void FindOne(char *input)
{
    int HashTable[256] = {0};
    int length = 0;

    for(int i=0; input[i]!='\0'; i++)
    {
        HashTable[input[i]-'\0']++;
        length++;
        //cout << length << endl;
    }

    for(int i=0; i<256; i++)
    {
        if(HashTable[i] == 1)
        {
            printf("%c ",i);
            //cout << '\0' + input[i] << " ";
        }
    }
}
int main0501()
{
    char input[256];
    cout << "Inout a String:" << endl;
    cin >> input;
    FindOne(input);
    return 0;
}
