// ditiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "diti.h"
#include "ditiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////
int CDitiDlg::doorlocation=90;
bool CDitiDlg::OC_flag=true;
UINT CDitiDlg::lift_updown = 0;//停止
UINT CDitiDlg::floorID = 1;
bool CDitiDlg::lift_moving = false;//电梯停止
UINT CDitiDlg::upqueue[8]={0};
UINT CDitiDlg::downqueue[8]={0};
UINT CDitiDlg::mudi[8]={0};
	CWnd* CDitiDlg::pWnddoor;
	CWnd* CDitiDlg::pWndlift;
bool CDitiDlg::threadt_f = false;//线程已结束
bool CDitiDlg::ocf=true;
CWinThread* CDitiDlg::threadlift;
HANDLE CDitiDlg::handle;
////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDitiDlg dialog

CDitiDlg::CDitiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDitiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDitiDlg)
	m_people = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDitiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDitiDlg)
	DDX_Control(pDX, IDC_COMBOjin, m_jindianti);
	DDX_Control(pDX, IDC_COMBOchu, m_chudianti);
	DDX_Text(pDX, IDC_EDIT1, m_people);
	DDV_MinMaxUInt(pDX, m_people, 0, 13);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDitiDlg, CDialog)
	//{{AFX_MSG_MAP(CDitiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_1, On1)
	ON_BN_CLICKED(IDC_8, On8)
	ON_BN_CLICKED(IDC_2, On2)
	ON_BN_CLICKED(IDC_3, On3)
	ON_BN_CLICKED(IDC_4, On4)
	ON_BN_CLICKED(IDC_5, On5)
	ON_BN_CLICKED(IDC_6, On6)
	ON_BN_CLICKED(IDC_7, On7)
	ON_BN_CLICKED(IDC_8xia, On8xia)
	ON_BN_CLICKED(IDC_7xia, On7xia)
	ON_BN_CLICKED(IDC_6xia, On6xia)
	ON_BN_CLICKED(IDC_5xia, On5xia)
	ON_BN_CLICKED(IDC_4xia, On4xia)
	ON_BN_CLICKED(IDC_3xia, On3xia)
	ON_BN_CLICKED(IDC_2xia, On2xia)
	ON_BN_CLICKED(IDC_7shang, On7shang)
	ON_BN_CLICKED(IDC_6shang, On6shang)
	ON_BN_CLICKED(IDC_5shang, On5shang)
	ON_BN_CLICKED(IDC_4shang, On4shang)
	ON_BN_CLICKED(IDC_3shang, On3shang)
	ON_BN_CLICKED(IDC_2shang, On2shang)
	ON_BN_CLICKED(IDC_1shang, On1shang)
	ON_BN_CLICKED(IDC_open, Onopen)
	ON_BN_CLICKED(IDC_close, Onclose)
	ON_CBN_SELCHANGE(IDC_COMBOchu, OnSelchangeCOMBOchu)
	ON_CBN_SELCHANGE(IDC_COMBOjin, OnSelchangeCOMBOjin)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDitiDlg message handlers

BOOL CDitiDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//////////////////////////////////////////////////////////////////
	SetTimer (1,1,NULL);
	paint=TRUE;
	showf=1;
	showzt=1;
////////////////////////////////////////////////////////////////////
	people=0;
	CString tem1="1";//初始楼层为1
	CString tem2="<";//初始化向上
	m_zhuangtai.set(this,tem2.GetLength(),90,20,0);
	m_zhuangtai.showicon(tem2);
	loucheng.set(this,tem1.GetLength(),110,20,0);

    loucheng.showicon(tem1);


	CBitmap Bitmap;
	HBITMAP hBitmap;
	CButton *pButton;
/////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_1);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_1);
	pButton->SetBitmap(hBitmap);
/////////////////////////////////////// 
	Bitmap.LoadBitmap(IDB_2);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_2);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_3);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_3);
	pButton->SetBitmap(hBitmap);
////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_4);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_4);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_5);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_5);
	pButton->SetBitmap(hBitmap);
////////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_6);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_6);
	pButton->SetBitmap(hBitmap);
///////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_7);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_7);
	pButton->SetBitmap(hBitmap);
/////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_8);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_8);
	pButton->SetBitmap(hBitmap);
////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_8xia);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////////////	
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_7xia);
	pButton->SetBitmap(hBitmap);
/////////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_6xia);
	pButton->SetBitmap(hBitmap);
