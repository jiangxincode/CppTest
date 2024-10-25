#include <signal.h>
#include <stdio.h>
void sigroutine(int dunno)
{
    switch (dunno)
    {
    case SIGINT:
        // ������ֹ(interrupt)�ź�, ���û�����INTR�ַ�(ͨ����Ctrl+C)ʱ����������֪ͨǰ̨��������ֹ���̡�
        perror("Get a signal -- SIGINT ");
        break;
    case SIGABRT:
        perror("Get a signal -- SIGABRT ");
        break;
    case SIGTERM:
        perror("Get a signal -- SIGTERM ");
        break;
    case SIGBREAK:
        // ���رպڿ򣬷���SIGBREAKʱ
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
