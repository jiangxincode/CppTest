// DlgBlueToothExc.cpp : implementation file
//

#include "stdafx.h"
#include "BlueToothExc.h"
#include "DlgDataShow.h"
#include "DlgBlueToothExc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDlgBlueToothExc dialog




CDlgBlueToothExc::CDlgBlueToothExc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBlueToothExc::IDD, pParent)
	, m_pHwCOM ( NULL )
	, m_hThread ( NULL )
	, m_dwThreadID ( 0 )
	, m_hEvtEndThread ( NULL )
	, m_hEvtSendDataReq ( NULL )
	, m_nBytesForSending ( 0 )
	, m_bNoteBeCleared ( FALSE )
	, m_bShowCurve(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset ( m_DataForSending, 0, sizeof(m_DataForSending) );
	DeleteFile ( _T("c:\\bthdebug.dat") );
}

void CDlgBlueToothExc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgBlueToothExc, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_ScanBluetoothDevice, &CDlgBlueToothExc::OnBnClickedButtonScanbluetoothdevice)
	ON_LBN_DBLCLK(IDC_LIST_NearbyBthDev, &CDlgBlueToothExc::OnLbnDblclkListNearbybthdev)
	ON_BN_CLICKED(IDC_BUTTON_Test, &CDlgBlueToothExc::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_Enumerate, &CDlgBlueToothExc::OnBnClickedButtonEnumerate)
	ON_BN_CLICKED(IDC_BUTTON_RequestAuthenticate, &CDlgBlueToothExc::OnBnClickedButtonRequestauthenticate)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_Connect, &CDlgBlueToothExc::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_Disconnect, &CDlgBlueToothExc::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_Send, &CDlgBlueToothExc::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_Clearup, &CDlgBlueToothExc::OnBnClickedButtonClearup)
	ON_BN_CLICKED(IDC_BUTTON_Test1, &CDlgBlueToothExc::OnBnClickedButtonTest1)
	ON_EN_SETFOCUS(IDC_SENDTEXT, &CDlgBlueToothExc::OnEnSetfocusSendtext)
	ON_BN_CLICKED(IDC_BUTTON_Receive, &CDlgBlueToothExc::OnBnClickedButtonReceive)
	ON_BN_CLICKED(IDC_BUTTON_Finished, &CDlgBlueToothExc::OnBnClickedButtonFinished)
//	ON_LBN_SELCHANGE(IDC_LIST_NearbyBthDev, &CDlgBlueToothExc::OnLbnSelchangeListNearbybthdev)
ON_BN_CLICKED(IDC_CHECK_ReceivedOnTimer, &CDlgBlueToothExc::OnBnClickedCheckReceivedontimer)
ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgBlueToothExc message handlers
BOOL CDlgBlueToothExc::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 初始化控件
	( (CButton*)GetDlgItem(IDC_CHECK_ShowRemembered) )->SetCheck ( TRUE );

	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_COM);
	ASSERT ( pCombo );
	for ( int i=0; i<32; i++ )
	{
		CString csCom;
		csCom.Format ( L"COM%d", i+1 );
		pCombo->AddString ( csCom );
	}
	pCombo->SetCurSel ( 1-1 );	// 默认在控件中显示的端口号
	GetDlgItem(IDC_EDIT_Baud)->SetWindowText ( L"115200" );
	EnableWindow_ConnCOM ( FALSE );
	( (CButton*)GetDlgItem(IDC_CHECK_Hex) )->SetCheck ( TRUE );

