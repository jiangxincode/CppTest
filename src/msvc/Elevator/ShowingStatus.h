#if !defined(AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
#define AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ShowingStatus
{
public:
    void set(CDialog* parent, int tnum, int tx, int ty, int tspace);
    void showIcon(CString temp);
    int getIconIndex(char a);
    ShowingStatus();
    CStatic* pictureList[50];// ��̬ͼ ָ������

    virtual ~ShowingStatus();
    int num;// ��̬ͼ����
    int x;// ��ʼX����
    int y;// ��ʼY����
    int space;// ������֮�� ���

};

#endif // !defined(AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
