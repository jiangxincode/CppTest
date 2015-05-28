#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/**停车管理收费系统*/

void system_start(); //系统登录界面
void car_gui(); //小车界面
void login(); //登录界面
void input(); //输入界面
void query(); //查询车辆信息界
void parking(int i); //停车信息界面
void user_name_query(); //按车主姓名查询
void car_no_query(); //按车牌号码查询
float reset(); //重新设置停车费率
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

/**车辆信息*/
typedef struct CARINFO
{
    char carNo[10]; //车牌号
    char userName[10]; //用户名
    char color[10]; //颜色
    char type[10]; //型号
    int hour; //时间(h)
    int minute; //时间(m)
    int abbreviation; //简称
} CarInfo;

static CarInfo *carInfo = NULL;

/**定制的时间打印函数*/
void time_print()
{
    time_t ltime;
    time(&ltime);
    printf("现在时间:%s",ctime(&ltime));
}

/**重新设置停车费率*/
float reset()
{
    printf("\n\n\n\n\n\n\n");
    printf("\n\n\t\t---设置停车费率---");
    printf("\n\n\t\t请输入新的费率:");
    float a;
    scanf("%f",&a);
    return a;
}

void parking(int i)
{
    float hour,minute;
    float n=0.5;
    printf("\n\n\n\n\n\n");
    printf("\t\t---停车信息查询---");
    printf("\n\n\t默认停车费用0.5元/小时   按 1 键重设");

    if(getch()=='1')
    {
        system("CLS");
        n=reset();
    }

    system("CLS");
    printf("现在时间:");
    time_print();
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t---停车信息查询---");
    printf("\n\n\t起始时间:%.0d时%.0d分",carInfo[i].hour,carInfo[i].minute);
n:
    printf("\n\n\t输入现在时间:");
    scanf("%f,%f",&hour,&minute);

    if(hour<0.0||hour>24.0||minute<0.0||minute>60.0)
    {
        printf("输入错误!");
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

    printf("\n\t停车时间:%.0f时%.0f分",shi,fen);
    printf("\n\n\t停车费用:%.2f元",n*(shi+fen/60));
    printf("\n\n\t是否删除此车信息!");
    printf("\n\n\t1.是   2.否");
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
    printf("\n\n\n\n\n\n\n\t\t\t请 稍 候 …");
    Sleep(500);
    system("CLS");
    printf("\n\n\n\n\n\n\n\t\t\t请 稍 候 ……");
    Sleep(500);

    if(carInfo[i].carNo[0]=='0'&&carInfo[i].userName[0]=='0')
    {
        system("CLS");
        printf("\n\n\n\n\n\n\t\t\t删除成功!");
        Sleep(1500);
    }
    else
    {
        system("CLS");
        printf("\n\n\n\n\n\n\t\t\t删除失败!");
        Sleep(1500);
    }
}

void car_no_query()//车牌号查询
{
    char carNo[10];
    int a;
    int i = 0;
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t----简称选择----");
    printf("\n\n\t\t1.湘  2.鄂  3.赣  4.粤  5.京  ");
    scanf("%d",&a);
m:
    system("CLS");
    printf("\n\n\n\t\t\t---请输入车牌号码---\n\n");

    switch(a)
    {
    case 1:
        printf("\n\t车牌号码:湘");
        break;

    case 2:
        printf("\n\t车牌号码:鄂");
        break;

    case 3:
        printf("\n\t车牌号码:赣");
        break;

    case 4:
        printf("\n\t车牌号码:粤");
        break;

    case 5:
        printf("\n\t车牌号码:京");
        break;
    }

    scanf("%9s",carNo);

    if(carNo[0]<'A'||carNo[0]>'Z')
    {
        printf("\n\n\t输入错误!");
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
            printf("\n\n\t车牌号码:湘%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t车主姓名:%s",carInfo[i].userName);
        printf("\n\n\t汽车型号:%s",carInfo[i].type);
        printf("\n\n\t汽车颜色:%s",carInfo[i].color);
        printf("\n\n\t起始时间:%.0d时%.0d分",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n\n\t按1键查看停车信息:");

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
        printf("\n\n\t没有这辆车的信息!");
        printf("\n\n\t按任意键返回");
        getch();
        system("CLS");
        query();
    }
}

void user_name_query()//车主名查询
{
    char chezhuming[10];
    printf("\n\n\n\n\n\n");
    printf("请输入车主姓名:");
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
        int	a=carInfo[i].abbreviation;//printf("此处正常!%d",a);

        switch(a)
        {
        case 1:
        {
            printf("\n\n\t车牌号码:湘%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t车主姓名:%s",carInfo[i].userName);
        printf("\n\n\t汽车型号:%s",carInfo[i].type);
        printf("\n\n\t汽车颜色:%s",carInfo[i].color);
        printf("\n\n\t起始时间:%.0d时%.0d分",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n\n\t按1键查看停车信息:");
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
        printf("\n\n\t没有这辆车的信息!");
        printf("\n\n\t按任意键返回");
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
            printf("\n\n\t车牌号码:湘%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t车主姓名:%s",carInfo[i].userName);
        printf("\n\n\t汽车型号:%s",carInfo[i].type);
        printf("\n\n\t汽车颜色:%s",carInfo[i].color);
        printf("\n\n\t起始时间:%.0d时%.0d分",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n\n\t按2键查看停车信息:");
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
    printf("\n\t\t---车辆信息查询---");
    printf("\n\n\t\t1.按车牌号查询");
    printf("\n\n\t\t2.按车主名查询");
    printf("\n\n\t\t3.退出--");
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
            perror("\n\n\n\n\n\n\n\t\t\t停车场已满!");
            Sleep(2000);
            login();
        }

        i=j;
        FILE *fp = fopen("data/che.txt","wb");

        if(fp == NULL)
        {
            perror("打开文件失败\n");
            exit(1);
        }

        fwrite(&carInfo[i],sizeof(CarInfo),1,fp);
        system("CLS");
        time_print();
        printf("\n\n\n\t第%d个车位",i+1);
        printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
        printf("\n\t按1键选择简称");
        printf("\n\n\t车牌号码:湘");
        int j = getch();

        if(j == '1')
        {
            system("CLS");
            printf("\n\n\n\t第%d个车位",i+1);
            printf("\n\n\n\n\n\n\n");
            printf("\n\n\t\t----简称选择----");
            printf("\n\n\t\t1.湘  2.鄂  3.赣  4.粤  5.京  ");
            scanf("%d",&carInfo[i].abbreviation);
        }

ab:
        system("CLS");
        time_print();
        printf("\n\n\n\t第%d个车位",i+1);
        printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");

        if((carInfo[i].abbreviation > 0) && (carInfo[i].abbreviation < 10))
        {
            switch(carInfo[i].abbreviation)
            {
            case 1:
                printf("\n\t车牌号码:湘");
                break;

            case 2:
                printf("\n\t车牌号码:鄂");
                break;

            case 3:
                printf("\n\t车牌号码:赣");
                break;

            case 4:
                printf("\n\t车牌号码:粤");
                break;

            case 5:
                printf("\n\t车牌号码:京");
                break;

            default:
                printf("\n\t车牌号码:湘");
                break;
            }
        }

        scanf("%9s",carInfo[i].carNo);

        if((carInfo[i].carNo[0] < 'A') || (carInfo[i].carNo[0]>'Z'))
        {
            perror("\n\n\t输入错误!");
            Sleep(100);
            goto ab;
        }

        for(int j=0; j<MAX_CAR_NUM; j++)
        {
            if((i != j) && (strcmp(carInfo[j].carNo,carInfo[i].carNo)==0))
            {
                system("CLS");
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                printf("\n\t\t\t非 法 车 牌 号 !");
                Sleep(1000);
                goto ab;
            }
        }

        printf("\n\t车主姓名:");
        scanf("%9s",carInfo[i].userName);
        printf("\n\t汽车型号:");
        scanf("%9s",carInfo[i].type);
        printf("\n\t汽车颜色:");
        scanf("%9s",carInfo[i].color);

        while((carInfo[i].hour >= MAX_HOUR) ||
                (carInfo[i].hour < 0) ||
                (carInfo[i].minute < 0) ||
                (carInfo[i].minute >= MAX_MINUT))
        {
            perror("输入错误!");
            printf("\n\t现在时间<时,分>");
            scanf("%d,%d",&carInfo[i].hour,&carInfo[i].minute);
        }

        fclose(fp);
        printf("\n\n\t按1键退出\n");

        if(getch() == '1')
        {
            system("CLS");
            login();
        }
    }

    system("CLS");
    perror("\n\n\n\n\n\n\n\t\t\t停车场已满!");
    Sleep(2000);
    login();
}

void login()
{
    system("CLS");
    printf("\n\n\n\n\n\n\n");
    printf("\n\t\t\t----欢迎使用心灵软件----");
    printf("\n\n\t1.输入车辆信息");
    printf("\n\n\t2.查询车辆信息");
    printf("\n\n\t3.查询车库容量");
    printf("\n\n\t4.退出系统");
    printf("\n\n\t\t请选择:");
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
            printf("\n\t\t车 场 无 车 !");
            Sleep(1000);
            system("CLS");
            login();
        }
        else
        {
            printf("\n\n\n\n\n");
            printf("\t\t车库总容量%d个车位",N);
            printf("\n\n\n\t\t\t还有%d个车位!",N-(N-M));
            Sleep(1000);
            printf("\n\n\t\t1.查看所有车辆信息\n\n\t\t2.返回");
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
        printf("\n\n\n\n\n\n\t\t停车场已满!");
    }

    Sleep(1000);
    printf("\n\n\t\t1.查看所有车辆信息\n\n\t\t2.返回");
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
        printf("%d号车位",i+1);

        switch(a)
        {
        case 1:
        {
            printf("\n\n\t车牌号码:湘%s",carInfo[i].carNo);
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",carInfo[i].carNo);
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",carInfo[i].carNo);
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",carInfo[i].carNo);
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",carInfo[i].carNo);
            break;
        }
        }

        printf("\n\n\t车主姓名:%s",carInfo[i].userName);
        printf("\n\n\t汽车型号:%s",carInfo[i].type);
        printf("\n\n\t汽车颜色:%s",carInfo[i].color);
        printf("\n\n\t起始时间:%.0d时%.0d分",carInfo[i].hour,carInfo[i].minute);
        printf("\n\n");
    }

    printf("\t\t按任意键退出");
    getch();
    system("CLS");
    login();
}
void quit()
{
    int sleep;
    printf("\n");
    printf("\n\t\t\t     〓〓");
    printf("\n\t\t\t〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++) //循环次数停止等待
    {}

    system("cls"); //清屏
    printf("\n\n\n");
    printf("\n\t\t\t      〓〓");
    printf("\n\t\t\t 〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n");
    printf("\n\t\t\t       〓〓");
    printf("\n\t\t\t  〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t        〓〓");
    printf("\n\t\t\t   〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t         〓〓");
    printf("\n\t\t\t    〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t           〓〓");
    printf("\n\t\t\t      〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t            〓〓");
    printf("\n\t\t\t       〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t              〓〓");
    printf("\n\t\t\t         〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                〓〓");
    printf("\n\t\t\t           〓○〓〓〓○〓");

    for(sleep=1; sleep<1000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                  〓〓");
    printf("\n\t\t\t             〓○〓〓〓○〓");

    for(sleep=1; sleep<10000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                     〓〓");
    printf("\n\t\t\t                〓○〓〓〓○〓");

    for(sleep=1; sleep<10000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                        〓〓");
    printf("\n\t\t\t                   〓○〓〓〓○〓");

    for(sleep=1; sleep<20000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                          〓〓");
    printf("\n\t\t\t                     〓○〓〓〓○〓");

    for(sleep=1; sleep<20000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                            〓〓");
    printf("\n\t\t\t                       〓○〓〓〓○〓");

    for(sleep=1; sleep<30000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                              〓〓");
    printf("\n\t\t\t                         〓○〓〓〓○〓");

    for(sleep=1; sleep<30000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                                〓〓");
    printf("\n\t\t\t                           〓○〓〓〓○〓");

    for(sleep=1; sleep<50000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t                                  〓〓");
    printf("\n\t\t\t                             〓○〓〓〓○〓");

    for(sleep=1; sleep<80000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n\7\7");
    printf("\n\t\t\t                                    〓〓");
    printf("\n\t\t\t                               〓○〓〓〓○〓  ▲  ");

    for(sleep=1; sleep<100000000; sleep++)
    {}

    system("cls"); //清屏
    printf("\n\n\n\n\n\n\n\n\n\n\7\7\7");
    printf("\n\t\t\t                                       〓〓       请");
    printf("\n\t\t\t                                  〓○〓〓〓●〓  交");
    printf("\n\t\t\t                                            ⊥    费");
    Sleep(1000);
    system("CLS");
    system("color f1");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t 用 !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t使 用 !");
    ;
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t 谢 使 用 !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t谢 谢 使 用 !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t谢 谢 使 用 !");
    Sleep(100);
    system("CLS");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t谢 谢 使 用 !\t\t");
    Sleep(500);
    exit(0);
}

void car_gui()
{
    int i,sleep;

    /**外循环三次使用软件界面*/
    for(i=1; i<=1; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t     〓〓");
        printf("\n\t〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++) //循环次数停止等待
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t       〓〓");
        printf("\n\t  〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t     〓〓");
        printf("\n\t\t〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t     〓〓");
        printf("\n\t\t\t〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t       〓〓");
        printf("\n\t\t\t  〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t     〓〓");
        printf("\n\t\t\t\t〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t       〓〓");
        printf("\n\t\t\t\t  〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\t\t\t\t     〓〓");
        printf("\n\t\t\t\t\t〓○〓〓〓○〓");

        for(sleep=1; sleep<10000000; sleep++)
        {}

        system("cls"); //清屏
    }

    printf("\n\n\n\n\n\n\n\n\n\n\7");
    printf("\n\t\t\t\t\t\t       〓〓        欢 ");
    printf("\n\t\t\t\t\t\t  〓○〓〓〓○〓");
    printf("\n\t\t\t\t\t\t                   迎 ");
    Sleep(1000);
    system("CLS");
    printf("\n\n\n\n\n\n");
    printf("\t\t  　---------------------------------- \n");
    printf("\t\t   ｜※※※※※※※※※※※※※※※※｜\n");
    printf("\t\t   ｜※　　　 欢迎使用本软件　 　  ※｜\n");
    printf("\t\t    ---------------------------------- \n");
    printf("\t\t   ｜※　　 停车场收费管理系统     ※｜\n");
    printf("\t\t   ｜※　　　          　　        ※｜\n");
    printf("\t\t   ｜※　　　     学生: jiangxin      ※｜\n");
    printf("\t\t   ｜※                            ※｜\n");
    printf("\t\t   ｜※※※※※※※※※※※※※※※※｜\n");
    printf("\t\t    ---------------------------------- \n");

    for(int j=0; j<600000000; j++) //用于控制停留时间的长短
    {}

    system("cls");
}
void system_start()
{
    for(int i=1; i<=3; i++)
    {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候.");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t●●\n ");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候.");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t●●● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候..");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t    ●\n ");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候..");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t    ●●\n ");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候...");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t    ●●● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候...");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t        ● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候.....");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t        ●● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候....");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t        ●●● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候.....");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t            ●\n ");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候.....");
        Sleep(100);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t            ●●\n ");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候......");
        Sleep(200);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t            ●●●\n ");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候......");
        Sleep(300);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t              ●●\n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候.");
        Sleep(400);
        system("CLS");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t       〓〓\n");
        printf("\t\t\t\t  〓○〓〓〓○〓\n");
        printf("\t\t\t\t＿＿＿＿＿＿＿＿＿\n");
        printf("\t\t\t\t                ● \n");
        printf("\t\t\t\t￣￣￣￣￣￣￣￣￣\n\n\n");
        printf("\t\t\t\t正在启动  请稍候..");
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
        carInfo[i].carNo[0] = '\0'; //未初始化的标志
        carInfo[i].abbreviation = 1; //初始化所有的简称为"湘"
    }

    /**初始化一个样例 begin*/
    strncpy(carInfo[0].carNo, "B74110", sizeof(carInfo[0].carNo));
    strncpy(carInfo[0].userName, "jiangxin", sizeof(carInfo[0].userName));
    strncpy(carInfo[0].color, "black", sizeof(carInfo[0].color));
    carInfo[0].hour = 11;
    carInfo[0].minute = 20;
    /**初始化一个样例 end*/
    FILE *fp = fopen("data/che.txt","w");

    if(fp == NULL)
    {
        perror("打开文件失败\n");
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
