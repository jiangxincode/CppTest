#include "pch.h"
#include "testdll.h"

int i = 0;
JNIEXPORT jint JNICALL Java_testdll_get (JNIEnv *, jclass)
{
	return i;
}
JNIEXPORT void JNICALL Java_testdll_set (JNIEnv *, jclass, jint j)
{
	i = j;
}