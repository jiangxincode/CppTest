/*������ļ�*/
#pragma comment(lib,"wsock32.lib")
/*����ͷ�ļ�*/
#include <stdio.h>
#include <winsock2.h>
/*�Զ��庯��ԭ��*/
void initial();
static int InitSockets(void);

static void GetArgments(int argc, char **argv);
static void ErrorPrint(x);
static void userHelp();

int LoopControl(SOCKET listenfd, int isMultiTasking);

void Service(LPVOID lpv);

/*���峣��*/
#define MAX_SER 10
/*����ȫ�ֱ���*/
char *hostName;
unsigned short maxService;
unsigned short  port;

/*��ʼ��ȫ�ֱ�������*/
void initial()
{
    hostName = "127.0.0.1";
    maxService = 3;
    port = 9999;
}

/*��ʼ��Winsocket����*/
static int InitSockets(void)
{
    WSADATA wsaData;
    WORD sockVersion;
    int err;

    /*����Winsock�汾��*/
    sockVersion = MAKEWORD( 2, 2 );
    /*��ʼ��Winsock*/
    err = WSAStartup( sockVersion, &wsaData );
    /*�����ʼ��ʧ��*/
    if ( err != 0 )
    {
      printf("Error %d: Winsock not available\n", err);
      return 1;
    }
    return 0;
}


/*��ȡѡ���*/
static void GetArgments(int argc, char **argv)
{
    int i;
    for(i=1; i < argc ;i++)
    {
        /*�����ĵ�һ���ַ����ǡ�-��*/
        if (argv[i][0] == '-')
        {
            /*ת����Сд*/
            switch (tolower(argv[i][1]))
            {
                /*���Ƕ˿ں�*/
                case 'p':
                    if (strlen(argv[i]) > 3)
                        port = atoi(&argv[i][3]);
                    break;
               /*����������*/
               case 'h':
                    hostName = &argv[i][3];
                    break;
                /*���������*/
                case 'n':
                    maxService = atoi(&argv[i][3]);
                    break;
                /*�������*/
                default:
                    userHelp();
                    break;
            }
        }
    }
    return;
}

/*�����������*/
static void ErrorPrint(x)
{
    printf("Error %d: %s\n", WSAGetLastError(), x);
}

/*�û���������*/
static void userHelp()
{
    printf("userHelp:  -h:str -p:int -n:int\n");
    printf("           -h:str  The host name \n");
    printf("                   The default host is 127.0.0.1\n");
    printf("           -p:int  The Port number to use\n");
    printf("                   The default port is 9999\n");
    printf("           -n:int  The number of service,below MAX_SER \n");
    printf("                   The default number is 3\n");
    ExitProcess(-1);
}

/*ѭ�����ƺ���*/
int LoopControl(SOCKET listenfd, int isMultiTasking)
{
    SOCKET acceptfd;
    struct sockaddr_in clientAddr;
    int err;
    int nSize;
    int serverNum = 0;
    HANDLE handles[MAX_SER];
    int myID;

    /*�������С�����������*/
    while (serverNum < maxService)
    {
      nSize = sizeof(clientAddr);
      /*���տͻ�������*/
      acceptfd = accept(listenfd, (struct sockaddr *)
                         &clientAddr, &nSize);
      /*�������ʧ��*/
      if (acceptfd == INVALID_SOCKET)
      {
          ErrorPrint("Error: accept failed\n");
          return 1;
      }
      /*���ճɹ�*/
      printf("Accepted connection from client at %s\n",
             inet_ntoa(clientAddr.sin_addr));
      /*������������ִ��*/
      if (isMultiTasking)
      {
          /*����һ�����߳���ִ���������̵߳ĳ�ʼ��ջ��СΪ1000���߳�ִ�к���
          ��Service()�����ݸ�Service()�Ĳ���Ϊacceptfd*/
          handles[serverNum] = CreateThread(NULL, 1000,
                      (LPTHREAD_START_ROUTINE)Service,
                      (LPVOID) acceptfd, 0, &myID);

       }
      else
          /*ֱ�ӵ��÷���ͻ��˵ĺ���*/
          Service((LPVOID) acceptfd);
      serverNum++;
    }

    if (isMultiTasking)
    {
        /*��һ���߳��еȴ�����¼��������ж��󶼱�֪ͨʱ�����Ż᷵�أ����ҵȴ�û��ʱ������*/
        err = WaitForMultipleObjects(maxService, handles, TRUE, INFINITE);
        printf("Last thread to finish was thread #%d\n", err);

     }
    return 0;
}

