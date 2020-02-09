#include <cstdio>
#include <cstdlib>
#include "Python.h"

using namespace std;

//#include "C:\\Program Files\\Python27\\include\\Python.h"
//#pragma comment(lib, "C:\\Program Files\\Python27\\libs\\python27.lib")

int main(int argc, char** argv)
{
    //初始化Python在使用Python系统前，必须使用Py_Initialize对其进行初始化。
    //它会载入Python的内建模块并添加系统路
    //径到模块搜索路径中。这个函数没有返回值，检查系统
    //是否初始化成功需要使用Py_IsInitialized。
    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pRetVal;
    Py_Initialize();
    // 检查初始化是否成功
    if ( !Py_IsInitialized() )
    {
        return -1;
    }
    // 载入名为pytest的脚本(注意：不是pytest.py)
    pName = PyString_FromString("pytest");
    pModule = PyImport_Import(pName);
    if ( !pModule )
    {
        printf("can't find pytest.py");
        getchar();
        return -1;
    }
    pDict = PyModule_GetDict(pModule);
    if ( !pDict )
    {
        return -1;
    }
    // 找出函数名为add的函数
    pFunc = PyDict_GetItemString(pDict, "add");
    if ( !pFunc || !PyCallable_Check(pFunc) )
    {
        printf("can't find function [add]");
        getchar();
        return -1;
    }
    // 参数进栈
    pArgs = PyTuple_New(2);
    // PyObject* Py_BuildValue(char *format, ...)
    // 把C++的变量转换成一个Python对象。当需要从
    // C++传递变量到Python时，就会使用这个函数。此函数
    // 有点类似C的printf，但格式不同。常用的格式有
    // s 表示字符串，
    // i 表示整型变量，
    // f 表示浮点数，
    // O 表示一个Python对象。
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("l",3));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("l",4));
    // 调用Python函数
    pRetVal = PyObject_CallObject(pFunc, pArgs);
    printf("function return value : %ld\r\n", PyInt_AsLong(pRetVal));
    Py_DECREF(pName);
    Py_DECREF(pArgs);
    Py_DECREF(pModule);
    Py_DECREF(pRetVal);
    // 关闭Python
    Py_Finalize();
    return 0;
}



