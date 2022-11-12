
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

char jx_getchar(short option);
void jx_PrintBye(void);
void jx_PrintAuthorInfo(void);

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