//	SetDlgItemText ( IDC_EDIT_ReceivedData_Hex, Data2HexString ( (char*)NOTE_Bluetooth, (int)wcslen(NOTE_Bluetooth) ) );
//	GetDlgItem(IDC_EDIT_ReceivedData_Hex)->SendMessage ( WM_VSCROLL, (WPARAM)SB_BOTTOM, (LPARAM)NULL );	// 滚动在最底行
//	SetDlgItemText ( IDC_EDIT_ReceivedData_String, NOTE_Bluetooth );
//	GetDlgItem(IDC_EDIT_ReceivedData_String)->SendMessage ( WM_VSCROLL, (WPARAM)SB_BOTTOM, (LPARAM)NULL );	// 滚动在最底行

	SetDlgItemText ( IDC_STATIC_ReceivedData_Hex_Length, _T("") );
	SetDlgItemText ( IDC_STATIC_ReceivedData_String_Length, _T("") );

	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_Segment);
	ASSERT ( pCombo );
	pCombo->SetCurSel ( 0 );
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_Section);
	ASSERT ( pCombo );
	pCombo->SetCurSel ( 0 );
	
	// 初始化显示心电数据的框
	CDlgDataShow *pDlgDataShow = CDlgDataShow::GetInstance ();
	if ( pDlgDataShow )
	{
		CRect rcClient;
		pDlgDataShow->GetWindowRect ( &rcClient );
		CSize szArea = GetWorkAreaSize ();
		CRect rcDataShow ( 0, 0, szArea.cx, rcClient.Height() );
		pDlgDataShow->MoveWindow ( rcDataShow );

		CRect rcMainWnd;
		CenterWindow ();
		GetWindowRect ( &rcMainWnd );
		int nMainWndHeight = rcMainWnd.Height();
		rcMainWnd.top = rcDataShow.bottom;
		rcMainWnd.bottom = rcMainWnd.top + nMainWndHeight;
		MoveWindow ( &rcMainWnd );
	}

	return TRUE;  // return TRUE  unless you set the focus to a control

}

void CDlgBlueToothExc::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgBlueToothExc::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgBlueToothExc::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//搜索蓝牙设备
void CDlgBlueToothExc::OnBnClickedButtonScanbluetoothdevice()
{
	// 先确定本地蓝牙设备，如果还没有就查找
	t_LocalRadioInfo LocalRadioInfo;
	if ( !GetCur_LocalRadioInfo ( LocalRadioInfo ) ) return;

	// 搜索附近的蓝牙设备，并添加到列表中
	CListBox *pListBox_NearbyBthDev = (CListBox*)GetDlgItem ( IDC_LIST_NearbyBthDev );
	ASSERT ( pListBox_NearbyBthDev );
	pListBox_NearbyBthDev->ResetContent ();

	BOOL fReturnRemembered = ( (CButton*)GetDlgItem(IDC_CHECK_ShowRemembered) )->GetCheck ();
	BOOL fIssueInquiry = ( (CButton*)GetDlgItem(IDC_CHECK_IssueInquiry) )->GetCheck ();
	int nCount = 0;
	if ( ( (CButton*)GetDlgItem(IDC_CHECK_Wizard) )->GetCheck () )
	{
		nCount = m_BlueTooth.ScanNearbyBthDev_Wizard ( GetSafeHwnd(), LocalRadioInfo.hRadio, _T("我现在正在搜索周边的蓝牙设备，您别打扰我！ -- 谢红伟"),
			FALSE, TRUE, fReturnRemembered, TRUE, TRUE, TRUE );
	}
	else
	{
		nCount = m_BlueTooth.ScanNearbyBthDev ( LocalRadioInfo.hRadio, TRUE, fReturnRemembered, TRUE, TRUE, fIssueInquiry );
	}
	
	if ( nCount <= 0 )
	{
		if ( nCount < 0 ) AfxMessageBox ( _T("Scan nearby bluetooth device failed") );
		return;
	}

	for ( int i=0; i<nCount; i++ )
	{
		t_RemoteBthDevInfo &RemoteBthDevInfo = m_BlueTooth.m_Ary_RemoteBthDevInfo.GetAt(i);
		CString csItemString;
		csItemString.Format ( _T("%s ( %s )"), RemoteBthDevInfo.szName, m_BlueTooth.FormatBthAddress ( RemoteBthDevInfo.Address.rgBytes ) );
		pListBox_NearbyBthDev->AddString ( csItemString );
	}
}

void CDlgBlueToothExc::OnLbnDblclkListNearbybthdev()
{
	int nSel = GetListCurSel ( IDC_LIST_NearbyBthDev, _T("Please select remote bluetooth device") );
	if ( nSel < 0  ) return;
	m_BlueTooth.ShowPropertySheet ( nSel, GetSafeHwnd() );
}

void CDlgBlueToothExc::OnBnClickedButtonTest()
{
	CString csFileName = L"C:\\UHolter_multi\\3.txt";
	int nFileSize = hwGetFileAttr ( csFileName );
	if ( nFileSize < 1 ) return;
	char* strdata = new char[nFileSize];
	if ( !strdata ) return;
	char *data = new char[nFileSize];
	wchar_t *wdata = new wchar_t[nFileSize*2];

	int nReadBytes = ReadDataFromFile ( csFileName, strdata, nFileSize );
	if ( nReadBytes > 1 )
	{
		MultiByteToWideChar(CP_ACP, 0, (char*)strdata, nReadBytes, wdata, 2*nFileSize);
		int nDataSize = ConvStringToHexData ( wdata, (BYTE*)data, nFileSize );
		WriteDataToFile ( L"C:\\UHolter_multi\\data.dat", data, nDataSize, L"wb" );
	}

//	m_BlueTooth.Test ();
	
}

