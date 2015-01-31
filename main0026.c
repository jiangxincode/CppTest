#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/**停车管理收费系统*/

void systemstart();//系统登录界面
void chexh();      //小车界面
void denglu();     //登录界面
void shuru();//输入界面
void chaxun();  //查询车辆信息界
void tingche(int i);  //停车信息界面
void chezhumingchaxun();//按车主姓名查询
void chehaochaxun();//按车牌号码查询
float chongshe();//重新设置停车费率
int jiancheng();
void tianjia();
void tuichu();
void shanchu(int i);
void shurudiaoyong();
void chekurongliang();
void chekuxinxi();
void xingmingchaxun(int i,int a,int k);

#define N 2  //宏定义

struct chexinxi
{
    char chepaihao[10];
    char yonghuming[20];
    char yanse[10];
    char xinghao[10];
    float shijianshi;
    float shijianfen;
    int jiancheng;
} stu[N]= {{"B74110","huanghe","heise","benchi600",11,20,1}};

void mytime()
{
    time_t ltime;
    time(&ltime);
    printf("现在时间:%s",ctime(&ltime));
}

float chongshe()
{
    printf("\n\n\n\n\n\n\n");
    printf("\n\n\t\t---设置停车费率---");
    printf("\n\n\t\t请输入新的费率:");
    float a;
    scanf("%f",&a);
    return a;
}


