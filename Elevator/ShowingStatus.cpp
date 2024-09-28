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
    for (k = 0; k < num - iconType.GetLength(); k++)//���ǰ���ͼ����ʾ
    {
        CImageList imageList;
        imageList.Create(IDB_BITMAP1, 12, 1, RGB(255, 255, 255));//����λͼ�� ÿ��λͼ12����
        HICON myIcon = imageList.ExtractIcon(10);	//ȡ��ͼ��
        pictureList[k]->SetIcon(myIcon);//������ʾ��ͼ��
    }
    for (int i = k; i < num; i++)//�������ͼ����ʾ
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
    for (int i = 0; i < num; i++)// ɾ����ǰ�����
        delete* (pictureList + i);
    // ���ø���Ա����
    num = tnum; x = tx; y = ty; space = tspace;
    for (int j = 0; j < num; j++)//���·���
        pictureList[j] = new(CStatic);
    for (int k = 0; k < num; k++)
    {
        //ȷ����ʾλ��
        CRect aa1(x + k * (space + 12), y, 40 + x + k * (space + 12), 40 + y);
        pictureList[k]->Create(NULL, SS_ICON, aa1, mypar, 1);// ������̬ͼ��ؼ�
        pictureList[k]->ShowWindow(true);
    }
}
