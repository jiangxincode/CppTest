#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
/*for directroy function */
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

//#define _LINUX

#ifdef _LINUX
#include <sys/types.h>
#include <dirent.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace std;

vector<string> ReadDir(string dirName);
void PrintVec(vector<string> vecStr);
int ProcessFile(string fileName,int& sum);

int main(int argc , char* argv[])
{
    string dirName;
    vector<string> strVec;

    int sum =0;
    if (argc == 1)
    {
        //char filepath[100] = "";
        //cout << "Input the directory:(\".\" stands \"current directory\") " << endl;
        //cin >> filepath;
        strVec = ReadDir(".");
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

    cout << "Sum is£» " << sum << endl;
    #ifdef _LINUX
        system("pasuse");
    #endif // _LINUX
    #ifdef _WIN32
        getch();
    #endif // _WIN32

    return 0;
}
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

    // print out the current directory name
    if( !GetFullPathName("*.*", 256, fullName, &fileName ) )
        return ret;
    cout << endl << "Directory - " << fullName << endl;

    // Loop through all files in the directory
    fileHandle = FindFirstFile("*.*", &findData );
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
    return ret;
}
//#endif

int ProcessFile(string fileName,int& sum)
{
    // open input file
    int counter = 0;
    ifstream file (fileName.c_str());
    // file opened?
    if (! file)
    {
        // NO, abort program
        cerr << "can't open input file \"" << fileName << "\"" << endl;
        return (0);
    }

    char c;
    while (file.get(c))
    {
        if( c == '\n')
        {
            counter++;
        }
    }
    sum += counter;
    cout << fileName << "---->" << counter << endl;
    return counter;
}
