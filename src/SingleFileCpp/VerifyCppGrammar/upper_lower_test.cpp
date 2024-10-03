#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <locale>

int main()
{
    std::string src = "Hello World";
    std::string dst;

    std::ranges::transform(src.begin(), src.end(), back_inserter(dst), ::toupper);
    std::cout << dst << std::endl;

    std::ranges::transform(src.begin(), src.end(), dst.begin(), ::tolower);
    std::cout << dst << std::endl;

    //std::wcout.imbue(std::locale("chs"));  //即使设置，有中文的时候也无法使用wcout输出

    std::wstring wsrc = L"Hello World";
    std::wstring wdst;

    std::ranges::transform(wsrc.begin(), wsrc.end(), back_inserter(wdst), ::towupper);
    std::wcout << wdst << std::endl;

    std::ranges::transform(wsrc.begin(), wsrc.end(), wdst.begin(), ::towlower);
    std::wcout << wdst << std::endl;

    return 0;
}
