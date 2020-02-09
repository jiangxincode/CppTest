#include <python3.7/Python.h>
int main()
{
    Py_Initialize();
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    pModule = PyImport_ImportModule("test");
    pFunc = PyObject_GetAttrString(pModule,"Hello");
    PyEval_CallObject(pFunc,NULL);
    Py_Finalize();
    return 0;
}