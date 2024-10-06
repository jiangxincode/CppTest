#include "function.h"
#include "jiangxin.h"

using namespace std;

int main(int argc , char* argv[])
{
    string dirName;
    vector<string> strVec;
    long int sum,temp;

    jx_PrintAuthorInfo();
    char ch;

    do
    {
        sum = 0;
        if (argc == 1)
        {
            cout << "\nInput the directory:" << endl;
            cout << "\t \".\" stands \"current directory\"" << endl;
            cout << "\t \"..\" stands \"parent directory\"" << endl;
            cin >> dirName;
            strVec = ReadDir(dirName); // get all filename in the dirName
        }
        else if(argc == 2)
        {
            argc = 1; //After one loop, the branch is no longer needed.
            strVec = ReadDir(argv[1]);
        }
        cout << "the size of strVec is " << strVec.size() << endl;
        for(vector<string>::iterator pos = strVec.begin(); pos < strVec.end(); pos++)
        {
            if((temp = ProcessFile(*pos)) == -1)
            {
                continue;
            }
            sum = sum + temp;
        }
        cout << "Sum is: " << sum << endl;

        cout << "Continue/Exit(C/E): ";
		ch=jx_getchar((short)1);
    }while(ch != 'e');

    jx_PrintBye();
    return 0;
}