///////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_5xia);
	pButton->SetBitmap(hBitmap);
///////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_4xia);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_3xia);
	pButton->SetBitmap(hBitmap);
///////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_xia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_2xia);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_1shang);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_2shang);
	pButton->SetBitmap(hBitmap);
//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_3shang);
	pButton->SetBitmap(hBitmap);
	//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_4shang);
	pButton->SetBitmap(hBitmap);
	//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_5shang);
	pButton->SetBitmap(hBitmap);
	//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_6shang);
	pButton->SetBitmap(hBitmap);
	//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_shang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_7shang);
	pButton->SetBitmap(hBitmap);
	//////////////////////////////////////////////////////
	Bitmap.LoadBitmap(IDB_open);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_open);
	pButton->SetBitmap(hBitmap);
///////////////////////////////////////////////////////////
	//Bitmap.LoadBitmap(IDB_close);
	Bitmap.LoadBitmap(IDB_close);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_close);
	pButton->SetBitmap(hBitmap);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDitiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDitiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
	/////////////////////////////////////////////
	if(paint)
	{
		
		CWnd *pWnd=GetDlgItem(IDC_STATIC);
		CDC *pControlDC=pWnd->GetDC();
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		pControlDC->SelectStockObject(WHITE_BRUSH);
		pControlDC->Rectangle(0,0,140,320);
		
		CPen *pen;
		CPen newpen(PS_SOLID,0,RGB(128,128,128));
		pen=pControlDC->SelectObject(&newpen);
		for(unsigned int x=320-floorID*40;x<=320-(floorID-1)*40;x++)
		{
			pControlDC->MoveTo(2,x);
			pControlDC->LineTo(138,x);
		}
		//////////////////////////////////////////////////////
		pWnd=GetDlgItem(IDC_STATIC1);
		pControlDC=pWnd->GetDC();
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		pControlDC->SelectStockObject(0);
		pControlDC->Rectangle(doorlocation,0,180-doorlocation,100);
		pControlDC->SelectStockObject(1);
		pControlDC->Rectangle(0,0,doorlocation,100);
		pControlDC->Rectangle(180-doorlocation,0,180,100);
		paint=false;
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDitiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDitiDlg::On1() 
{

/*
	Bitmap.LoadBitmap(IDB_1an);
	hBitmap = (HBITMAP)Bitmap.Detach();
	CButton *pButton = (CButton*)GetDlgItem(IDC_1);
	pButton->SetBitmap(hBitmap);	*/
 
	CDitiDlg::insertqueue(1,mudi);
	orderqueue_j(upqueue);
	

////////////////////////////////////////////////





}

void CDitiDlg::On8() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_8an);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_8);
	pButton->SetBitmap(hBitmap);*/
	// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(8,mudi);
			orderqueue_j(upqueue);

	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On2() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_2an);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_2);
	pButton->SetBitmap(hBitmap);	// TODO: Add your control notification handler code here*/

	CDitiDlg::insertqueue(2,mudi);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On3() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_3an);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_3);
		pButton->SetBitmap(hBitmap);*/
		// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(3,mudi);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On4() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_4an);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_4);
		pButton->SetBitmap(hBitmap);*/
		// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(4,mudi);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On5() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_5an);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_5);
	pButton->SetBitmap(hBitmap);*/
	// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(5,mudi);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On6() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_6an);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_6);
		pButton->SetBitmap(hBitmap);*/
		// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(6,mudi);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On7() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_7an);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_7);
	pButton->SetBitmap(hBitmap);*/
	// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(7,mudi);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}

}

void CDitiDlg::On8xia() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anxia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_8xia);
	pButton->SetBitmap(hBitmap);*/

	CDitiDlg::insertqueue(8,downqueue);
			orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);

	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On7xia() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anxia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_7xia);
	pButton->SetBitmap(hBitmap);	*/
// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(7,downqueue);
		CDitiDlg::orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
	threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On6xia() 
{
/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anxia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_6xia);
	pButton->SetBitmap(hBitmap);*/
	// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(6,downqueue);
				orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On5xia() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anxia);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_5xia);
	pButton->SetBitmap(hBitmap);	*/
// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(5,downqueue);
				orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On4xia() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_anxia);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_4xia);
		pButton->SetBitmap(hBitmap);*/
		// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(4,downqueue);
				orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On3xia() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_anxia);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_3xia);
		pButton->SetBitmap(hBitmap);*/
		// TODO: Add your control notification handler code here
	CDitiDlg::insertqueue(3,downqueue);
	CDitiDlg::orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On2xia() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_anxia);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_2xia);
		pButton->SetBitmap(hBitmap);	// TODO: Add your control notification handler code here*/
	
		CDitiDlg::insertqueue(2,downqueue);
		orderqueue_s(downqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On7shang() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anshang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_7shang);
	pButton->SetBitmap(hBitmap);*/
	// TODO: Add your control notification handler code here
		CDitiDlg::insertqueue(7,upqueue);
		orderqueue_j(upqueue);
		
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
	threadlift=	AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On6shang() 
{
/*

	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anshang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_6shang);
	pButton->SetBitmap(hBitmap);	*/
// TODO: Add your control notification handler code here
			CDitiDlg::insertqueue(6,upqueue);
			orderqueue_j(upqueue);
			
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On5shang() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_anshang);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_5shang);
		pButton->SetBitmap(hBitmap);*/
		// TODO: Add your control notification handler code here
			CDitiDlg::insertqueue(5,upqueue);
			orderqueue_j(upqueue);
			
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On4shang() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anshang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_4shang);
	pButton->SetBitmap(hBitmap);*/
	// TODO: Add your control notification handler code here
			CDitiDlg::insertqueue(4,upqueue);
			orderqueue_j(upqueue);
			
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On3shang() 
{

	/*
	CButton *pButton;
		Bitmap.LoadBitmap(IDB_anshang);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_3shang);
		pButton->SetBitmap(hBitmap);	*/
	// TODO: Add your control notification handler code here
	insertqueue(3,upqueue);
	orderqueue_j(upqueue);
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{
		threadlift=AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On2shang() 
{

/*
	CButton *pButton;
	Bitmap.LoadBitmap(IDB_anshang);
	hBitmap = (HBITMAP)Bitmap.Detach();
	pButton = (CButton*)GetDlgItem(IDC_2shang);
	pButton->SetBitmap(hBitmap);	*/

	CDitiDlg::insertqueue(2,upqueue);
	orderqueue_j(upqueue);
	
	pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	if(threadt_f==false)
	{


		threadlift = AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);
		threadt_f=true;
	}
}

void CDitiDlg::On1shang() 
{

/*
		CButton *pButton;
		Bitmap.LoadBitmap(IDB_anshang);
		hBitmap = (HBITMAP)Bitmap.Detach();
		pButton = (CButton*)GetDlgItem(IDC_1shang);
		pButton->SetBitmap(hBitmap);*/
		
	CDitiDlg::insertqueue(1,upqueue);
	orderqueue_j(upqueue);
		pWndlift=GetDlgItem(IDC_STATIC)	;	
	pWnddoor=GetDlgItem(IDC_STATIC1);
	AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);

}

void CDitiDlg::Onopen() 
{
   	if(lift_moving)
	{
		AfxMessageBox("电梯正在移动中，不能开门！");
		
	}

	
	else
	{
		if (people==0) 
		{
			AfxMessageBox("电梯中没人！");
		}
		else
		{
		
		ocf=false;
		
		OC_flag=true;
		CWnd *pWnd=GetDlgItem(IDC_STATIC1);
		AfxBeginThread(AFX_THREADPROC(OCdoor),pWnd);
		}
	}
}

void CDitiDlg::Onclose() 
{




	if(lift_moving)
	{
		AfxMessageBox("电梯正在移动中，不能关门！");
		
	}
	
	
	else
	{
		if (people==0) 
		{
			AfxMessageBox("电梯中没人！");
		}
		else
		{
			
			ocf=false;
			OC_flag=false;
			CWnd *pWnd=GetDlgItem(IDC_STATIC1);
			AfxBeginThread(AFX_THREADPROC(OCdoor),pWnd);
		}
	}
	


}

