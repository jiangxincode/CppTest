/*������ļ�*/
#pragma comment(lib,"wsock32.lib")
/*����ͷ�ļ�*/
#include <stdio.h>
#include <winsock2.h>

/*�Զ��庯��*/
int InitSockets(void);

void GetArgument(int argc, char **argv);
void ErrorPrint(x);
void userHelp();

/*����ȫ�ֱ���*/
unsigned short port;
char *hostName;

/*��ʼ��Winsock����*/
int InitSockets(void)
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
void GetArgments(int argc, char **argv)
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
void ErrorPrint(x)
{
	printf("Error %d: %s\n", WSAGetLastError(), x);
}

/*�û���������*/
void userHelp()
{
    printf("userHelp:  -h:str -p:int\n");
    printf("           -h:str  The host name \n");
    printf("           -p:int  The Port number to use\n");
    ExitProcess(-1);
}

/*������*/
int mainclcdc10client(int argc, char **argv)
{
    SOCKET clientfd;
    int err;
    struct sockaddr_in serverAddr;
    struct hostent *ptrHost;
    char response[4096];
    char *msg = "HELLO SERVER";
	GetArgments(argc, argv);
    if (argc != 3)
	{
      userHelp();
      return 1;
    }
	GetArgments(argc,argv);
    InitSockets();
	/*�����׽���*/
    clientfd = socket(PF_INET, SOCK_STREAM, 0);
	/*�������ʧ��*/
    if (clientfd == INVALID_SOCKET)
	{
        ErrorPrint("no more socket resources");
		return 1;
	}
	/*����IP��ַ����������*/
    if (atoi(hostName))
	{
        u_long ip_addr = inet_addr(hostName);
        ptrHost = gethostbyaddr((char *)&ip_addr,
            sizeof(u_long), AF_INET);
    }
	/*��������������IP��ַ*/
    else
        ptrHost = gethostbyname(hostName);

	/*�������ʧ��*/
    if (!ptrHost)
	{
        ErrorPrint("cannot resolve hostname");
		return 1;
	}

    /*���÷������˵�ַѡ��*/
	serverAddr.sin_family = PF_INET;
    memcpy((char *) &(serverAddr.sin_addr),
        ptrHost->h_addr,ptrHost->h_length);
    serverAddr.sin_port = htons(port);

	/*���ӷ�����*/
    err = connect(clientfd, (struct sockaddr *) &serverAddr,
        sizeof(serverAddr));
	/*����ʧ��*/
    if (err == INVALID_SOCKET)
	{
		ErrorPrint("cannot connect to server");
		return 1;
	}

	/*���ӳɹ��������Ϣ*/
    printf("You are connected to the server\n");
	/*������Ϣ����������*/
    send (clientfd, msg, strlen(msg)+1, 0);
    memset(response, 0, sizeof(response));
	/*�������Է������˵���Ϣ*/
    recv(clientfd, response, sizeof(response), 0);
    printf("server says %s\n", response);
	/*�ر��׽���*/
    closesocket(clientfd);
	/*�ͷ�Winscoket��ʼ��ʱռ�õ���Դ*/
    WSACleanup();
    return 0;
}