//显示搜索到的蓝牙设备
void CDlgBlueToothExc::OnBnClickedButtonEnumerate()
{
	CListBox *pListBox = (CListBox*)GetDlgItem ( IDC_LIST_LocalBluetoothRadios );
	ASSERT ( pListBox );
	pListBox->ResetContent ();
	int nCount = m_BlueTooth.EnumerateLocalRadios ();
	if ( nCount <= 0 )
	{
		AfxMessageBox ( _T("None any local bluetooth radios") );
		return;
	}
	for ( int i=0; i<nCount; i++ )
	{
		t_LocalRadioInfo &LocalRadioInfo = m_BlueTooth.m_Ary_LocalRadioInfo.GetAt(i);
		CString csItemString;
		csItemString.Format ( _T("%s ( %s )"), LocalRadioInfo.RadioInfo.szName, m_BlueTooth.FormatBthAddress ( LocalRadioInfo.RadioInfo.address.rgBytes ) );
		pListBox->AddString ( csItemString );
	}
}

void CDlgBlueToothExc::OnBnClickedButtonRequestauthenticate()
{
	// 先确定本地蓝牙设备，如果还没有就查找
	t_LocalRadioInfo LocalRadioInfo;
	if ( !GetCur_LocalRadioInfo ( LocalRadioInfo ) ) return;

	// 当前选择的远程蓝牙设备
	int nSel = GetListCurSel ( IDC_LIST_NearbyBthDev, _T("Please select remote bluetooth device") );
	if ( nSel < 0  ) return;
	DWORD result = ERROR_SUCCESS;
	if ( !m_BlueTooth.RequestAuthenticateDevice ( nSel, GetSafeHwnd(), &result ) )
	{
		CString csMsg;
		csMsg.Format ( _T("Authenticate failed using passkey [%s] : %s"), AUTHENTICATION_PASSKEY, hwFormatMessage(result) );
		AfxMessageBox ( csMsg );
	}
}

BOOL CDlgBlueToothExc::GetCur_LocalRadioInfo(t_LocalRadioInfo& LocalRadioInfo)
{
	// 先确定本地蓝牙设备，如果还没有就查找
	CListBox *pListBox_LocalBluetoothRadios = (CListBox*)GetDlgItem ( IDC_LIST_LocalBluetoothRadios );
	ASSERT ( pListBox_LocalBluetoothRadios );
	int nSel_LocalBluetoothRadios = 0;
	if ( m_BlueTooth.m_Ary_LocalRadioInfo.GetSize() < 1 )
	{
		OnBnClickedButtonEnumerate ();
		if ( m_BlueTooth.m_Ary_LocalRadioInfo.GetSize() < 1 )
		{
			return FALSE;
		}
		pListBox_LocalBluetoothRadios->SetCurSel ( nSel_LocalBluetoothRadios );
	}

	nSel_LocalBluetoothRadios = pListBox_LocalBluetoothRadios->GetCurSel ();
	if ( nSel_LocalBluetoothRadios < 0 || nSel_LocalBluetoothRadios >= pListBox_LocalBluetoothRadios->GetCount() )
	{
		nSel_LocalBluetoothRadios = 0;
		pListBox_LocalBluetoothRadios->SetCurSel ( nSel_LocalBluetoothRadios );
	}
	ASSERT ( m_BlueTooth.m_Ary_LocalRadioInfo.GetSize() == pListBox_LocalBluetoothRadios->GetCount() );
	t_LocalRadioInfo& LocalRadioInfo_Ref = m_BlueTooth.m_Ary_LocalRadioInfo.GetAt(nSel_LocalBluetoothRadios);
	memcpy ( &LocalRadioInfo, &LocalRadioInfo_Ref, sizeof(t_LocalRadioInfo) );

	return TRUE;
}

int CDlgBlueToothExc::GetListCurSel(UINT nID, LPCTSTR lpszMsg)
{
	CListBox *pListBox = (CListBox*)GetDlgItem ( nID );
	if ( !pListBox ) return -1;
	int nSel = pListBox->GetCurSel ();
	if ( nSel < 0 || nSel >= pListBox->GetCount() )
	{
		if ( lpszMsg ) AfxMessageBox ( lpszMsg );
		return -1;
	}

	return nSel;
}

