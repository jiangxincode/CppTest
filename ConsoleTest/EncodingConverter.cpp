// 字符集相关知识的简单总结: https://www.cnblogs.com/dejavu/archive/2012/09/15/2686618.html
// 控制台程序的中文输出乱码问题: https://www.cnblogs.com/dejavu/archive/2012/09/16/2687586.html
// VC++的Unicode编程: https://blog.csdn.net/u014015972/article/details/47382665
// Using Unicode in C++ source code: https://stackoverflow.com/questions/331690/using-unicode-in-c-source-code
// std::wstring_convert: http://www.cplusplus.com/reference/locale/wstring_convert/
// Dword、LPSTR、LPWSTR、LPCSTR、LPCWSTR、LPTSTR、LPCTSTR: https://www.cnblogs.com/goed/archive/2011/11/11/2245702.html
// Windows Via C／C++ Fifth Edition: Chapter 2: Working with Characters and Strings

#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <locale.h>

#include <string>
#include <iostream>

#define CP_GB2312 936

/**
 * GB2312到UTF-8的转换
 */
static int GB2312ToUtf8(const char* gb2312, char* utf8)
{
    int len = MultiByteToWideChar(CP_GB2312, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_GB2312, 0, gb2312, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return len;
}

/**
 * UTF-8到GB2312的转换
 */
static int Utf8ToGB2312(const char* utf8, char* gb2312)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_GB2312, 0, wstr, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_GB2312, 0, wstr, -1, gb2312, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return len;
}

/**
 * GB2312到Unicode的转换
 */
static int GB2312ToUnicodeA(const char* gb2312, char* unicode)
{
    int len = MultiByteToWideChar(CP_GB2312, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_GB2312, 0, gb2312, -1, wstr, len);
    len = len * sizeof(wchar_t);
    memcpy(unicode, wstr, len);
    if (wstr) delete[] wstr;
    return len;
}

static int GB2312ToUnicodeW(const char* gb2312, wchar_t* unicode)
{
    int len = MultiByteToWideChar(CP_GB2312, 0, gb2312, -1, NULL, 0);
    return MultiByteToWideChar(CP_GB2312, 0, gb2312, -1, unicode, len);
}

/**
 * Unicode到GB2312的转换
 */
static int UnicodeToGB2312A(const char* unicode, int size, char* gb2312)
{
    wchar_t* wstr = new wchar_t[size / 2 + 1];
    memcpy(wstr, unicode, size);
    int len = WideCharToMultiByte(CP_GB2312, 0, wstr, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_GB2312, 0, wstr, -1, gb2312, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return len;
}

static int UnicodeToGB2312W(const wchar_t* unicode, char* gb2312)
{
    int len = WideCharToMultiByte(CP_GB2312, 0, unicode, -1, NULL, 0, NULL, NULL);
    return WideCharToMultiByte(CP_GB2312, 0, unicode, -1, gb2312, len, NULL, NULL);
}

/**
 * UTF-8到Unicode的转换
 */
static int Utf8ToUnicodeA(const char* utf8, char* unicode)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    memcpy(unicode, wstr, len);
    if (wstr) delete[] wstr;
    return len;
}

static int Utf8ToUnicodeW(const char* utf8, wchar_t* unicode)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    return MultiByteToWideChar(CP_UTF8, 0, utf8, -1, unicode, len);
}

/**
 * Unicode到UTF-8的转换
 */
static int UnicodeToUtf8A(const char* unicode, int size, char* utf8)
{
    wchar_t* wstr = new wchar_t[size / 2 + 1];
    memcpy(wstr, unicode, size);
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return len;
}

static int UnicodeToUtf8W(const wchar_t* unicode, char* utf8)
{
    int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    return WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, len, NULL, NULL);
}

int test_encoding_convert() {
    // chcp查看或者设置当前控制台的CodePage
    // 936:GBK 65001:UTF8
    const char* tmp = "你好世界";
    char gbkStr[32]; // 仅能在GBK的CodePage中展示
    char utf8Str[32]; // 仅能在UTF8的CodePage中展示
    char unicodeStr[32]; // 能在GBK/UTF8的CodePage中展示
    wchar_t wunicodeStr[32]; // 能在GBK/UTF8的CodePage中展示
    memset(gbkStr, 0, sizeof(gbkStr));
    memset(utf8Str, 0, sizeof(utf8Str));
    memset(unicodeStr, 0, sizeof(unicodeStr));
    memset(wunicodeStr, 0, sizeof(wunicodeStr));

    memcpy(gbkStr, tmp, strlen(tmp));
    printf("gbkStr: %s\n", gbkStr);

    GB2312ToUtf8(gbkStr, utf8Str);
    printf("utf8Str: %s\n", utf8Str);

    Utf8ToGB2312(utf8Str, gbkStr);
    printf("gbkStr: %s\n", gbkStr);

    char* p = setlocale(LC_ALL, NULL);
    printf("locale %s\n", p);
    p = setlocale(LC_ALL, "");
    printf("locale %s\n", p);
    p = setlocale(LC_ALL, "C");
    printf("locale %s\n", p);

    setlocale(LC_ALL, "");
    GB2312ToUnicodeA(gbkStr, unicodeStr);
    GB2312ToUnicodeW(gbkStr, wunicodeStr);

    //printf("unicodeStr1: %s\n", unicodeStr); // 打印不正确
    //printf("unicodeStr2: %ls\n", unicodeStr); // 有告警
    //printf("unicodeStr3: %s\n", wunicodeStr); // 有告警
    printf("unicodeStr4: %ls\n", wunicodeStr);
    //wprintf(L"unicodeStr5: %s\n", unicodeStr); // 有告警
    //wprintf(L"unicodeStr6: %ls\n", unicodeStr); // 有告警
    //wprintf(L"unicodeStr7: %s\n", wunicodeStr); // 无法兼容Linux
    wprintf(L"unicodeStr8: %ls\n", wunicodeStr);

    setlocale(LC_ALL, "C");
    UnicodeToGB2312W(wunicodeStr, gbkStr);
    printf("gbkStr: %s\n", gbkStr);

    setlocale(LC_ALL, "");
    Utf8ToUnicodeW(utf8Str, wunicodeStr);
    wprintf(L"unicodeStr: %s\n", wunicodeStr);

    setlocale(LC_ALL, "C");
    UnicodeToUtf8W(wunicodeStr, utf8Str);
    printf("utf8Str: %s\n", utf8Str);

    setlocale(LC_ALL, "");
    std::wstring wStr = L"你好世界";
    std::wcout << L"wStr: " << wStr << std::endl;
    wprintf(L"wStr: %ls\n", wStr.c_str());
    std::wstring wStrCopy(wStr.c_str());
    std::wcout << L"wStrCopy: " << wStrCopy << std::endl;


    std::string str = "你好世界";
    std::cout << "str: " << str << std::endl;
    printf("str: %s\n", str.c_str());
    std::string strCopy(str.c_str());
    std::cout << "strCopy: " << strCopy << std::endl;

    return 0;
}