#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/**ͣ�������շ�ϵͳ*/

void system_start(); //ϵͳ��¼����
void car_gui(); //С������
void login(); //��¼����
void input(); //�������
void query(); //��ѯ������Ϣ��
void parking(int i); //ͣ����Ϣ����
void user_name_query(); //������������ѯ
void car_no_query(); //�����ƺ����ѯ
float reset(); //��������ͣ������
void quit();
void shanchu(int i);
void inputdiaoyong();
void parking_ability();
void parking_info();
void xingmingquery(int i,int a,int k);

#define N 2
#define MAX_CAR_NUM 10
#define MAX_HOUR 24
#define MAX_MINUT 60

/**������Ϣ*/
typedef struct CARINFO
{
    char carNo[10]; //���ƺ�
    char userName[10]; //�û���
    char color[10]; //��ɫ
    char type[10]; //�ͺ�
    int hour; //ʱ��(h)
    int minute; //ʱ��(m)
    int abbreviation; //���
} CarInfo;

static CarInfo *carInfo = NULL;

/**���Ƶ�ʱ���ӡ����*/
void time_print()
{
    time_t ltime;
    time(&ltime);
    printf("����ʱ��:%s",ctime(&ltime));
}

/**��������ͣ������*/
float reset()
{
    printf("\n\n\n\n\n\n\n");
    printf("\n\n\t\t---����ͣ������---");
    printf("\n\n\t\t�������µķ���:");
    float a;
    scanf("%f",&a);
    return a;
}

void parking(int i)
{
    float hour,minute;
    float n=0.5;
    printf("\n\n\n\n\n\n");
    printf("\t\t---ͣ����Ϣ��ѯ---");
    printf("\n\n\tĬ��ͣ������0.5Ԫ/Сʱ   �� 1 ������");

    if(getch()=='1')
    {
        system("CLS");
        n=reset();
    }

    system("CLS");
    printf("����ʱ��:");
    time_print();
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t---ͣ����Ϣ��ѯ---");
    printf("\n\n\t��ʼʱ��:%.0dʱ%.0d��",carInfo[i].hour,carInfo[i].minute);
n:
    printf("\n\n\t��������ʱ��:");
    scanf("%f,%f",&hour,&minute);

    if(hour<0.0||hour>24.0||minute<0.0||minute>60.0)
    {
        printf("�������!");
        goto n;
    }

    float shi,fen;

    if(hour-carInfo[i].hour<0)
    {
        if((minute-carInfo[i].minute)<0)
        {
            shi=hour-carInfo[i].hour-1+24;
            fen=60-(carInfo[i].minute-minute);
        }
        else
        {
            shi=hour-carInfo[i].hour+24;
            fen=minute-carInfo[i].minute;
        }
    }

    if(hour-carInfo[i].hour==0)
    {
        if((minute-carInfo[i].minute)<0)
        {
            shi=hour-carInfo[i].hour+23;
            fen=60-(carInfo[i].minute-minute);
        }
        else
        {
            shi=hour-carInfo[i].hour;
            fen=minute-carInfo[i].minute;
        }
    }

    if(hour-carInfo[i].hour>0)
    {
        if((minute-carInfo[i].minute)<0)
        {
            shi=hour-carInfo[i].hour-1;
            fen=60-(carInfo[i].minute-minute);
        }
        else
        {
            shi=hour-carInfo[i].hour;
            fen=minute-carInfo[i].minute;
        }
    }

    printf("\n\tͣ��ʱ��:%.0fʱ%.0f��",shi,fen);
    printf("\n\n\tͣ������:%.2fԪ",n*(shi+fen/60));
    printf("\n\n\t�Ƿ�ɾ���˳���Ϣ!");
    printf("\n\n\t1.��   2.��");
    int l;
    scanf("%d",&l);

    if(l==1)
    {
        system("CLS");
        shanchu(i);
    }

    system("CLS");
    login();
}

void shanchu(int i)
{
    strcpy(carInfo[i].carNo,"000000000");
    strcpy(carInfo[i].userName,"000000000");
    printf("\n\n\n\n\n\n\n\t\t\t�� �� �� ��");
    Sleep(500);
    system("CLS");
    printf("\n\n\n\n\n\n\n\t\t\t�� �� �� ����");
    Sleep(500);

    if(carInfo[i].carNo[0]=='0'&&carInfo[i].userName[0]=='0')
    {
        system("CLS");
        printf("\n\n\n\n\n\n\t\t\tɾ���ɹ�!");
        Sleep(1500);
    }
    else
    {
        system("CLS");
        printf("\n\n\n\n\n\n\t\t\tɾ��ʧ��!");
        Sleep(1500);
    }
}