void CDlgBlueToothExc::OnDestroy()
{
	CDialog::OnDestroy();

	CDlgDataShow::DeleteInstance ();

	ExitCOMThread ();
	SAFE_CLOSE_HANDLE ( m_hEvtEndThread );
	SAFE_CLOSE_HANDLE ( m_hEvtSendDataReq );
	DeleteCOMObject ();
}

void CDlgBlueToothExc::DeleteCOMObject(void)
{
	if ( m_pHwCOM )
	{
		delete m_pHwCOM;
		m_pHwCOM = NULL;
	}
}

DWORD WINAPI ThreadProc_COM(
  LPVOID lpParameter   // thread data
)
{
	CDlgBlueToothExc *pDlgBlueToothExc = reinterpret_cast<CDlgBlueToothExc*>(lpParameter);
	if ( pDlgBlueToothExc )
		pDlgBlueToothExc->ThreadProc_COM ();
	return TRUE;
}

void CDlgBlueToothExc::OnBnClickedButtonConnect()
{
	CWaitCursor WaitCurSor;
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_COM);
	ASSERT ( pCombo );
	int nSel = pCombo->GetCurSel ();
	if ( nSel < 0 || nSel >= pCombo->GetCount () )
	{
		AfxMessageBox ( L"Please select COM" );
		return;
	}

	int nCOM = nSel + 1;
	int nBaudRate = (int)GetDlgItemInt ( IDC_EDIT_Baud, NULL, FALSE );
	DeleteCOMObject ();

	m_pHwCOM = new CHwCOM;
	if ( !m_pHwCOM ) return;
	if ( !m_pHwCOM->OpenCOM ( nCOM, nBaudRate, TRUE ) )
	{
		DeleteCOMObject ();
		CString csMsg;
		csMsg.Format ( L"Open COM%d failed : %s", nCOM, hwFormatMessage ( GetLastError() ) );
		AfxMessageBox ( csMsg );
		return;
	}
	m_pHwCOM->SetCommMask ( EV_RXCHAR );

	ExitCOMThread ();

	if ( !HANDLE_IS_VALID(m_hEvtEndThread) )
		m_hEvtEndThread = ::CreateEvent ( NULL, TRUE, FALSE, NULL );
	if ( !HANDLE_IS_VALID(m_hEvtSendDataReq) )
		m_hEvtSendDataReq = ::CreateEvent ( NULL, FALSE, FALSE, NULL );
	if ( !HANDLE_IS_VALID(m_hThread) )
		m_hThread = ::CreateThread ( NULL, 0, ::ThreadProc_COM, this, 0, &m_dwThreadID );
	if ( !HANDLE_IS_VALID(m_hThread) || !HANDLE_IS_VALID(m_hEvtEndThread) || !HANDLE_IS_VALID(m_hEvtSendDataReq) )
		return;

	GetDlgItem(IDC_BUTTON_Connect)->EnableWindow ( FALSE );
	EnableWindow_ConnCOM ( TRUE );
}

//
// 数据处理的线程
//
void CDlgBlueToothExc::ThreadProc_COM(void)
{
	HANDLE hAryEvt[] = { m_hEvtEndThread, m_hEvtSendDataReq };
	while ( TRUE )
	{
		DWORD dwRet = ::WaitForMultipleObjects ( LENGTH(hAryEvt), hAryEvt, FALSE, 100 ) - WAIT_OBJECT_0;
		// 请求线程终止
		if ( dwRet == 0 )
			return;
		// 发送数据到串口
		else if ( dwRet == 1 )
		{
			if ( m_pHwCOM )
			{
				m_CSFor_DataForSending.Lock();
				char DataForSending[MAX_COM_BUFSIZE] = {0};
				int nBytesForSending = m_nBytesForSending;
				memcpy ( DataForSending, m_DataForSending, nBytesForSending );
				memset ( m_DataForSending, 0, sizeof(m_DataForSending) );
				m_nBytesForSending = 0;
				m_CSFor_DataForSending.Unlock ();

				if ( m_pHwCOM->Write ( DataForSending, nBytesForSending ) != nBytesForSending )
				{
					AfxMessageBox ( _T("Send data failed") );
				}
			}
		}
		// 从串口读取数据
		else
		{
			ReadDataAndDisplay ();
		}
	}
}

