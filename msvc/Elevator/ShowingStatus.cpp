#include "stdafx.h"
#include "Elevator.h"
#include "ShowingStatus.h"
#include "ElevatorDlg.h"

ShowingStatus::ShowingStatus()
{
}

ShowingStatus::~ShowingStatus()
{
}

int ShowingStatus::getIconIndex(char a)
{
    switch (a)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':return a - '0';
        break;
    case '<':return 10;
        break;
    case '>':return 11;
        break;
    default: return 0;
    }
}

void ShowingStatus::showIcon(CString iconType)
{
    int k;
    for (k = 0; k < num - iconType.GetLength(); k++)//添加前面空图标显示
    {
        CImageList imageList;
        imageList.Create(IDB_BITMAP1, 12, 1, RGB(255, 255, 255));//创建位图链 每个位图12像素
        HICON myIcon = imageList.ExtractIcon(10);	//取出图标
        pictureList[k]->SetIcon(myIcon);//设置显示的图标
    }
    for (int i = k; i < num; i++)//添加数字图标显示
    {
        CImageList imageList;
        imageList.Create(IDB_BITMAP1, 12, 1, RGB(255, 255, 255));
        HICON myIcon = imageList.ExtractIconA(getIconIndex(iconType[i - k]));
        pictureList[i]->SetIcon(myIcon);
    }
}

void ShowingStatus::set(CDialog* parent, int tnum, int tx, int ty, int tspace)
{
    CElevatorDlg* mypar = (CElevatorDlg*)parent;
    for (int i = 0; i < num; i++)// 删除以前分配的
        delete* (pictureList + i);
    // 设置各成员变量
    num = tnum; x = tx; y = ty; space = tspace;
    for (int j = 0; j < num; j++)//重新分配
        pictureList[j] = new(CStatic);
    for (int k = 0; k < num; k++)
    {
        //确定显示位置
        CRect aa1(x + k * (space + 12), y, 40 + x + k * (space + 12), 40 + y);
        pictureList[k]->Create(NULL, SS_ICON, aa1, mypar, 1);// 创建静态图标控件
        pictureList[k]->ShowWindow(true);
    }
}
