
// RadioButtonDlg.h : ͷ�ļ�
//

#pragma once


// CRadioButtonDlg �Ի���
class CRadioButtonDlg : public CDialogEx
{
// ����
public:
	CRadioButtonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RADIOBUTTON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_spring;
	BOOL m_fl1;
	afx_msg void OnBnClickedOk();
};
