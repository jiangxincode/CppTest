#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void sigroutine(int dunno)
{
	switch(dunno)
	{
	case SIGHUP:
	    // SIGHUP，hang up ，挂断。
		// 本信号在用户终端连接(正常或非正常)结束时发出, 通常是在终端的控制进程结束时, 通知同一session内的各个作业, 这时它们与控制终端不再关联。
        // 登录Linux时，系统会分配给登录用户一个终端(Session)。在这个终端运行的所有程序，包括前台进程组和 后台进程组，一般都属于这个 Session。
		// 当用户退出Linux登录时，前台进程组和后台有对终端输出的进程将会收到SIGHUP信号。
		// 这个信号的默认操作为终止进程，因此前台进 程组和后台有终端输出的进程就会中止。不过可以捕获这个信号，比如wget能捕获SIGHUP信号，并忽略它，这样就算退出了Linux登录，wget也 能继续下载。
        // 此外，对于与终端脱离关系的守护进程，这个信号用于通知它重新读取配置文件。
		// 要想模拟该信号，可以Ctrl-Z将进程置于后台，然后kill -HUP PID，向进程发送SIGHUP信号
		perror("Get a signal -- SIGHUP ");
		break;
	case SIGINT:
	    // 程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl+C)时发出，用于通知前台进程组终止进程。
		perror("Get a signal -- SIGINT ");
		break;
	case SIGQUIT:
	    // 和SIGINT类似, 但由QUIT字符(通常是Ctrl+\)来控制. 进程在因收到SIGQUIT退出时会产生core文件, 在这个意义上类似于一个程序错误信号。
		perror("Get a signal -- SIGQUIT ");
		break;
	}
	return;
}
int main()
{
	printf("process id is %d \n",getpid());
	signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法
	signal(SIGINT, sigroutine);
	signal(SIGQUIT, sigroutine);
	for(;;) ;
}