void CDlgBlueToothExc::ExitCOMThread(void)
{
	if ( HANDLE_IS_VALID(m_hEvtEndThread) )
		::SetEvent ( m_hEvtEndThread );
	WaitForThreadEnd ( &m_hThread );
}

void CDlgBlueToothExc::OnBnClickedButtonDisconnect()
{
	ExitCOMThread ();
	DeleteCOMObject ();

	GetDlgItem(IDC_BUTTON_Connect)->EnableWindow ( TRUE );
	EnableWindow_ConnCOM ( FALSE );
}

void CDlgBlueToothExc::ReadDataAndDisplay(void)
{
	BYTE data[MAX_COM_BUFSIZE] = {0};
	if ( !m_pHwCOM ) return;
	DWORD dwEvtMask = 0;

	int nReadBytes = m_pHwCOM->Read ( (char*)data, sizeof(data)-1 );
	if ( nReadBytes > 0 )
	{
		// 将收到的数据保存到临时文件
		WriteDataToFile ( _T("c:\\bthdebug.dat"), (char*)data, nReadBytes, _T("ab+") );
		// 将数据显示成曲线
		if ( m_bShowCurve && nReadBytes > 20 )
		{
			CDlgDataShow *pDlgDataShow = CDlgDataShow::GetInstance ();
			if ( pDlgDataShow )
			{
				pDlgDataShow->DrawDataCurve ( data, nReadBytes );
			}
			m_bShowCurve = FALSE;
		}

		CEdit *pEdit_Hex = (CEdit*)GetDlgItem(IDC_EDIT_ReceivedData_Hex);
		ASSERT ( pEdit_Hex );
		if ( !m_bNoteBeCleared ) pEdit_Hex->SetWindowText ( _T("") );
		pEdit_Hex->SetSel ( -1, -1 );
		pEdit_Hex->ReplaceSel ( Data2HexString((char*)data,nReadBytes) );
		pEdit_Hex->SetSel ( -1, -1 );
		pEdit_Hex->ReplaceSel ( L"\r\n" );
		CalcAndShowDataLength ( IDC_EDIT_ReceivedData_Hex, IDC_STATIC_ReceivedData_Hex_Length, TRUE );

		CEdit *pEdit_String = (CEdit*)GetDlgItem(IDC_EDIT_ReceivedData_String);
		ASSERT ( pEdit_String );
		if ( !m_bNoteBeCleared ) pEdit_String->SetWindowText ( _T("") );
		pEdit_String->SetSel ( -1, -1 );
		data[nReadBytes] = '\0';
		CString csData;
#ifdef UNICODE
		WCHAR wchar[MAX_COM_BUFSIZE] = {0};	// UNICODE串缓冲区
		MultiByteToWideChar(CP_ACP, 0, (char*)data, nReadBytes, wchar, MAX_COM_BUFSIZE);
		csData.Format ( _T("%s"), wchar );
#else
		csData = (LPCTSTR)data;
#endif
		pEdit_String->ReplaceSel ( csData );
		pEdit_String->SetSel ( -1, -1 );
		pEdit_String->ReplaceSel ( L"\r\n" );

		m_bNoteBeCleared = TRUE;
	}
}

void CDlgBlueToothExc::OnBnClickedButtonSend()
{
	if ( !HANDLE_IS_VALID(m_hEvtSendDataReq) ) return;

	CString csData;
	GetDlgItemText ( IDC_SENDTEXT, csData );
	if ( csData.IsEmpty() ) return;

	if ( ( (CButton*)GetDlgItem(IDC_CHECK_Hex) )->GetCheck () )
	{
		m_nBytesForSending = ConvStringToHexData ( csData, (BYTE*)m_DataForSending, (int)sizeof(m_DataForSending) );
	}
	else
	{
#ifdef UNICODE
		m_nBytesForSending = WideCharToMultiByte ( CP_ACP, 0, csData, csData.GetLength(), (LPSTR)m_DataForSending, sizeof(m_DataForSending), NULL, NULL );
#else
		m_nBytesForSending = _sntprintf ( m_DataForSending, sizeof(m_DataForSending), "%s", csData );
#endif
	}

	SendData ( m_DataForSending, m_nBytesForSending );
}

