// SumCode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "function.h"
#include "jiangxin.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
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
            argc = 1; //��ѭ��һ��֮�󣬲�����Ҫ�÷�֧
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
    }while((ch=jx_getchar((short)1))!='e');

    jx_PrintBye();
    return 0;
}
