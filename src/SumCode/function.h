#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

char jx_getchar(short option);

#ifdef __linux__
#include <sys/types.h>
#include <dirent.h>
#endif

#ifdef __APPLE__
#include <sys/types.h>
#include <dirent.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

#define NDEBUG

#define MAXSUFFIXNUM 100
#define MAXSUFFIXLEN 10
#define BufferLength 256

using namespace std;

vector<string> ReadDir(string dirName);
void PrintVec(vector<string> vecStr);
long int ProcessFile(string fileName);
