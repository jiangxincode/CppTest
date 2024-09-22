// ditiDlg.h : header file
//

#if !defined(AFX_DITIDLG_H__3F937DD7_0CCC_4BEE_B853_54F0A653B038__INCLUDED_)
#define AFX_DITIDLG_H__3F937DD7_0CCC_4BEE_B853_54F0A653B038__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "shuzishow.h"
/////////////////////////////////////////////////////////////////////////////
// CDitiDlg dialog

class CDitiDlg : public CDialog
{
// Construction
public:
    bool paint;
	static void liftdown(UINT &floor,CWnd *pWnd);
	static void liftup(UINT &floor,CWnd *pWnd);
	static void orderqueue_j(UINT queue[]);
	static void orderqueue_s(UINT queue[]);
	static void deletequeue(UINT m, UINT queue[]);
	static void insertqueue(UINT m,UINT queue[]);
	static bool lift_moving;
	static UINT liftmove(CWnd *pWnd);
	static UINT OCdoor(CWnd *pWnd);
	CDitiDlg(CWnd* pParent = NULL);	// standard constructor
	static bool OC_flag;
	static int doorlocation;
	shuzishow loucheng;
	shuzishow  m_zhuangtai;
	static UINT lift_updown;//0Í££¬1ÉÏ£¬2ÏÂ
	static UINT floorID;
	static UINT upqueue[8];
	static UINT downqueue[8];
	static UINT mudi[8];
	static bool threadt_f;
	CBitmap Bitmap;
	HBITMAP hBitmap;
static	CWnd *pWnddoor;
static	CWnd *pWndlift;
static  bool ocf;
static CWinThread *threadlift;
static HANDLE handle;
UINT people;
UINT showf;
UINT showzt;
CString loucengshow;
CString zhuangtaishow;
// Dialog Data
	//{{AFX_DATA(CDitiDlg)
	enum { IDD = IDD_DITI_DIALOG };
	CComboBox	m_jindianti;
	CComboBox	m_chudianti;
	UINT	m_people;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDitiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDitiDlg)
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
	afx_msg void On8xia();
	afx_msg void On7xia();
	afx_msg void On6xia();
	afx_msg void On5xia();
	afx_msg void On4xia();
	afx_msg void On3xia();
	afx_msg void On2xia();
	afx_msg void On7shang();
	afx_msg void On6shang();
	afx_msg void On5shang();
	afx_msg void On4shang();
	afx_msg void On3shang();
	afx_msg void On2shang();
	afx_msg void On1shang();
	afx_msg void Onopen();
	afx_msg void Onclose();
	afx_msg void OnSelchangeCOMBOchu();
	afx_msg void OnSelchangeCOMBOjin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DITIDLG_H__3F937DD7_0CCC_4BEE_B853_54F0A653B038__INCLUDED_)





















