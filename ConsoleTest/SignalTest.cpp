#include <signal.h>
#include <stdio.h>
void sigroutine(int dunno)
{
    switch (dunno)
    {
    case SIGINT:
        // 程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl+C)时发出，用于通知前台进程组终止进程。
        perror("Get a signal -- SIGINT ");
        break;
    case SIGABRT:
        perror("Get a signal -- SIGABRT ");
        break;
    case SIGTERM:
        perror("Get a signal -- SIGTERM ");
        break;
    case SIGBREAK:
        // 当关闭黑框，返回SIGBREAK时
        perror("Get a signal -- SIGBREAK ");
        break;
    }
    return;
}

int main()
{
    signal(SIGINT, sigroutine);
    signal(SIGABRT, sigroutine);
    signal(SIGTERM, sigroutine);
    signal(SIGBREAK, sigroutine);
    for (;;);
}
