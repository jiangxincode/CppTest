
// RadioButtonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RadioButton.h"
#include "RadioButtonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRadioButtonDlg 对话框




CRadioButtonDlg::CRadioButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRadioButtonDlg::IDD, pParent)
	, m_spring(FALSE)
	, m_fl1(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRadioButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_SPRING, m_spring);
	DDX_Radio(pDX, IDC_RADIO_FL1, m_fl1);
}

BEGIN_MESSAGE_MAP(CRadioButtonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRadioButtonDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRadioButtonDlg 消息处理程序

BOOL CRadioButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRadioButtonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRadioButtonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRadioButtonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRadioButtonDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strMessage;
	CString str_spring;
	CString str_flower;

	//从对话框的控件中得到数据，并且更新与它们相连的变量
	UpdateData();

	//得到角色类型组中被选中的单选按钮的标题
	GetDlgItem(IDC_RADIO_SPRING+m_spring)->GetWindowText(str_spring);
	//得到人员类型组中被选中的单选按钮的标题
	GetDlgItem(IDC_RADIO_FL1+m_fl1)->GetWindowText(str_flower);

	//组织选中按钮的文字以得到要显示的消息
	strMessage=str_flower+L"是"+str_spring+L"的代表";

	//获得复选框控件的指针
	CButton* pSmell=(CButton*)GetDlgItem(IDC_CHECK_SMELL);
	CButton* pWatch=(CButton*)GetDlgItem(IDC_CHECK_WATCH);

	//获得复选框是否选中，并做出相应处理
	if(pSmell->GetCheck()&&!pWatch->GetCheck())
	{
		strMessage+="，香气宜人";
	}
	if(pWatch->GetCheck()&&!pSmell->GetCheck())
	{
		strMessage+="，美丽大方";
	}
	if(pSmell->GetCheck()&&pWatch->GetCheck())
	{
		strMessage+="，不但香气宜人，而且美丽大方";
	}


	MessageBox(strMessage);

	CDialogEx::OnOK();
}
