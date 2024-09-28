#if !defined(AFX_ELEVATOR_DLG_H__3F937DD7_0CCC_4BEE_B853_54F0A653B038__INCLUDED_)
#define AFX_ELEVATOR_DLG_H__3F937DD7_0CCC_4BEE_B853_54F0A653B038__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ShowingStatus.h"
/////////////////////////////////////////////////////////////////////////////
// CElevatorDlg dialog

class CElevatorDlg : public CDialog
{
    // Construction
public:
    bool paint;
    static void liftDown(UINT& floor, CWnd* pWnd);
    static void liftUp(UINT& floor, CWnd* pWnd);
    static void orderqueue_j(UINT queue[]);
    static void orderqueue_s(UINT queue[]);
    static void deleteQueue(UINT m, UINT queue[]);
    static void insertqueue(UINT m, UINT queue[]);
    void OnInternal(UINT floatNumber);
    void OnDownInternal(UINT floorNumber);
    void OnUpInternal(UINT floorNumber);
    static bool lift_moving;
    static UINT liftMove(CWnd* pWnd);
    static UINT OpenCloseDoor(CWnd* pWnd);
    CElevatorDlg(CWnd* pParent = NULL);	// standard constructor
    static bool OC_flag;
    static int doorlocation;
    ShowingStatus floorNumber;
    ShowingStatus  status;
    static UINT currentStatus;//0Í££¬1ÉÏ£¬2ÏÂ
    static UINT currentFloorNumber;
    static UINT upQueue[8];
    static UINT downQueue[8];
    static UINT targetQueue[8];
    static bool threadt_f;
    CBitmap Bitmap;
    HBITMAP hBitmap;
    static	CWnd* pWnddoor;
    static	CWnd* pWndlift;
    static  bool ocf;
    static CWinThread* threadlift;
    static HANDLE handle;
    UINT people;
    UINT showingCurrentFloorNumber;
    UINT showingCurrentStatus;
    // Dialog Data
        //{{AFX_DATA(CElevatorDlg)
    enum { IDD = IDD_ELEVATOR_DIALOG };
    CComboBox	ComBoBoxPeopleIn;
    CComboBox	ComBoBoxPeopleOut;
    UINT	m_people;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CElevatorDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CElevatorDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void On1();
    afx_msg void On8();
    afx_msg void On2();
    afx_msg void On3();
    afx_msg void On4();
    afx_msg void On5();
    afx_msg void On6();
    afx_msg void On7();
    afx_msg void OnDown8();
    afx_msg void OnDown7();
    afx_msg void OnDown6();
    afx_msg void OnDown5();
    afx_msg void OnDown4();
    afx_msg void OnDown3();
    afx_msg void OnDown2();
    afx_msg void OnUp7();
    afx_msg void OnUp6();
    afx_msg void OnUp5();
    afx_msg void OnUp4();
    afx_msg void OnUp3();
    afx_msg void OnUp2();
    afx_msg void OnUp1();
    afx_msg void OnOpen();
    afx_msg void Onclose();
    afx_msg void OnPeopleOut();
    afx_msg void OnPeopleIn();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEVATOR_DLG_H__3F937DD7_0CCC_4BEE_B853_54F0A653B038__INCLUDED_)