UINT CDitiDlg::OCdoor(CWnd *pWnd)//开关们线程函数
{
	//		threadt_f=true;
		CClientDC pControlDC(pWnd);

		while (OC_flag&&doorlocation>=0)//开门
		{

			
			pControlDC.SelectStockObject(0);
			pControlDC.Rectangle(doorlocation,0,180-doorlocation,100);
			pControlDC.SelectStockObject(1);
			pControlDC.Rectangle(0,0,doorlocation,100);
			pControlDC.Rectangle(180-doorlocation,0,180,100);
			Sleep(20);
			doorlocation--;
		}
		if(ocf==true)
		{
			Sleep(2000);
		}
		OC_flag=false;
		while (!OC_flag&&doorlocation<=90)//关门
		{
			
			pControlDC.SelectStockObject(0);
			pControlDC.Rectangle(doorlocation,0,180-doorlocation,100);
			pControlDC.SelectStockObject(1);
			pControlDC.Rectangle(0,0,doorlocation,100);
			pControlDC.Rectangle(180-doorlocation,0,180,100);
			Sleep(20);
			doorlocation++;
		}
		

		ocf=true;
		OC_flag=true;
		ResumeThread(threadlift->m_hThread);
	//	AfxBeginThread(AFX_THREADPROC(liftmove),pWndlift);

        return 0;

}

UINT CDitiDlg::liftmove(CWnd *pWnd)//电梯移动线程函数
{

	while (upqueue[0]!=0||downqueue[0]!=0||mudi[0]!=0)
	{
	   if(lift_updown==0)
	   {
		   if (upqueue[0]!=0) 
		   {
			   if (upqueue[0]>floorID) 
			   {
				   lift_updown=1;
			   }
			   if (upqueue[0]<floorID) 
			   {
				   lift_updown=2;
			   }
			   if (upqueue[0]==floorID) 
			   {
				   //AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
			   }
			   
		   }
		   if(downqueue[0]!=0)
		   {
			   orderqueue_j(downqueue);
			   if (downqueue[0]>floorID) 
			   {
				   lift_updown=1;
			   }
			   if (downqueue[0]<floorID) 
			   {
				   lift_updown=2;
			   }
			   if (downqueue[0]==floorID) 
			   {
				  // AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
			   }
			   orderqueue_s(downqueue);
		   }
		   if(mudi[0]!=0)
		   {
			   orderqueue_j(mudi);
			   if (mudi[0]>floorID) 
			   {
				   lift_updown=1;
			   }
			   if (mudi[0]<floorID) 
			   {
				   lift_updown=2;
			   }
			   if (mudi[0]==floorID) 
			   {
				   //AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
			   }
			   orderqueue_s(mudi);
		   }
		   
	   }
	   if (lift_updown==1)
	   {
		   
		   orderqueue_j(downqueue);
		   		   while(downqueue[0]>floorID&&floorID>=upqueue[0]&&floorID>=mudi[0])
		   		   {
		   			
		   				   liftup(floorID,pWnd);//向上移动一层
							if (downqueue[0]==floorID) 
							{
								AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
								deletequeue(floorID,downqueue);
								orderqueue_j(downqueue);
								lift_updown=2;
								SuspendThread(threadlift->m_hThread);
							}
		   		
		   		   }
		   		orderqueue_s(downqueue);
		   
		  if(floorID<upqueue[0]||floorID<mudi[0])
		  {
			  liftup(floorID,pWnd);//向上移动一层
			  //检查mudi队列和向上队列
			  for(int i=0;i<=7;i++)
			  {
				  
				  if(floorID==upqueue[i]||floorID==mudi[i])
				  {
					  if(floorID==upqueue[i])
					  {
						  deletequeue(floorID,upqueue);
						  orderqueue_j(upqueue);
						 
					  }
					  if(floorID==mudi[i])
					  {
						  deletequeue(floorID,mudi);
						  orderqueue_j(mudi);
						  
					  }
					  
					  
					  AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
		
					  
					  if(upqueue[0]==0&&mudi[0]==0)
					  {
						  lift_updown=0;
						   
						  
					  }
					 
					 
				
					  SuspendThread(threadlift->m_hThread);
					  
			
				  }
				  
			  }
		  }
	   
	   }
/////////////////////////////////////////////////////////////////////////////////////////
	   if (lift_updown==2)
	   {
		   orderqueue_s(upqueue);
		   while(upqueue[0]<floorID&&floorID<=downqueue[0]&&floorID<=mudi[0])
		   {
			   
			   liftdown(floorID,pWnd);//向下移动一层
			   if (upqueue[0]==floorID) 
			   {
				   lift_updown=1;
				   deletequeue(floorID,upqueue);
				   orderqueue_s(upqueue);
				   AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
				   SuspendThread(threadlift->m_hThread);
				   
			   }
			   
		   }
		   orderqueue_j(upqueue);


		   if((floorID>downqueue[0]&&downqueue[0]!=0)||(floorID>mudi[0]&&mudi[0]!=0))
		   {
			   liftdown(floorID,pWnd);//向下移动一层
			   //检查mudi队列和向下队列
			   for(int i=0;i<=7;i++)
			   {
				   
				   if(floorID==downqueue[i]||floorID==mudi[i])
				   {
					   if(floorID==downqueue[i])
					   {
						   deletequeue(floorID,downqueue);
						   orderqueue_s(downqueue);
						   
					   }
					   if(floorID==mudi[i])
					   {
						   deletequeue(floorID,mudi);
						   orderqueue_s(mudi);
						   
					   }
					   
					   
					   
					  
					    AfxBeginThread(AFX_THREADPROC(OCdoor),pWnddoor);
					   //threaddoor->m_bAutoDelete=false;
					   if(downqueue[0]==0&&mudi[0]==0)
					   {
						   lift_updown=0;
	   
					   }
					  
					   
					   SuspendThread(threadlift->m_hThread);
	   
				   }
				   
			   }
		   }


	   }
 
/////////////////////////////////////////////////////////////////////////////
	
	}

	threadt_f=false;
	return 0;
}

