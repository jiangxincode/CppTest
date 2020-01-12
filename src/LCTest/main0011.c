/**
signal函数详细解释说明
位于 <signal.h> 中
void ( *signal( int sig, void (* handler)( int ))) ( int );
这个函数的声明很是吓人, 一看就难弄懂. 下面是解释用法.
一步一步解释:
int (*p)();
这是一个函数指针, p所指向的函数是一个不带任何参数, 并且返回值为int的一个函数.
int (*fun())();
这个式子与上面式子的区别在于用fun()代替了p,而fun()是一个函数,
所以说就可以看成是fun()这个函数执行之后,它的返回值是一个函数指针,
这个函数指针(其实就是上面的p)所指向的函数是一个不带任何参数,并且返回值为int的一个函数.
所以说对于void (*signal(int signo,void(*handler)(int)))(int);
就可以看成是signal()函数(它自己是带两个参数,一个为整型,一个为函数指针的函数),
而这个signal()函数的返回值也为一个函数指针,这个函数指针指向一个带一个整型参数,并且返回值为void的一个函数.
而你在写信号处理函数时对于信号处理的函数也是void sig_fun(int signo);这种类型,
恰好与上面signal()函数所返回的函数指针所指向的函数是一样的.
注意, void ( *signal() )( int );
signal是一个函数, 它返回一个函数指针,后者所指向的函数接受一个整型参数 且没有返回值,
仔细看, 是不是siganal( int signo, void(*handler)(int) )的第2个参数了,
对了, 其实他所返回的就是 signal的第2个信号处理函数,
指向信号处理函数,就可以执行函数了
( signal内部时, signal把信号做为参数传递给handler信号处理函数, 接着 signal函数返回指针,
并且又指向信号处理函数, 就开始执行它)
*/
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void sigroutine(int dunno)
{
	switch(dunno)
	{
	case SIGHUP:
		perror("Get a signal -- SIGHUP ");
		break;
	case SIGINT:
		perror("Get a signal -- SIGINT ");
		break;
	case SIGQUIT:
		perror("Get a signal -- SIGQUIT ");
		break;
	}
	return;
}
int main0011()
{
	printf("process id is %d \n",getpid());
	signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法
	signal(SIGINT, sigroutine);
	signal(SIGQUIT, sigroutine);
	for(;;) ;
}
/**
其中信号SIGINT由按下Ctrl-C发出，信号SIGQUIT由按下Ctrl-/发出。该程序执行的结果如下：
localhost:~$ ./sig_test
process id is 463
Get a signal -SIGINT //按下Ctrl-C得到的结果
Get a signal -SIGQUIT //按下Ctrl-/得到的结果
//按下Ctrl-z将进程置于后台
[1]+ Stopped ./sig_test
localhost:~$ bg
[1]+ ./sig_test &
localhost:~$ kill -HUP 463 //向进程发送SIGHUP信号
localhost:~$ Get a signal – SIGHUP
kill -9 463 //向进程发送SIGKILL信号，终止进程
localhost:~$
*/
