// DlgBlueToothExc.h : header file
//

#pragma once

#include "BlueTooth.h"
#include "HwCOM.h"

// CDlgBlueToothExc dialog
class CDlgBlueToothExc : public CDialog
{
// Construction
public:
	CDlgBlueToothExc(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DLGBLUETOOTHMAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CBlueTooth m_BlueTooth;
public:
	afx_msg void OnBnClickedButtonScanbluetoothdevice();
public:
	afx_msg void OnLbnDblclkListNearbybthdev();
public:
	afx_msg void OnBnClickedButtonTest();
public:
	afx_msg void OnBnClickedButtonEnumerate();
public:
	afx_msg void OnBnClickedButtonRequestauthenticate();
public:
	BOOL GetCur_LocalRadioInfo(t_LocalRadioInfo& LocalRadioInfo);
public:
	int GetListCurSel(UINT nID, LPCTSTR lpszMsg);
public:
	afx_msg void OnDestroy();
	CHwCOM *m_pHwCOM;
public:
	void DeleteCOMObject(void);
public:
	afx_msg void OnBnClickedButtonConnect();

	HANDLE m_hEvtEndThread;
	HANDLE m_hEvtSendDataReq;
	DWORD m_dwThreadID;
	HANDLE m_hThread;

public:
	void ThreadProc_COM(void);
public:
	void ExitCOMThread(void);
public:
	afx_msg void OnBnClickedButtonDisconnect();
public:
	void ReadDataAndDisplay(void);
public:
	afx_msg void OnBnClickedButtonSend();

	BYTE m_DataForSending[MAX_COM_BUFSIZE];
	int m_nBytesForSending;
	CCriticalSection m_CSFor_DataForSending;
	BOOL m_bNoteBeCleared;
public:
	afx_msg void OnBnClickedButtonClearup();
public:
	void CalcAndShowDataLength(UINT nEditID, UINT nStaticID, bool bHex);
public:
	afx_msg void OnBnClickedButtonTest1();
public:
	afx_msg void OnEnSetfocusSendtext();
public:
	afx_msg void OnBnClickedButtonReceive();
public:
	BOOL SendData(BYTE* data, int size);
public:
	afx_msg void OnBnClickedButtonFinished();
	BOOL m_bShowCurve;
private:
	void EnableWindow_ConnCOM(bool bEnable);
//	afx_msg void OnLbnSelchangeListNearbybthdev();
	afx_msg void OnBnClickedCheckReceivedontimer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