void CDitiDlg::insertqueue(UINT m, UINT queue[])
{
	for(int i=0;i<=7;i++)
	{
		if(queue[i]==m)
			return;
	
	}
	for(int i=0;i<=7;i++)
	{
		if(queue[i]==0)
		{
			queue[i]=m;
			return;
		}

	}



}

void CDitiDlg::deletequeue(UINT m, UINT queue[])
{
		for(int i=0;i<=7;i++)
	{
		if(queue[i]==m)
		{
			queue[i]=9;
			return;
		}
	
	}


}

void CDitiDlg::orderqueue_s(UINT queue[])
{
	int que[8]={0};
	int pos;
	unsigned int temp;
	for(int t=0;t<=7;t++)
    {
		if(queue[t]==0)
		{
			queue[t]=9;
		}

	}
	for(int t=0;t<=7;t++)
    {
	    temp=queue[0];
		for(int l=0;l<=7;l++)
		{
			if(temp>queue[l])
			{
				temp=queue[l];
				pos=l;
			}	
		}
		if(temp==queue[0])
		{
			que[t]=queue[0];
			queue[0]=9;
		}
		else
		{
			que[t]=temp;
			queue[pos]=9;
		}
	}

	for(int n=0;n<=7;n++)
    {
		queue[n]=que[n];
	}
	for(int p=0;p<=7;p++)
    {
		if(queue[p]==9)
		{
			for(int w=p;w<=7;w++)
			{queue[w]=0;}
		}
	}

}

void CDitiDlg::orderqueue_j(UINT queue[])
{
	int t=0;
	int que[8]={0,0,0,0,0,0,0,0};
	orderqueue_s(queue);

	for(int w=7;w>=0;w--)
	{
		if(queue[w]!=0)
		{
			que[t]=queue[w];
			t++;
		}
	}
	for(int n=0;n<=7;n++)
    {
		queue[n]=que[n];
	}

}

void CDitiDlg::liftup(UINT &floor,CWnd *pWnd)
{
	CClientDC pControlDC(pWnd);	
	lift_moving=true;
	if(doorlocation>=90&&floor<8)
	{
		
		for(int x=0;x<=40;x++)
		{
			CPen *pen;
			
			CPen newpen(PS_SOLID,0,RGB(128,128,128));
			pen=pControlDC.SelectObject(&newpen);
			pControlDC.MoveTo(2,320-40*floor-x);
			pControlDC.LineTo(138,320-40*floor-x);
			
			CPen new2pen(PS_SOLID,1,RGB(255,255,255));
			pen=pControlDC.SelectObject(&new2pen);
			pControlDC.MoveTo(2,320-40*(floor-1)-x);
			pControlDC.LineTo(138,320-40*(floor-1)-x);	
			Sleep(20);
		}	
		floor++;
	
	}
		lift_moving=false;

}

void CDitiDlg::liftdown(UINT &floor,CWnd *pWnd)
{
	CClientDC pControlDC(pWnd);	
	lift_moving=true;
	if(doorlocation>=90&&floor>1)
	{
		for(int x=0;x<=40;x++)
		{
			
			CPen *pen;
			
			CPen newpen(PS_SOLID,0,RGB(128,128,128));
			pen=pControlDC.SelectObject(&newpen);
			pControlDC.MoveTo(2,320-40*(floor-1)+x);
			pControlDC.LineTo(138,320-40*(floor-1)+x);
			
			CPen new2pen(PS_SOLID,1,RGB(255,255,255));
			pen=pControlDC.SelectObject(&new2pen);
			pControlDC.MoveTo(2,320-40*floor+x);
			pControlDC.LineTo(138,320-40*floor+x);	
			Sleep(20);
		}	
		floorID--;

	}
	lift_moving=false;

}

