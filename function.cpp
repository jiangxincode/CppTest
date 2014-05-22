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

    // print out the current directory name
    //if( !GetFullPathName("*.*", 256, fullName, &fileName ) )
    if( !GetFullPathName(dirName.c_str(), 256, fullName, &fileName ) )
        return ret;
    cout << endl;
    cout << "Directory - " << fullName << endl;
    unsigned int i;
    for(i=0;fullName[i]!='\0';i++)
    {
        cout << fullName[i];
    }
    cout << i;
    fullName[i] = '\\';
    fullName[i+1] = '*';
    fullName[i+2] = '.';
    fullName[i+3] = '*';
    fullName[i+4] = '\0';
    // Loop through all files in the directory
    //fileHandle = FindFirstFile("*.*", &findData );
    fileHandle = FindFirstFile(fullName, &findData );
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