void car_no_query()//���ƺŲ�ѯ
{
    char carNo[10];
    int a;
    int i = 0;
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t----���ѡ��----");
    printf("\n\n\t\t1.��  2.��  3.��  4.��  5.��  ");
    scanf("%d",&a);
m:
    system("CLS");
    printf("\n\n\n\t\t\t---�����복�ƺ���---\n\n");

    switch(a)
    {
    case 1:
        printf("\n\t���ƺ���:��");
        break;

    case 2:
        printf("\n\t���ƺ���:��");
        break;

    case 3:
        printf("\n\t���ƺ���:��");
        break;

    case 4:
        printf("\n\t���ƺ���:��");
        break;

    case 5:
        printf("\n\t���ƺ���:��");
        break;
    }

    scanf("%9s",carNo);

    if(carNo[0]<'A'||carNo[0]>'Z')
    {
        printf("\n\n\t�������!");
        Sleep(100);
        goto m;
    }

    for(i=0; i<N; i++)
    {
        if(strcmp(carInfo[i].carNo,carNo)==0)
        {
            break;
        }
    }

    if(strcmp(carInfo[i].carNo,carNo)==0)
    {
        switch(a)
        {
        case 1:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t��������:%s",carInfo[i].userName);
        printf("\n\n\t�����ͺ�:%s",carInfo[i].type);
        printf("\n\n\t������ɫ:%s",carInfo[i].color);
        printf("\n\n\t��ʼʱ��:%.0dʱ%.0d��",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n\n\t��1���鿴ͣ����Ϣ:");

        if(getch()=='1')
        {
            system("CLS");
            parking(i);
        }
        else
        {
            system("CLS");
            query();
        }
    }

    {
        printf("\n\n\tû������������Ϣ!");
        printf("\n\n\t�����������");
        getch();
        system("CLS");
        query();
    }
}

void user_name_query()//��������ѯ
{
    char chezhuming[10];
    printf("\n\n\n\n\n\n");
    printf("�����복������:");
    scanf("%9s",chezhuming);
    int i = 0;

    for(i=0; i<N; i++)
    {
        if((strcmp(carInfo[i].userName,chezhuming))==0)
        {
            break;
        }
    }

    if((strcmp(carInfo[i].userName,chezhuming))==0)
    {
        int	a=carInfo[i].abbreviation;//printf("�˴�����!%d",a);

        switch(a)
        {
        case 1:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t��������:%s",carInfo[i].userName);
        printf("\n\n\t�����ͺ�:%s",carInfo[i].type);
        printf("\n\n\t������ɫ:%s",carInfo[i].color);
        printf("\n\n\t��ʼʱ��:%.0dʱ%.0d��",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n\n\t��1���鿴ͣ����Ϣ:");
        int k=i;

        for(i=i+1; i<N; i++)
        {
            if((strcmp(carInfo[i].userName,chezhuming))==0)
            {
                xingmingquery(i,a,k);
            }
        }

        if(getch()=='1')
        {
            system("CLS");
            parking(k);
        }
        else
        {
            system("CLS");
            query();
        }
    }
    else
    {
        printf("\n\n\tû������������Ϣ!");
        printf("\n\n\t�����������");
        getch();
        system("CLS");
        query();
    }
}
void xingmingquery(int i,int a,int k)
{
    if(1)
    {
        switch(a)
        {
        case 1:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t��������:%s",carInfo[i].userName);
        printf("\n\n\t�����ͺ�:%s",carInfo[i].type);
        printf("\n\n\t������ɫ:%s",carInfo[i].color);
        printf("\n\n\t��ʼʱ��:%.0dʱ%.0d��",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n\n\t��2���鿴ͣ����Ϣ:");
    }

    int n;
    scanf("%d",&n);

    switch(n)
    {
    case 1:
        system("CLS");
        parking(k);
        break;

    case 2:
        system("CLS");
        parking(i);
        break;
    }
}

void query()
{
    printf("\n\n\n\n\n\n");
    printf("\n\t\t---������Ϣ��ѯ---");
    printf("\n\n\t\t1.�����ƺŲ�ѯ");
    printf("\n\n\t\t2.����������ѯ");
    printf("\n\n\t\t3.�˳�--");
    int i;
    scanf("%d",&i);

    switch(i)
    {
    case 1:
        system("CLS");
        car_no_query();

    case 2:
        system("CLS");
        user_name_query();

    case 3:
        system("CLS");
        login();
    }
}

void input()
{
    int i = 0 , j = 0;

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if((carInfo[j].carNo[0]==0) || (carInfo[j].carNo[0]=='0'))
            {
                break;
            }
        }

        if(j >= N)
        {
            system("CLS");
            perror("\n\n\n\n\n\n\n\t\t\tͣ��������!");
            Sleep(2000);
            login();
        }

        i=j;
        FILE *fp = fopen("data/che.txt","wb");

        if(fp == NULL)
        {
            perror("���ļ�ʧ��\n");
            exit(1);
        }

        fwrite(&carInfo[i],sizeof(CarInfo),1,fp);
        system("CLS");
        time_print();
        printf("\n\n\n\t��%d����λ",i+1);
        printf("\n\n\n\t\t\t---�����복����Ϣ---\n\n");
        printf("\n\t��1��ѡ����");
        printf("\n\n\t���ƺ���:��");
        int j = getch();

        if(j == '1')
        {
            system("CLS");
            printf("\n\n\n\t��%d����λ",i+1);
            printf("\n\n\n\n\n\n\n");
            printf("\n\n\t\t----���ѡ��----");
            printf("\n\n\t\t1.��  2.��  3.��  4.��  5.��  ");
            scanf("%d",&carInfo[i].abbreviation);
        }

ab:
        system("CLS");
        time_print();
        printf("\n\n\n\t��%d����λ",i+1);
        printf("\n\n\n\t\t\t---�����복����Ϣ---\n\n");

        if((carInfo[i].abbreviation > 0) && (carInfo[i].abbreviation < 10))
        {
            switch(carInfo[i].abbreviation)
            {
            case 1:
                printf("\n\t���ƺ���:��");
                break;

            case 2:
                printf("\n\t���ƺ���:��");
                break;

            case 3:
                printf("\n\t���ƺ���:��");
                break;

            case 4:
                printf("\n\t���ƺ���:��");
                break;

            case 5:
                printf("\n\t���ƺ���:��");
                break;

            default:
                printf("\n\t���ƺ���:��");
                break;
            }
        }

        scanf("%9s",carInfo[i].carNo);

        if((carInfo[i].carNo[0] < 'A') || (carInfo[i].carNo[0]>'Z'))
        {
            perror("\n\n\t�������!");
            Sleep(100);
            goto ab;
        }

        for(int j=0; j<MAX_CAR_NUM; j++)
        {
            if((i != j) && (strcmp(carInfo[j].carNo,carInfo[i].carNo)==0))
            {
                system("CLS");
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                printf("\n\t\t\t�� �� �� �� �� !");
                Sleep(1000);
                goto ab;
            }
        }

        printf("\n\t��������:");
        scanf("%9s",carInfo[i].userName);
        printf("\n\t�����ͺ�:");
        scanf("%9s",carInfo[i].type);
        printf("\n\t������ɫ:");
        scanf("%9s",carInfo[i].color);

        while((carInfo[i].hour >= MAX_HOUR) ||
                (carInfo[i].hour < 0) ||
                (carInfo[i].minute < 0) ||
                (carInfo[i].minute >= MAX_MINUT))
        {
            perror("�������!");
            printf("\n\t����ʱ��<ʱ,��>");
            scanf("%d,%d",&carInfo[i].hour,&carInfo[i].minute);
        }

        fclose(fp);
        printf("\n\n\t��1���˳�\n");

        if(getch() == '1')
        {
            system("CLS");
            login();
        }
    }

    system("CLS");
    perror("\n\n\n\n\n\n\n\t\t\tͣ��������!");
    Sleep(2000);
    login();
}

void login()
{
    system("CLS");
    printf("\n\n\n\n\n\n\n");
    printf("\n\t\t\t----��ӭʹ���������----");
    printf("\n\n\t1.���복����Ϣ");
    printf("\n\n\t2.��ѯ������Ϣ");
    printf("\n\n\t3.��ѯ��������");
    printf("\n\n\t4.�˳�ϵͳ");
    printf("\n\n\t\t��ѡ��:");
    int i;
    scanf("%d",&i);

    switch(i)
    {
    case 1:
        input();
        break;

    case 2:
        query();
        break;

    case 3:
        parking_ability();
        break;

    case 4:
        quit();
        break;

    default:
        login();
        break;
    }
}

void parking_ability()
{
    int M=0;

    for(int J=0; J<N; J++)
    {
        if(carInfo[J].carNo[0]==0||carInfo[J].carNo[0]=='0')
        {
            M++;
        }
    }

    if(N-(N-M))
    {
        if((N-N-(N-M))==0)
        {
            printf("\n\n\n\n\n");
            printf("\n\t\t�� �� �� �� !");
            Sleep(1000);
            system("CLS");
            login();
        }
        else
        {
            printf("\n\n\n\n\n");
            printf("\t\t����������%d����λ",N);
            printf("\n\n\n\t\t\t����%d����λ!",N-(N-M));
            Sleep(1000);
            printf("\n\n\t\t1.�鿴���г�����Ϣ\n\n\t\t2.����");
            printf("\n\n\t\t\t---");
            int a;
            scanf("%d",&a);

            if(a==1)
            {
                system("CLS");
                parking_info();
            }
            else
            {
                system("CLS");
                login();
            }
        }
    }
    else
    {
        printf("\n\n\n\n\n\n\t\tͣ��������!");
    }

    Sleep(1000);
    printf("\n\n\t\t1.�鿴���г�����Ϣ\n\n\t\t2.����");
    printf("\n\n\t\t\t---");
    int b;
    scanf("%d",&b);

    if(b==1)
    {
        system("CLS");
        parking_info();
    }

    system("CLS");
    login();
}

void parking_info()
{
    for(int i=0; i<N; i++)
    {
        if(carInfo[i].carNo[0]==0||carInfo[i].carNo[0]=='0')
        {
            continue;
        }

        int	a=carInfo[i].abbreviation;
        printf("%d�ų�λ",i+1);

        switch(a)
        {
        case 1:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t���ƺ���:��%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t��������:%s",carInfo[i].userName);
        printf("\n\n\t�����ͺ�:%s",carInfo[i].type);
        printf("\n\n\t������ɫ:%s",carInfo[i].color);
        printf("\n\n\t��ʼʱ��:%.0dʱ%.0d��",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n");
    }

    printf("\t\t��������˳�");
    getch();
    system("CLS");
    login();
}
void quit()
{
    int sleep;
    printf("\n");
    printf("\n\t\t\t     ����");
    printf("\n\t\t\t������������");

    for(sleep=1; sleep<1000000; sleep++) //ѭ������ֹͣ�ȴ�
    {}

    system("cls"); //����
    printf("\n\n\n");
    printf("\n\t\t\t      ����");
    printf("\n\t\t\t ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n");
    printf("\n\t\t\t       ����");
    printf("\n\t\t\t  ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t        ����");
    printf("\n\t\t\t   ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t         ����");
    printf("\n\t\t\t    ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t           ����");
    printf("\n\t\t\t      ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t            ����");
    printf("\n\t\t\t       ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t              ����");
    printf("\n\t\t\t         ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                ����");
    printf("\n\t\t\t           ������������");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                  ����");
    printf("\n\t\t\t             ������������");

    for(sleep=1; sleep<10000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                     ����");
    printf("\n\t\t\t                ������������");

    for(sleep=1; sleep<10000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                        ����");
    printf("\n\t\t\t                   ������������");

    for(sleep=1; sleep<20000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                          ����");
    printf("\n\t\t\t                     ������������");

    for(sleep=1; sleep<20000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                            ����");
    printf("\n\t\t\t                       ������������");

    for(sleep=1; sleep<30000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                              ����");
    printf("\n\t\t\t                         ������������");

    for(sleep=1; sleep<30000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                                ����");
    printf("\n\t\t\t                           ������������");

    for(sleep=1; sleep<50000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                                  ����");
    printf("\n\t\t\t                             ������������");

    for(sleep=1; sleep<80000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n\7\7");
    printf("\n\t\t\t                                    ����");
    printf("\n\t\t\t                               ������������  ��  ");

    for(sleep=1; sleep<100000000; sleep++)
    {}

    system("cls"); //����
    printf("\n\n\n\n\n\n\n\n\n\n\7\7\7");
    printf("\n\t\t\t                                       ����       ��");
    printf("\n\t\t\t                                  ������������  ��");
    printf("\n\t\t\t                                            ��    ��");
    Sleep(1000);
    system("CLS");
    system("color f1");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t �� !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\tʹ �� !");
    ;
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t л ʹ �� !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\tл л ʹ �� !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\tл л ʹ �� !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\tл л ʹ �� !\t\t");
    Sleep(500);
    exit(0);
}

void car_gui()
{
    int i,sleep;

    /**��ѭ������ʹ���������*/
    for(i=1; i<=1; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t     ����");
        printf("\n\t������������");

        for(sleep=1; sleep<10000000; sleep++) //ѭ������ֹͣ�ȴ�
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t       ����");
        printf("\n\t  ������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t     ����");
        printf("\n\t\t������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t     ����");
        printf("\n\t\t\t������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t       ����");
        printf("\n\t\t\t  ������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t     ����");
        printf("\n\t\t\t\t������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t       ����");
        printf("\n\t\t\t\t  ������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t\t     ����");
        printf("\n\t\t\t\t\t������������");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //����
    }

    printf("\n\n\n\n\n\n\n\n\n\n\7");
    printf("\n\t\t\t\t\t\t       ����        �� ");
    printf("\n\t\t\t\t\t\t  ������������");
    printf("\n\t\t\t\t\t\t                   ӭ ");
    Sleep(1000);
    system("CLS");
    printf("\n\n\n\n\n\n");
    printf("\t\t  ��---------------------------------- \n");
    printf("\t\t   ������������������������������������\n");
    printf("\t\t   ���������� ��ӭʹ�ñ������ ��  ����\n");
    printf("\t\t    ---------------------------------- \n");
    printf("\t\t   �������� ͣ�����շѹ���ϵͳ     ����\n");
    printf("\t\t   ����������          ����        ����\n");
    printf("\t\t   ����������     ѧ��: jiangxin      ����\n");
    printf("\t\t   ����                            ����\n");
    printf("\t\t   ������������������������������������\n");
    printf("\t\t    ---------------------------------- \n");

    for(int j=0; j<600000000; j++) //���ڿ���ͣ��ʱ��ĳ���
    {}

    system("cls");
}
void system_start()
{
    for(int i=1; i<=3; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t�� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�.");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t���\n ");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�.");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t���� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�..");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t    ��\n ");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�..");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t    ���\n ");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�...");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t    ���� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�...");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t        �� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�.....");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t        ��� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�....");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t        ���� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�.....");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t            ��\n ");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�.....");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t            ���\n ");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�......");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t            ����\n ");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�......");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t              ���\n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�.");
        Sleep(400);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       ����\n");
        printf("\t\t\t\t  ������������\n");
        printf("\t\t\t\t�ߣߣߣߣߣߣߣߣ�\n");
        printf("\t\t\t\t                �� \n");
        printf("\t\t\t\t������������������\n\n\n");
        printf("\t\t\t\t��������  ���Ժ�..");
        Sleep(500);
        system("CLS");
    }
}

int main0026()
{
    carInfo = (CarInfo*)malloc(sizeof(CarInfo)*MAX_CAR_NUM);
    memset(carInfo, 0, sizeof(CarInfo)*MAX_CAR_NUM);

    for(int i=0; i<MAX_CAR_NUM; i++)
    {
        carInfo[i].carNo[0] = '\0'; //δ��ʼ���ı�־
        carInfo[i].abbreviation = 1; //��ʼ�����еļ��Ϊ"��"
    }

    /**��ʼ��һ������ begin*/
    strncpy(carInfo[0].carNo, "B74110", sizeof(carInfo[0].carNo));
    strncpy(carInfo[0].userName, "jiangxin", sizeof(carInfo[0].userName));
    strncpy(carInfo[0].color, "black", sizeof(carInfo[0].color));
    carInfo[0].hour = 11;
    carInfo[0].minute = 20;
    /**��ʼ��һ������ end*/
    FILE *fp = fopen("data/che.txt","w");

    if(fp == NULL)
    {
        perror("���ļ�ʧ��\n");
        exit(1);
    }

    fwrite(carInfo, sizeof(CarInfo), 1, fp);
    rewind(fp);
    fclose(fp);
    //system_start();
    //car_gui();
    login();
    return 0;
}