void CDitiDlg::OnSelchangeCOMBOchu() 
{
	// TODO: Add your control notification handler code here
	int nindex=m_chudianti.GetCurSel();
	CString chunum;
	m_chudianti.GetLBText(nindex,chunum);
	switch (atoi(chunum))
	{
	
	case 1: 
		if(people<1) 
		{
			AfxMessageBox("电梯中没有这么多人");
		}
		else{	  people=people-1;}
		break;
	case 2:if(people<2) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-2;}
		break;
	case 3:if(people<3) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-3;}
		break;
	case 4:if(people<4) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-4;}
		break;
	case 5:if(people<5) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-5;}
		break;
	case 6:if(people<6) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-6;}
		break;
	case 7:if(people<7) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-7;}
		break;
	case 8:if(people<8) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-8;}
		break;
	case 9:if(people<9) 
			 {
				 AfxMessageBox("电梯中没有这么多人");
			 }
		else{	  people=people-9;}
		break;
	case 10:if(people<10) 
			  {
				  AfxMessageBox("电梯中没有这么多人");
			  }
		else{	  people=people-10;}
		break;
	case 11:if(people<11) 
			  {
				  AfxMessageBox("电梯中没有这么多人");
			  }
		else{	  people=people-11;}
		break;
	case 12:if(people<12) 
			  {
				  AfxMessageBox("电梯中没有这么多人");
			  }
		else{	  people=people-12;}
		break;
	case 13:if(people<13) 
			  {
				  AfxMessageBox("电梯中没有这么多人");
			  }
		else{	  people=people-13;}
		break;
	default:
		break;
	}
	m_people=people;
	UpdateData(false);
	
}

void CDitiDlg::OnSelchangeCOMBOjin() 
{
	// TODO: Add your control notification handler code here
	int nindex=m_jindianti.GetCurSel();
	CString chunum;
	m_jindianti.GetLBText(nindex,chunum);
	switch (atoi(chunum))
	{
		
	case 1: 
		if(people+1>13) 
		{
			AfxMessageBox("本电梯只能装载13人");
		}
		else{	  people=people+1;}
		break;
	case 2:if(people+2>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+2;}
		break;
	case 3:if(people+3>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+3;}
		break;
	case 4:if(people+4>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+4;}
		break;
	case 5:if(people+5>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+5;}
		break;
	case 6:if(people+6>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+6;}
		break;
	case 7:if(people+7>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+7;}
		break;
	case 8:if(people+8>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+8;}
		break;
	case 9:if(people+9>13) 
			 {
				 AfxMessageBox("本电梯只能装载13人");
			 }
		else{	  people=people+9;}
		break;
	case 10:if(people+10>13) 
			  {
				  AfxMessageBox("本电梯只能装载13人");
			  }
		else{	  people=people+10;}
		break;
	case 11:if(people+11>13) 
			  {
				  AfxMessageBox("本电梯只能装载13人");
			  }
		else{	  people=people+11;}
		break;
	case 12:if(people+12>13) 
			  {
				  AfxMessageBox("本电梯只能装载13人");
			  }
		else{	  people=people+12;}
		break;
	case 13:if(people+13>13) 
			  {
				  AfxMessageBox("本电梯只能装载13人");
			  }
		else{	  people=people+13;}
		break;
	default:
		break;
	}
	m_people=people;
	UpdateData(false);
	
	
}

void CDitiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	loucengshow.Format("%d",floorID);

	if(showf!=floorID||showzt!=lift_updown)
	{		
		if(lift_updown==1)
		{
			zhuangtaishow="<";
		}
		if(lift_updown==2)
		{
			zhuangtaishow=">";
		}
	
		m_zhuangtai.set(this,zhuangtaishow.GetLength(),90,20,0);
		m_zhuangtai.showicon(zhuangtaishow);
	

		loucheng.set(this,loucengshow.GetLength(),110,20,0);
		
		loucheng.showicon(loucengshow);
		showf=floorID;
		showzt=lift_updown;
	}
	CDialog::OnTimer(nIDEvent);
}










































