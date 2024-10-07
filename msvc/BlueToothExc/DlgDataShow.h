#pragma once

#include "PublicFunc.h"
#include "StaticDataCurve.h"
#include "afxwin.h"
#include "afxcmn.h"

// CDlgDataShow 对话框

class CDlgDataShow : public CDialog
{
	DECLARE_DYNAMIC(CDlgDataShow)

public:
	CDlgDataShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDataShow();
	static CDlgDataShow *m_pDlg;

// 对话框数据
	enum { IDD = IDD_DlgDataShow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	static CDlgDataShow* GetInstance(void);
	static void DeleteInstance(void);
	void ShowCurStartPos(int nCurStartPos);
	void DrawDataCurve(BYTE* data, int size);
public:
	CStaticDataCurve m_staticCurve;
	CSliderCtrl m_SliderGraph;
protected:
	void OnCancel(void);
	void OnClose(void);
	void OnOK(void);
private:
	void Align(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonDynamic();
	afx_msg void OnDeltaposSpinStep(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinInterval(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditStep();
	afx_msg void OnEnChangeEditInterval();
	afx_msg void OnBnClickedButtonZoomin();
	afx_msg void OnBnClickedButtonZoomout();
private:
	void ShowScale(void);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonFromfile();
};
