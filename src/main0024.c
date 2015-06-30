#include <glib.h>

int main0024(int argc, char* argv[])
{
    g_print("hello world!");
#ifdef G_OS_WIN32
    g_print("windows");
#endif // G_OS_WIN32
    return 0;
}