void CDlgBlueToothExc::OnBnClickedButtonClearup()
{
	CEdit *pEdit_Hex = (CEdit*)GetDlgItem(IDC_EDIT_ReceivedData_Hex);
	ASSERT ( pEdit_Hex );
	pEdit_Hex->SetWindowText ( _T("") );
	
	CEdit *pEdit_String = (CEdit*)GetDlgItem(IDC_EDIT_ReceivedData_String);
	ASSERT ( pEdit_String );
	pEdit_String->SetWindowText ( _T("") );
	CalcAndShowDataLength ( IDC_EDIT_ReceivedData_Hex, IDC_STATIC_ReceivedData_Hex_Length, TRUE );
}

void CDlgBlueToothExc::CalcAndShowDataLength(UINT nEditID, UINT nStaticID, bool bHex)
{
	CString csData;
	GetDlgItemText ( nEditID, csData );
	csData.Trim ();
	csData.Replace ( _T("\r\n"), _T("") );
	csData.Replace ( _T("\r"), _T("") );
	csData.Replace ( _T("\n"), _T("") );

	int nLength = csData.GetLength ();

	if ( bHex )
	{
		nLength = (nLength+1)/3;
	}
	CString csLength;
	csLength.Format ( _T("%d byte(s)"), nLength );
	SetDlgItemText ( nStaticID, csLength );
}

void CDlgBlueToothExc::OnBnClickedButtonTest1()
{
	CDlgDataShow *pDlgDataShow = CDlgDataShow::GetInstance ();
//	static int nPos = 0;
//	nPos += 10;
//	pDlgDataShow->m_staticCurve.SetCurStartPos ( nPos );
	pDlgDataShow->m_staticCurve.Dynamic ( 200 );
}

void CDlgBlueToothExc::OnEnSetfocusSendtext()
{
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_SENDTEXT);
	ASSERT ( pEdit );
	pEdit->SetSel ( 0, -1 );
}

void CDlgBlueToothExc::OnBnClickedButtonReceive()
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_Segment);
	ASSERT ( pCombo );
	int nSegment = pCombo->GetCurSel ();

	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_Section);
	ASSERT ( pCombo );
	int nSection = pCombo->GetCurSel ();

	BYTE data[] = {0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x03,0xA3,0x00,0x01};
	data[LENGTH(data)-1] = nSegment*4+nSection+1;

	m_bShowCurve = TRUE;
	SendData ( data, LENGTH(data) );
}

BOOL CDlgBlueToothExc::SendData(BYTE* data, int size)
{
	if ( !data || size<1 ) return FALSE;

	m_CSFor_DataForSending.Lock ();
	m_nBytesForSending = size;
	memcpy ( m_DataForSending, data, size );
	m_CSFor_DataForSending.Unlock ();
	::SetEvent ( m_hEvtSendDataReq );
	return TRUE;
}

void CDlgBlueToothExc::OnBnClickedButtonFinished()
{
	BYTE data[] = {0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x01,0xA7};
	SendData ( data, LENGTH(data) );
}

void CDlgBlueToothExc::EnableWindow_ConnCOM(bool bEnable)
{
	GetDlgItem(IDC_BUTTON_Disconnect)->EnableWindow ( bEnable );
	GetDlgItem(IDC_BUTTON_Receive)->EnableWindow ( bEnable );
	GetDlgItem(IDC_CHECK_ReceivedOnTimer)->EnableWindow ( bEnable );
	GetDlgItem(IDC_BUTTON_Finished)->EnableWindow ( bEnable );
	GetDlgItem(IDC_COMBO_Segment)->EnableWindow ( bEnable );
	GetDlgItem(IDC_COMBO_Section)->EnableWindow ( bEnable );
	GetDlgItem(IDC_SENDTEXT)->EnableWindow ( bEnable );
	GetDlgItem(IDC_CHECK_Hex)->EnableWindow ( bEnable );
	GetDlgItem(IDC_BUTTON_Send)->EnableWindow ( bEnable );
}

//void CDlgBlueToothExc::OnLbnSelchangeListNearbybthdev()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}

void CDlgBlueToothExc::OnBnClickedCheckReceivedontimer()
{
	if ( ((CButton*)GetDlgItem(IDC_CHECK_ReceivedOnTimer))->GetCheck() )
	{
		SetTimer ( 1, 300, NULL );
	}
	else
	{
		KillTimer ( 1 );
	}
}

void CDlgBlueToothExc::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == 1 )
	{
		PostMessage ( WM_COMMAND, IDC_BUTTON_Receive );
	}

	CDialog::OnTimer(nIDEvent);
}