void tingche(int i)
{
    float shijianshi,shijianfen;
    float n=0.5;
    printf("\n\n\n\n\n\n");
    printf("\t\t---停车信息查询---");
    printf("\n\n\t默认停车费用0.5元/小时   按 1 键重设");

    if(getch()=='1')
    {
        system("CLS");
        n=chongshe();
    }

    system("CLS");
    printf("现在时间:");
    mytime();
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t---停车信息查询---");
    printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
n:
    printf("\n\n\t输入现在时间:");
    scanf("%f,%f",&shijianshi,&shijianfen);

    if(shijianshi<0.0||shijianshi>24.0||shijianfen<0.0||shijianfen>60.0)
    {
        printf("输入错误!");
        goto n;
    }

    float shi,fen;

    if(shijianshi-stu[i].shijianshi<0)
    {
        if((shijianfen-stu[i].shijianfen)<0)
        {
            shi=shijianshi-stu[i].shijianshi-1+24;
            fen=60-(stu[i].shijianfen-shijianfen);
        }
        else
        {
            shi=shijianshi-stu[i].shijianshi+24;
            fen=shijianfen-stu[i].shijianfen;
        }
    }

    if(shijianshi-stu[i].shijianshi==0)
    {
        if((shijianfen-stu[i].shijianfen)<0)
        {
            shi=shijianshi-stu[i].shijianshi+23;
            fen=60-(stu[i].shijianfen-shijianfen);
        }
        else
        {
            shi=shijianshi-stu[i].shijianshi;
            fen=shijianfen-stu[i].shijianfen;
        }
    }

    if(shijianshi-stu[i].shijianshi>0)
    {
        if((shijianfen-stu[i].shijianfen)<0)
        {
            shi=shijianshi-stu[i].shijianshi-1;
            fen=60-(stu[i].shijianfen-shijianfen);
        }
        else
        {
            shi=shijianshi-stu[i].shijianshi;
            fen=shijianfen-stu[i].shijianfen;
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
    denglu();
}
void shanchu(int i)
{
    strcpy(stu[i].chepaihao,"000000000");
    strcpy(stu[i].yonghuming,"000000000");
    printf("\n\n\n\n\n\n\n\t\t\t请 稍 候 …");
    Sleep(500);
    system("CLS");
    printf("\n\n\n\n\n\n\n\t\t\t请 稍 候 ……");
    Sleep(500);

    if(stu[i].chepaihao[0]=='0'&&stu[i].yonghuming[0]=='0')
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
void chehaochaxun()//车牌号查询
{
    char chepaihao[10];
    int a;
    int i = 0;
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t----简称选择----");
    printf("\n\n\t\t1.湘  2.鄂  3.赣  4.粤  5.京  ");
    scanf("%d",&a);
m:

    switch(a)
    {
    case 1:
        system("CLS");
        printf("\n\n\n\t\t\t---请输入车牌号码---\n\n");
        printf("\n\t车牌号码:湘");
        break;

    case 2:
        system("CLS");
        printf("\n\n\n\t\t\t---请输入车牌号码---\n\n");
        printf("\n\t车牌号码:鄂");
        break;

    case 3:
        system("CLS");
        printf("\n\n\n\t\t\t---请输入车牌号码---\n\n");
        printf("\n\t车牌号码:赣");
        break;

    case 4:
        system("CLS");
        printf("\n\n\n\t\t\t---请输入车牌号码---\n\n");
        printf("\n\t车牌号码:粤");
        break;

    case 5:
        system("CLS");
        printf("\n\n\n\t\t\t---请输入车牌号码---\n\n");
        printf("\n\t车牌号码:京");
        break;
    }

    scanf("%s",chepaihao);

    if(chepaihao[0]<'A'||chepaihao[0]>'Z')
    {
        printf("\n\n\t输入错误!");
        Sleep(100);
        goto m;
    }

    for(i=0; i<N; i++)
    {
        if(strcmp(stu[i].chepaihao,chepaihao)==0)
            break;
    }

    if(strcmp(stu[i].chepaihao,chepaihao)==0)
    {
        switch(a)
        {
        case 1:
        {
            printf("\n\n\t车牌号码:湘%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }
        }

        if(getch()=='1')
        {
            system("CLS");
            tingche(i);
        }
        else
        {
            system("CLS");
            chaxun();
        }
    }

    {
        printf("\n\n\t没有这辆车的信息!");
        printf("\n\n\t按任意键返回");
        getch();
        system("CLS");
        chaxun();
    }
}
void chezhumingchaxun()//车主名查询
{
    char chezhuming[10];
    printf("\n\n\n\n\n\n");
    printf("请输入车主姓名:");
    scanf("%s",chezhuming);
    int i = 0;

    for(i=0; i<N; i++)
    {
        if((strcmp(stu[i].yonghuming,chezhuming))==0)
            break;
    }

    if((strcmp(stu[i].yonghuming,chezhuming))==0)
    {
        int	a=stu[i].jiancheng;//printf("此处正常!%d",a);

        switch(a)
        {
        case 1:
        {
            printf("\n\n\t车牌号码:湘%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按1键查看停车信息:");
            break;
        }
        }

        int k=i;

        for(i=i+1; i<N; i++)
        {
            if((strcmp(stu[i].yonghuming,chezhuming))==0)
                xingmingchaxun(i,a,k);
        }

        if(getch()=='1')
        {
            system("CLS");
            tingche(k);
        }
        else
        {
            system("CLS");
            chaxun();
        }
    }
    else
    {
        printf("\n\n\t没有这辆车的信息!");
        printf("\n\n\t按任意键返回");
        getch();
        system("CLS");
        chaxun();
    }
}
void xingmingchaxun(int i,int a,int k)
{
    if(1)
    {
        switch(a)
        {
        case 1:
        {
            printf("\n\n\t车牌号码:湘%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按2键查看停车信息:");
            break;
        }

        case 2:
        {
            printf("\n\n\t车牌号码:鄂%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按2键查看停车信息:");
            break;
        }

        case 3:
        {
            printf("\n\n\t车牌号码:赣%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按2键查看停车信息:");
            break;
        }

        case 4:
        {
            printf("\n\n\t车牌号码:粤%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按2键查看停车信息:");
            break;
        }

        case 5:
        {
            printf("\n\n\t车牌号码:京%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            printf("\n\n\n\t按2键查看停车信息:");
            break;
        }
        }
    }

    int n;
    scanf("%d",&n);

    switch(n)
    {
    case 1:
        system("CLS");
        tingche(k);
        break;

    case 2:
        system("CLS");
        tingche(i);
        break;
    }
}

void chaxun()
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
        chehaochaxun();

    case 2:
        system("CLS");
        chezhumingchaxun();

    case 3:
        system("CLS");
        denglu();
    }
}



void shuru()
{
    int i = 0 , j = 0;

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(stu[j].chepaihao[0]==0||stu[j].chepaihao[0]=='0')
                break;
        }

        if(j>=N)
        {
            system("CLS");
            printf("\n\n\n\n\n\n\n\t\t\t停车场已满!");
            Sleep(1000);
            system("CLS");
            denglu();
        }

        i=j;
        FILE *fp;
        fp=fopen("che.txt","wb");

        if(fp==NULL)//是否能打开文件
        {
            printf("打开文件失败\n");
            exit(1);
        }

        fwrite(&stu[i],sizeof(struct chexinxi),1,fp);//写入文件
        system("CLS");

        if(1)
        {
            system("CLS");
            mytime();
            printf("\n\n\n\t第%d个车位",i+1);
            printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
            printf("\n\t按1键选择简称");
            printf("\n\n\t车牌号码:湘");
            int a;
            char j = getch();

            if(j=='1')
            {
                system("CLS");
                printf("\n\n\n\t第%d个车位",i+1);
                printf("\n\n\n\n\n\n\n");
                printf("\n\n\t\t----简称选择----");
                printf("\n\n\t\t1.湘  2.鄂  3.赣  4.粤  5.京  ");
                scanf("%d",&a);
                stu[i].jiancheng=a;
            }

ab:

            if(a>0&&a<10)
            {
                switch(a)
                {
                case 1:
                    system("CLS");
                    mytime();
                    printf("\n\n\n\t第%d个车位",i+1);
                    printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
                    printf("\n\t车牌号码:湘");
                    scanf("%s",stu[i].chepaihao);
                    break;

                case 2:
                    system("CLS");
                    mytime();
                    printf("\n\n\n\t第%d个车位",i+1);
                    printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
                    printf("\n\t车牌号码:鄂");
                    scanf("%s",stu[i].chepaihao);
                    break;

                case 3:
                    system("CLS");
                    mytime();
                    printf("\n\n\n\t第%d个车位",i+1);
                    printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
                    printf("\n\t车牌号码:赣");
                    scanf("%s",stu[i].chepaihao);
                    break;

                case 4:
                    system("CLS");
                    mytime();
                    printf("\n\n\n\t第%d个车位",i+1);
                    printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
                    printf("\n\t车牌号码:粤");
                    scanf("%s",stu[i].chepaihao);
                    break;

                case 5:
                    system("CLS");
                    mytime();
                    printf("\n\n\n\t第%d个车位",i+1);
                    printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
                    printf("\n\t车牌号码:京");
                    scanf("%s",stu[i].chepaihao);
                    break;
                }
            }
            else
            {
                system("CLS");
                mytime();
                printf("\n\n\n\t第%d个车位",i+1);
                printf("\n\n\n\t\t\t---请输入车辆信息---\n\n");
                printf("\n\t车牌号码:湘");
                scanf("%s",stu[i].chepaihao);
                stu[i].jiancheng=1;
            }

            if(stu[i].chepaihao[0]<'A'||stu[i].chepaihao[0]>'Z')
            {
                printf("\n\n\t输入错误!");
                Sleep(100);
                goto ab;
            }

            int m=0;

            for(int j=0; j<N; j++)
            {
                if(strcmp(stu[j].chepaihao,stu[i].chepaihao)==0)
                {
                    m++;
                }
            }

            if(m>1)
            {
                system("CLS");
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                printf("\n\t\t\t非 法 车 牌 号 !");
                Sleep(1000);
                goto ab;
            }

            printf("\n\t车主姓名:");
            scanf("%s",stu[i].yonghuming);
            printf("\n\t汽车型号:");
            scanf("%s",stu[i].xinghao);
            printf("\n\t汽车颜色:");
            scanf("%s",stu[i].yanse);
m:
            printf("\n\t现在时间<时,分>");
            scanf("%f,%f",&stu[i].shijianshi,&stu[i].shijianfen);

            if(stu[i].shijianshi>24.0||stu[i].shijianshi<0.0||stu[i].shijianfen<0.0||stu[i].shijianfen>60.0)
            {
                printf("输入错误!");
                goto m;
            }

            fclose(fp);
            printf("\n\n\t按1键退出\n");

            if(getch()=='1')
            {
                system("CLS");
                denglu();
            }
        }
    }

    system("CLS");
    printf("\n\n\n\n\n\n\n\t\t\t停车场已满!");
    Sleep(2000);
    system("CLS");
    denglu();
}

void denglu()
{
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
        system("CLS");
        shuru();
        break;

    case 2:
        system("CLS");
        chaxun();
        break;

    case 3:
        system("CLS");
        chekurongliang();
        break;

    case 4:
        system("CLS");
        tuichu();
        break;

    default:
        denglu();
    }
}

void chekurongliang()
{
    int M=0;

    for(int J=0; J<N; J++)
    {
        if(stu[J].chepaihao[0]==0||stu[J].chepaihao[0]=='0')
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
            denglu();
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
                chekuxinxi();
            }
            else
            {
                system("CLS");
                denglu();
            }
        }
    }
    else
        printf("\n\n\n\n\n\n\t\t停车场已满!");

    Sleep(1000);
    printf("\n\n\t\t1.查看所有车辆信息\n\n\t\t2.返回");
    printf("\n\n\t\t\t---");
    int b;
    scanf("%d",&b);

    if(b==1)
    {
        system("CLS");
        chekuxinxi();
    }

    system("CLS");
    denglu();
}
void chekuxinxi()
{
    for(int i=0; i<N; i++)
    {
        if(stu[i].chepaihao[0]==0||stu[i].chepaihao[0]=='0')
            continue;

        int	a=stu[i].jiancheng;

        switch(a)
        {
        case 1:
        {
            printf("%d号车位",i+1);
            printf("\n\n\t车牌号码:湘%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            break;
        }

        case 2:
        {
            printf("%d号车位",i+1);
            printf("\n\n\t车牌号码:鄂%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            break;
        }

        case 3:
        {
            printf("%d号车位",i+1);
            printf("\n\n\t车牌号码:赣%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            break;
        }

        case 4:
        {
            printf("%d号车位",i+1);
            printf("\n\n\t车牌号码:粤%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            break;
        }

        case 5:
        {
            printf("%d号车位",i+1);
            printf("\n\n\t车牌号码:京%s",stu[i].chepaihao);
            printf("\n\n\t车主姓名:%s",stu[i].yonghuming);
            printf("\n\n\t汽车型号:%s",stu[i].xinghao);
            printf("\n\n\t汽车颜色:%s",stu[i].yanse);
            printf("\n\n\t起始时间:%.0f时%.0f分",stu[i].shijianshi,stu[i].shijianfen);
            break;
        }
        }

        printf("\n\n");
    }

    printf("\t\t按任意键退出");
    getch();
    system("CLS");
    denglu();
}
void tuichu()
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





void chexh()
{
    int start,sleep;

    for(start=1; start<=1; start++) //外循环三次使用软件界面
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
    printf("\t\t   ｜※　　　     学生: 黄 河      ※｜\n");
    printf("\t\t   ｜※                            ※｜\n");
    printf("\t\t   ｜※              2009年08月31日※｜\n");
    printf("\t\t   ｜※※※※※※※※※※※※※※※※｜\n");
    printf("\t\t    ---------------------------------- \n");

    for(int j=0; j<600000000; j++)   //用于控制停留时间的长短
    {}

    system("cls");
}
void systemstart()
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
    FILE *fp;
    fp=fopen("che.txt","w");

    if(fp==NULL)//是否能打开文件
    {
        printf("打开文件失败\n");
        exit(1);
    }

    fwrite(stu,sizeof(struct chexinxi),1,fp);//写入文件
    rewind(fp);
    fclose(fp);
    systemstart();
    chexh();
    denglu();
    return 0;
}
