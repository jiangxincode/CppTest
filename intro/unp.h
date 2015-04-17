/* Our own header, Tabs are set for 4 spaces, not 8 */

#ifndef __unp_h
#define __unp_h

#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket definition */
#include <sys/time.h> /* timeval() for select() */
#include <time.h> /*timespec() for pselect() */
#include <netinet/in.h> /*sockaddr_in() and other Internet defns */
#include <arpa/inet.h> /* inet(3) functions */
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> /* for S_xxx file mode constants */
#include <sys/uio.h> /* for iovec() and readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h> /* for Unix domain sockets */

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h> /* for convenience */
#endif // HAVE_SYS_SELECT_H

#ifdef HAVE_SYS_SYSCTL_H
#include <sys/sysctl.h>
#endif // HAVE_SYS_SYSCTL_H

#ifdef HAVE_POLL_H
#include <poll.h> /* for convenience */
#endif // HAVE_POLL_H

#ifdef HAVE_SYS_EVENT_H
#include <sys/event.h> /* for kqueue */
#endif // HAVE_SYS_EVENT_H

#ifdef HAVE_STRING_H
#include <strings.h> /* for convenience */
#endif // HAVE_STRING_H

/* Three headers are normally needed for socket/file ioctl's:
 * <sys/ioctl.h>, <sys/filio.h>, and <sys/sockio.h>.
 */
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif // HAVE_SYS_IOCTL_H

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif // HAVE_SYS_FILIO_H

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif // HAVE_SYS_SOCKIO_H

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif // HAVE_PTHREAD

#ifdef HAVE_NET_IF_DL_H
#include <net/if_dl.h>
#endif // HAVE_NET_IF_DL_H

#ifdef HAVE_NETINET_SCTP_H
#include <netinet/sctp.h>
#endif // HAVE_NETINET_SCTP_H

/* OSF/1 actually disables recv() and send() in <sys/socket.h> */
#ifdef __osf__
#undef recv
#undef send

#define recv(a,b,c,d) recvfrom(a,b,c,d,0,0)
#define send(a,b,c,d) sendto(a,b,c,d,0,0)
#endif // __osf__

#ifndef INADDR_NONE
#define INADDR_NONE 0xfffffff /* should have been in <netinet/in.h> */
#endif // INADDR_NONE

#ifndef SHUT_RD /* these three POSIX names are new */
#define SHUT_RD 0 /* shutdown for reading */
#define SHUT_WR 1 /* shutdown for writing */
#define SHUT_RDWR 2 /*shutdown for reading and writing */
#endif // SHUT_RD

/* Miscellaneous constants */
#define MAXLINE 4096 /*max text line length */
#define BUFFSIZE 8192 /* buffer size for reads and writes */

/* Following shortens all the typecasts of pointer arguments: */
#define SA struct sockaddr




void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);

#endif // __unp_h
