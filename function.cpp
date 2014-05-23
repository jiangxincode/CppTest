#include "function.h"

using namespace std;

void PrintVec(vector<string> vecStr)
{
    for(int i = 0; i < (int)vecStr.size(); i++)
        cout << vecStr[i] << endl;
}

#ifdef _LINUX
vector<string> ReadDir(string dirName)
{
    DIR *dp;
    struct dirent *ent;
    vector<string> ret;


    if((dp = opendir(dirName.c_str())) == NULL)
    {

        exit(1);
    }

    errno = 0;
    while((ent = readdir(dp)) != NULL)
    {
        //cout << setw(8)<< ent->d_ino <<"    "<< ent->d_name << endl;
        ret.push_back(ent->d_name);

    }

    if(errno != 0)
    {

        exit(1);
    }

    if(closedir(dp) != 0)
    {

        exit(1);

    }
    return ret;
}
#endif

//#ifdef _WIN32
vector<string> ReadDir(string dirName)
{
    char *fileName;
    char fullName[256];
    HANDLE fileHandle;
    WIN32_FIND_DATA findData;
    vector<string> ret;

    if( !GetFullPathName(dirName.c_str(), 256, fullName, &fileName ) ) //将相对目录转化为绝对目录
        return ret;

    cout << "\nDirectory - " << fullName << endl;
    int i;

    char suffix[MAXSUFFIXNUM][MAXSUFFIXLEN];

    int i_suffix_num = 0;
    char *p[i_suffix_num];
    cout << "How many types that you want to test?" << endl;
    cin >> i_suffix_num;
    cout << "Input the type of your source code(separate with space):" << endl;
    cout << "\n\t *.cpp *.h" << endl;

    for(i=0;i<i_suffix_num;i++)
    {
        cin >> suffix[i];
        //cout << suffix[i];
    }
    i=0;
    do
    {
        i++;
    }while(fullName[i]);
    fullName[i++] = '\\';
    for(int j=0;j<i_suffix_num;j++)
    {
        int temp = i;
        for(int k=0;suffix[j][k]!='\0';k++)
        {
            fullName[i++] = suffix[j][k];
            fullName[i+1] = '\0';
        }
        i = temp;
        cout << fullName << endl;
        p[j] = fullName;
        //cout << p[j] << endl;

    }
    for(i=0;i<i_suffix_num;i++)
{


    fileHandle = FindFirstFile(p[i], &findData );
    while ( fileHandle != INVALID_HANDLE_VALUE )
    {
        // If the name is a directory,
        // recursively walk it. Otherwise
        // print the file's data
        if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {
            //ListDirectoryContents( findData.cFileName,fileMask );
        }
        else
        {
            ret.push_back(findData.cFileName);
        }
        // loop thru remaining entries in the dir
        if (!FindNextFile( fileHandle, &findData ))
            break;
    }

    // clean up and restore directory
    FindClose( fileHandle );
}
    return ret;
}
//#endif

long int ProcessFile(string fileName)
{
    long int counter = 0;
    char c_temp;
    ifstream file(fileName.c_str(),ios::in);

    if (file.fail())
    {
        cerr << "Can't open input file \"" << fileName << "\"" << endl;
        return -1;
    }

    while (!file.eof())
    {
        file.get(c_temp);
        if(c_temp == '\n')
        {
            counter++;
        }
    }
    cout << fileName << "---->" << counter << endl;
    return counter;
}
