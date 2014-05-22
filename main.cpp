#include "function.h"

using namespace std;

int main(int argc , char* argv[])
{
    string dirName;
    vector<string> strVec;

    int sum =0;
    if (argc == 1)
    {
        //char filepath[100] = "";
        cout << "Input the directory:(\".\" stands \"current directory\") " << endl;
        cin >> dirName;
        cout << dirName;
        strVec = ReadDir(dirName);
    }
    else
    {
        strVec = ReadDir(argv[1]);
    }
    cout << "the size of strVec is " << strVec.size() << endl;
    for(vector<string>::iterator pos = strVec.begin(); pos < strVec.end(); pos++)
    {
        ProcessFile(*pos,sum);
    }

    cout << "Sum is: " << sum << endl;
    #ifdef _LINUX
        system("pasuse");
    #endif // _LINUX
    #ifdef _WIN32
        getch();
    #endif // _WIN32

    return 0;
}