/*������*/
void Service(LPVOID lpv)
{
    SOCKET acceptfd = (SOCKET) lpv;
    const char *msg = "HELLO CLIENT";
    char response[4096];

    /*��0��ʼ��response[4096]����*/
    memset(response, 0, sizeof(response));
    /*�������ݣ�����response��*/
    recv(acceptfd, response, sizeof(response), 0);

    /*������յ������ݺ�Ԥ��������ݲ�ͬ*/
    if (strcmp(response, "HELLO SERVER"))
    {
        printf("Application:  client not using expected "
            "protocol %s\n", response);
    }
    else
        /*���ͷ���������Ϣ���ͻ���*/
        send (acceptfd, msg, strlen(msg)+1, 0);
    /*�ر��׽���*/
    closesocket(acceptfd);
}


/*������*/
int mainclcdc10service(int argc, char **argv)
{
    SOCKET listenfd;
    int err;
    struct sockaddr_in serverAddr;
    struct hostent *ptrHost;
    initial();
    GetArgments(argc,argv);
    InitSockets();
    /*����TCP���׽��֣���domain����ΪPF_INET��SOCK_STREAM�׽ӿ��У�protocol����Ϊ0��ζ
    �Ÿ����ں�ѡ�� IPPRPTP_TCP����Ҳ��ζ���׽ӿڽ�ʹ��TCP/IPЭ��*/
    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    /*��������׽���ʧ��*/
    if (listenfd == INVALID_SOCKET)
    {
        printf("Error: out of socket resources\n");
        return 1;
    }

    /*�����IP��ַ*/
    if (atoi(hostName))
    {
        /*��IP��ַת����32�����Ʊ�ʾ��������32λ�����Ƶ������ֽ���*/
        u_long ip_addr = inet_addr(hostName);
        /*����IP��ַ�ҵ���֮ƥ���������*/
        ptrHost = gethostbyaddr((char *)&ip_addr,
                     sizeof(u_long), AF_INET);
     }
    /*�����������*/
    else
        /*������������ȡһ��ָ��hosten��ָ�룬�ýṹ�а����˸��������е�IP��ַ*/
        ptrHost = gethostbyname(hostName);

    /*�������ʧ��*/
    if (!ptrHost)
    {
        ErrorPrint("cannot resolve hostname");
        return 1;
    }

    /*���÷�������ַ*/
    /*���õ�ַ��ΪPF_INET*/
    serverAddr.sin_family = PF_INET;
    /*��һ��ͨ���Internet��ַת�����޷��ų����͵������ֽ�����*/
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*���˿ں�ת�����޷��Ŷ����͵������ֽ�����*/
    serverAddr.sin_port = htons(port);

    /*���׽������������ַ��*/
    err = bind(listenfd, (const struct sockaddr *) &serverAddr,
               sizeof(serverAddr));
    /*�����ʧ��*/
    if (err == INVALID_SOCKET)
    {
        ErrorPrint("Error: unable to bind socket\n");
        return 1;
    }

    /*��ʼ����,���õȴ����ӵ������г���ΪSOMAXCONN��Ĭ��ֵΪ5��*/
    err = listen(listenfd, SOMAXCONN);
    /*�������ʧ��*/
    if (err == INVALID_SOCKET)
    {
        ErrorPrint("Error: listen failed\n");
        return 1;
    }

    LoopControl(listenfd, 1);
    printf("Server is down\n");
    /*�ͷ�Winscoket��ʼ��ʱռ�õ���Դ*/
    WSACleanup();
    return 0;
}




