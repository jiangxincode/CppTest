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
    CStatic* pictureList[50];// 静态图 指针数组

    virtual ~ShowingStatus();
    int num;// 静态图个数
    int x;// 起始X坐标
    int y;// 起始Y坐标
    int space;// 各数码之间 间距

};

#endif // !defined(AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
