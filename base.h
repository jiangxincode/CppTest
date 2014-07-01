
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

#define NDEBUG

#define MAXSUFFIXNUM 100
#define MAXSUFFIXLEN 10
#define BufferLength 256
