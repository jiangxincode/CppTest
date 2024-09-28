// ElevatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Elevator.h"
#include "ElevatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////
int CElevatorDlg::doorlocation = 90;
bool CElevatorDlg::OC_flag = true;
UINT CElevatorDlg::currentStatus = 0;//停止
UINT CElevatorDlg::currentFloorNumber = 1;
bool CElevatorDlg::lift_moving = false;//电梯停止
UINT CElevatorDlg::upQueue[8] = { 0 };
UINT CElevatorDlg::downQueue[8] = { 0 };
UINT CElevatorDlg::targetQueue[8] = { 0 };
CWnd* CElevatorDlg::pWnddoor;
CWnd* CElevatorDlg::pWndlift;
bool CElevatorDlg::threadt_f = false;//线程已结束
bool CElevatorDlg::ocf = true;
CWinThread* CElevatorDlg::threadlift;
HANDLE CElevatorDlg::handle;

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

CElevatorDlg::CElevatorDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CElevatorDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CElevatorDlg)
    m_people = 0;
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CElevatorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CElevatorDlg)
    DDX_Control(pDX, IDC_COMBO_PEOPLE_IN, ComBoBoxPeopleIn);
    DDX_Control(pDX, IDC_COMBO_PEOPLE_OUT, ComBoBoxPeopleOut);
    DDX_Text(pDX, IDC_EDIT1, m_people);
    DDV_MinMaxUInt(pDX, m_people, 0, 13);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CElevatorDlg, CDialog)
    //{{AFX_MSG_MAP(CElevatorDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_1, On1)
    ON_BN_CLICKED(IDC_2, On2)
    ON_BN_CLICKED(IDC_3, On3)
    ON_BN_CLICKED(IDC_4, On4)
    ON_BN_CLICKED(IDC_5, On5)
    ON_BN_CLICKED(IDC_6, On6)
    ON_BN_CLICKED(IDC_7, On7)
    ON_BN_CLICKED(IDC_8, On8)
    ON_BN_CLICKED(IDC_DOWN_8, OnDown8)
    ON_BN_CLICKED(IDC_DOWN_7, OnDown7)
    ON_BN_CLICKED(IDC_DOWN_6, OnDown6)
    ON_BN_CLICKED(IDC_DOWN_5, OnDown5)
    ON_BN_CLICKED(IDC_DOWN_4, OnDown4)
    ON_BN_CLICKED(IDC_DOWN_3, OnDown3)
    ON_BN_CLICKED(IDC_DOWN_2, OnDown2)
    ON_BN_CLICKED(IDC_UP_7, OnUp7)
    ON_BN_CLICKED(IDC_UP_6, OnUp6)
    ON_BN_CLICKED(IDC_UP_5, OnUp5)
    ON_BN_CLICKED(IDC_UP_4, OnUp4)
    ON_BN_CLICKED(IDC_UP_3, OnUp3)
    ON_BN_CLICKED(IDC_UP_2, OnUp2)
    ON_BN_CLICKED(IDC_UP_1, OnUp1)
    ON_BN_CLICKED(IDC_open, OnOpen)
    ON_BN_CLICKED(IDC_close, Onclose)
    ON_CBN_SELCHANGE(IDC_COMBO_PEOPLE_OUT, OnPeopleOut)
    ON_CBN_SELCHANGE(IDC_COMBO_PEOPLE_IN, OnPeopleIn)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CElevatorDlg::OnInitDialog()
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
    SetTimer(1, 1, NULL);
    paint = TRUE;
    showingCurrentFloorNumber = 1;
    showingCurrentStatus = 1;
    ////////////////////////////////////////////////////////////////////
    people = 0;
    CString tem1 = "1";//初始楼层为1
    CString tem2 = "<";//初始化向上
    status.set(this, tem2.GetLength(), 90, 20, 0);
    status.showIcon(tem2);
    floorNumber.set(this, tem1.GetLength(), 110, 20, 0);

    floorNumber.showIcon(tem1);


    CBitmap Bitmap;
    HBITMAP hBitmap;
    CButton* pButton;
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
    pButton = (CButton*)GetDlgItem(IDC_DOWN_8);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////	
    Bitmap.LoadBitmap(IDB_xia);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_DOWN_7);
    pButton->SetBitmap(hBitmap);
    /////////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_xia);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_DOWN_6);
    pButton->SetBitmap(hBitmap);
    ///////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_xia);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_DOWN_5);
    pButton->SetBitmap(hBitmap);
    ///////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_xia);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_DOWN_4);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_xia);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_DOWN_3);
    pButton->SetBitmap(hBitmap);
    ///////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_xia);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_DOWN_2);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_1);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_2);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_3);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_4);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_5);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_6);
    pButton->SetBitmap(hBitmap);
    //////////////////////////////////////////////////////
    Bitmap.LoadBitmap(IDB_shang);
    hBitmap = (HBITMAP)Bitmap.Detach();
    pButton = (CButton*)GetDlgItem(IDC_UP_7);
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

void CElevatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CElevatorDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

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
    if (paint)
    {

        CWnd* pWnd = GetDlgItem(IDC_STATIC);
        CDC* pControlDC = pWnd->GetDC();
        pWnd->Invalidate();
        pWnd->UpdateWindow();
        pControlDC->SelectStockObject(WHITE_BRUSH);
        pControlDC->Rectangle(0, 0, 140, 320);

        CPen* pen;
        CPen newpen(PS_SOLID, 0, RGB(128, 128, 128));
        pen = pControlDC->SelectObject(&newpen);
        for (unsigned int x = 320 - currentFloorNumber * 40; x <= 320 - (currentFloorNumber - 1) * 40; x++)
        {
            pControlDC->MoveTo(2, x);
            pControlDC->LineTo(138, x);
        }
        //////////////////////////////////////////////////////
        pWnd = GetDlgItem(IDC_STATIC1);
        pControlDC = pWnd->GetDC();
        pWnd->Invalidate();
        pWnd->UpdateWindow();
        pControlDC->SelectStockObject(0);
        pControlDC->Rectangle(doorlocation, 0, 180 - doorlocation, 100);
        pControlDC->SelectStockObject(1);
        pControlDC->Rectangle(0, 0, doorlocation, 100);
        pControlDC->Rectangle(180 - doorlocation, 0, 180, 100);
        paint = false;
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CElevatorDlg::OnQueryDragIcon()
{
    return (HCURSOR)m_hIcon;
}

void CElevatorDlg::On1()
{
    OnInternal(1);
}

void CElevatorDlg::On2()
{
    OnInternal(2);
}

void CElevatorDlg::On3()
{
    OnInternal(3);
}

void CElevatorDlg::On4()
{
    OnInternal(4);
}

void CElevatorDlg::On5()
{
    OnInternal(5);
}

void CElevatorDlg::On6()
{
    OnInternal(6);
}

void CElevatorDlg::On7()
{
    OnInternal(7);
}

void CElevatorDlg::On8()
{
    OnInternal(8);
}

void CElevatorDlg::OnInternal(UINT targetFloorNumber)
{
    CElevatorDlg::insertqueue(targetFloorNumber, targetQueue);
    orderqueue_j(upQueue);
    pWndlift = GetDlgItem(IDC_STATIC);
    pWnddoor = GetDlgItem(IDC_STATIC1);

    if (targetFloorNumber != 1)
    {
        if (threadt_f == false)
        {
            threadlift = AfxBeginThread(AFX_THREADPROC(liftMove), pWndlift);
            threadt_f = true;
        }
    }
}

void CElevatorDlg::OnDown8()
{
    OnDownInternal(8);
}

void CElevatorDlg::OnDown7()
{
    OnDownInternal(7);
}

void CElevatorDlg::OnDown6()
{
    OnDownInternal(6);
}

void CElevatorDlg::OnDown5()
{
    OnDownInternal(5);
}

void CElevatorDlg::OnDown4()
{
    OnDownInternal(4);
}

void CElevatorDlg::OnDown3()
{
    OnDownInternal(3);
}

void CElevatorDlg::OnDown2()
{
    OnDownInternal(2);
}

void CElevatorDlg::OnDownInternal(UINT targetFloorNumber)
{
    CElevatorDlg::insertqueue(targetFloorNumber, downQueue);
    orderqueue_s(downQueue);
    pWndlift = GetDlgItem(IDC_STATIC);
    pWnddoor = GetDlgItem(IDC_STATIC1);
    if (threadt_f == false)
    {
        threadlift = AfxBeginThread(AFX_THREADPROC(liftMove), pWndlift);
        threadt_f = true;
    }
}

void CElevatorDlg::OnUp7()
{
    CElevatorDlg::OnUpInternal(7);
}

void CElevatorDlg::OnUp6()
{
    CElevatorDlg::OnUpInternal(6);
}

void CElevatorDlg::OnUp5()
{
    CElevatorDlg::OnUpInternal(5);
}

void CElevatorDlg::OnUp4()
{
    CElevatorDlg::OnUpInternal(4);
}

void CElevatorDlg::OnUp3()
{
    CElevatorDlg::OnUpInternal(3);
}

void CElevatorDlg::OnUp2()
{
    CElevatorDlg::OnUpInternal(2);
}

void CElevatorDlg::OnUp1()
{
    CElevatorDlg::OnUpInternal(1);
}

void CElevatorDlg::OnUpInternal(UINT targetFloorNumber)
{
    CElevatorDlg::insertqueue(targetFloorNumber, upQueue);
    orderqueue_j(upQueue);
    pWndlift = GetDlgItem(IDC_STATIC);
    pWnddoor = GetDlgItem(IDC_STATIC1);
    if (targetFloorNumber == 1)
    {
        AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnddoor);
    }
    else if(threadt_f == false)
    {
        threadlift = AfxBeginThread(AFX_THREADPROC(liftMove), pWndlift);
        threadt_f = true;
    }
}

void CElevatorDlg::OnOpen()
{
    if (lift_moving)
    {
        AfxMessageBox("电梯正在移动中，不能开门！");
    }
    else
    {
        if (people == 0)
        {
            AfxMessageBox("电梯中没人！");
        }
        else
        {
            ocf = false;
            OC_flag = true;
            CWnd* pWnd = GetDlgItem(IDC_STATIC1);
            AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnd);
        }
    }
}

void CElevatorDlg::Onclose()
{
    if (lift_moving)
    {
        AfxMessageBox("电梯正在移动中，不能关门！");
    }
    else
    {
        if (people == 0)
        {
            AfxMessageBox("电梯中没人！");
        }
        else
        {
            ocf = false;
            OC_flag = false;
            CWnd* pWnd = GetDlgItem(IDC_STATIC1);
            AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnd);
        }
    }
}

UINT CElevatorDlg::OpenCloseDoor(CWnd* pWnd)//开关们线程函数
{
    //		threadt_f=true;
    CClientDC pControlDC(pWnd);

    while (OC_flag && doorlocation >= 0)//开门
    {
        pControlDC.SelectStockObject(0);
        pControlDC.Rectangle(doorlocation, 0, 180 - doorlocation, 100);
        pControlDC.SelectStockObject(1);
        pControlDC.Rectangle(0, 0, doorlocation, 100);
        pControlDC.Rectangle(180 - doorlocation, 0, 180, 100);
        Sleep(20);
        doorlocation--;
    }
    if (ocf == true)
    {
        Sleep(2000);
    }
    OC_flag = false;
    while (!OC_flag && doorlocation <= 90)//关门
    {
        pControlDC.SelectStockObject(0);
        pControlDC.Rectangle(doorlocation, 0, 180 - doorlocation, 100);
        pControlDC.SelectStockObject(1);
        pControlDC.Rectangle(0, 0, doorlocation, 100);
        pControlDC.Rectangle(180 - doorlocation, 0, 180, 100);
        Sleep(20);
        doorlocation++;
    }

    ocf = true;
    OC_flag = true;
    ResumeThread(threadlift->m_hThread);
    //	AfxBeginThread(AFX_THREADPROC(liftMove),pWndlift);

    return 0;

}

UINT CElevatorDlg::liftMove(CWnd* pWnd)//电梯移动线程函数
{
    while (upQueue[0] != 0 || downQueue[0] != 0 || targetQueue[0] != 0)
    {
        if (currentStatus == 0)
        {
            if (upQueue[0] != 0)
            {
                if (upQueue[0] > currentFloorNumber)
                {
                    currentStatus = 1;
                }
                if (upQueue[0] < currentFloorNumber)
                {
                    currentStatus = 2;
                }
                if (upQueue[0] == currentFloorNumber)
                {
                    //AfxBeginThread(AFX_THREADPROC(OpenCloseDoor),pWnddoor);
                }

            }
            if (downQueue[0] != 0)
            {
                orderqueue_j(downQueue);
                if (downQueue[0] > currentFloorNumber)
                {
                    currentStatus = 1;
                }
                if (downQueue[0] < currentFloorNumber)
                {
                    currentStatus = 2;
                }
                if (downQueue[0] == currentFloorNumber)
                {
                    // AfxBeginThread(AFX_THREADPROC(OpenCloseDoor),pWnddoor);
                }
                orderqueue_s(downQueue);
            }
            if (targetQueue[0] != 0)
            {
                orderqueue_j(targetQueue);
                if (targetQueue[0] > currentFloorNumber)
                {
                    currentStatus = 1;
                }
                if (targetQueue[0] < currentFloorNumber)
                {
                    currentStatus = 2;
                }
                if (targetQueue[0] == currentFloorNumber)
                {
                    //AfxBeginThread(AFX_THREADPROC(OpenCloseDoor),pWnddoor);
                }
                orderqueue_s(targetQueue);
            }

        }
        if (currentStatus == 1)
        {

            orderqueue_j(downQueue);
            while (downQueue[0] > currentFloorNumber && currentFloorNumber >= upQueue[0] && currentFloorNumber >= targetQueue[0])
            {

                liftUp(currentFloorNumber, pWnd);//向上移动一层
                if (downQueue[0] == currentFloorNumber)
                {
                    AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnddoor);
                    deleteQueue(currentFloorNumber, downQueue);
                    orderqueue_j(downQueue);
                    currentStatus = 2;
                    SuspendThread(threadlift->m_hThread);
                }

            }
            orderqueue_s(downQueue);

            if (currentFloorNumber < upQueue[0] || currentFloorNumber < targetQueue[0])
            {
                liftUp(currentFloorNumber, pWnd);//向上移动一层
                //检查targetQueue和upQueue
                for (int i = 0; i <= 7; i++)
                {

                    if (currentFloorNumber == upQueue[i] || currentFloorNumber == targetQueue[i])
                    {
                        if (currentFloorNumber == upQueue[i])
                        {
                            deleteQueue(currentFloorNumber, upQueue);
                            orderqueue_j(upQueue);

                        }
                        if (currentFloorNumber == targetQueue[i])
                        {
                            deleteQueue(currentFloorNumber, targetQueue);
                            orderqueue_j(targetQueue);

                        }


                        AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnddoor);


                        if (upQueue[0] == 0 && targetQueue[0] == 0)
                        {
                            currentStatus = 0;


                        }



                        SuspendThread(threadlift->m_hThread);


                    }

                }
            }

        }
        /////////////////////////////////////////////////////////////////////////////////////////
        if (currentStatus == 2)
        {
            orderqueue_s(upQueue);
            while (upQueue[0] < currentFloorNumber && currentFloorNumber <= downQueue[0] && currentFloorNumber <= targetQueue[0])
            {

                liftDown(currentFloorNumber, pWnd);//向下移动一层
                if (upQueue[0] == currentFloorNumber)
                {
                    currentStatus = 1;
                    deleteQueue(currentFloorNumber, upQueue);
                    orderqueue_s(upQueue);
                    AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnddoor);
                    SuspendThread(threadlift->m_hThread);

                }

            }
            orderqueue_j(upQueue);

            if ((currentFloorNumber > downQueue[0] && downQueue[0] != 0) || (currentFloorNumber > targetQueue[0] && targetQueue[0] != 0))
            {
                liftDown(currentFloorNumber, pWnd);//向下移动一层
                //检查targetQueue和downQueue
                for (int i = 0; i <= 7; i++)
                {

                    if (currentFloorNumber == downQueue[i] || currentFloorNumber == targetQueue[i])
                    {
                        if (currentFloorNumber == downQueue[i])
                        {
                            deleteQueue(currentFloorNumber, downQueue);
                            orderqueue_s(downQueue);

                        }
                        if (currentFloorNumber == targetQueue[i])
                        {
                            deleteQueue(currentFloorNumber, targetQueue);
                            orderqueue_s(targetQueue);

                        }

                        AfxBeginThread(AFX_THREADPROC(OpenCloseDoor), pWnddoor);
                        //threaddoor->m_bAutoDelete=false;
                        if (downQueue[0] == 0 && targetQueue[0] == 0)
                        {
                            currentStatus = 0;

                        }
                        SuspendThread(threadlift->m_hThread);
                    }
                }
            }
        }
    }

    threadt_f = false;
    return 0;
}

void CElevatorDlg::insertqueue(UINT m, UINT queue[])
{
    for (int i = 0; i <= 7; i++)
    {
        if (queue[i] == m)
            return;

    }
    for (int i = 0; i <= 7; i++)
    {
        if (queue[i] == 0)
        {
            queue[i] = m;
            return;
        }
    }
}

void CElevatorDlg::deleteQueue(UINT m, UINT queue[])
{
    for (int i = 0; i <= 7; i++)
    {
        if (queue[i] == m)
        {
            queue[i] = 9;
            return;
        }

    }
}

void CElevatorDlg::orderqueue_s(UINT queue[])
{
    int que[8] = { 0 };
    int pos;
    unsigned int temp;
    for (int t = 0; t <= 7; t++)
    {
        if (queue[t] == 0)
        {
            queue[t] = 9;
        }

    }
    for (int t = 0; t <= 7; t++)
    {
        temp = queue[0];
        for (int l = 0; l <= 7; l++)
        {
            if (temp > queue[l])
            {
                temp = queue[l];
                pos = l;
            }
        }
        if (temp == queue[0])
        {
            que[t] = queue[0];
            queue[0] = 9;
        }
        else
        {
            que[t] = temp;
            queue[pos] = 9;
        }
    }

    for (int n = 0; n <= 7; n++)
    {
        queue[n] = que[n];
    }
    for (int p = 0; p <= 7; p++)
    {
        if (queue[p] == 9)
        {
            for (int w = p; w <= 7; w++)
            {
                queue[w] = 0;
            }
        }
    }

}

void CElevatorDlg::orderqueue_j(UINT queue[])
{
    int t = 0;
    int que[8] = { 0,0,0,0,0,0,0,0 };
    orderqueue_s(queue);

    for (int w = 7; w >= 0; w--)
    {
        if (queue[w] != 0)
        {
            que[t] = queue[w];
            t++;
        }
    }
    for (int n = 0; n <= 7; n++)
    {
        queue[n] = que[n];
    }
}

void CElevatorDlg::liftUp(UINT& floor, CWnd* pWnd)
{
    CClientDC pControlDC(pWnd);
    lift_moving = true;
    if (doorlocation >= 90 && floor < 8)
    {
        for (int x = 0; x <= 40; x++)
        {
            CPen* pen;

            CPen newpen(PS_SOLID, 0, RGB(128, 128, 128));
            pen = pControlDC.SelectObject(&newpen);
            pControlDC.MoveTo(2, 320 - 40 * floor - x);
            pControlDC.LineTo(138, 320 - 40 * floor - x);

            CPen new2pen(PS_SOLID, 1, RGB(255, 255, 255));
            pen = pControlDC.SelectObject(&new2pen);
            pControlDC.MoveTo(2, 320 - 40 * (floor - 1) - x);
            pControlDC.LineTo(138, 320 - 40 * (floor - 1) - x);
            Sleep(20);
        }
        floor++;
    }
    lift_moving = false;

}

void CElevatorDlg::liftDown(UINT& floor, CWnd* pWnd)
{
    CClientDC pControlDC(pWnd);
    lift_moving = true;
    if (doorlocation >= 90 && floor > 1)
    {
        for (int x = 0; x <= 40; x++)
        {
            CPen* pen;
            CPen newpen(PS_SOLID, 0, RGB(128, 128, 128));
            pen = pControlDC.SelectObject(&newpen);
            pControlDC.MoveTo(2, 320 - 40 * (floor - 1) + x);
            pControlDC.LineTo(138, 320 - 40 * (floor - 1) + x);

            CPen new2pen(PS_SOLID, 1, RGB(255, 255, 255));
            pen = pControlDC.SelectObject(&new2pen);
            pControlDC.MoveTo(2, 320 - 40 * floor + x);
            pControlDC.LineTo(138, 320 - 40 * floor + x);
            Sleep(20);
        }
        currentFloorNumber--;

    }
    lift_moving = false;

}

void CElevatorDlg::OnPeopleOut()
{
    int nindex = ComBoBoxPeopleOut.GetCurSel();
    CString peopleNumberString;
    ComBoBoxPeopleOut.GetLBText(nindex, peopleNumberString);
    UINT peopleNumber = atoi(peopleNumberString);
    if (people < peopleNumber)
    {
        AfxMessageBox("电梯中没有这么多人");
    }
    else
    {
        people -= peopleNumber;
    }
    m_people = people;
    UpdateData(false);

}

void CElevatorDlg::OnPeopleIn()
{
    int nindex = ComBoBoxPeopleIn.GetCurSel();
    CString peopleNumberString;
    ComBoBoxPeopleIn.GetLBText(nindex, peopleNumberString);
    UINT peopleNumber = atoi(peopleNumberString);
    if (people + peopleNumber > 13)
    {
        AfxMessageBox("本电梯只能装载13人");
    }
    else
    {
        people += peopleNumber;
    }
    m_people = people;
    UpdateData(false);
}

void CElevatorDlg::OnTimer(UINT_PTR nIDEvent)
{
    CString currentFloorNumberStr;
    CString currentStatusStr;
    currentFloorNumberStr.Format("%d", currentFloorNumber);

    if (showingCurrentFloorNumber != currentFloorNumber || showingCurrentStatus != currentStatus)
    {
        if (currentStatus == 1)
        {
            currentStatusStr = "<";
        }
        if (currentStatus == 2)
        {
            currentStatusStr = ">";
        }

        status.set(this, currentStatusStr.GetLength(), 90, 20, 0);
        status.showIcon(currentStatusStr);

        floorNumber.set(this, currentFloorNumberStr.GetLength(), 110, 20, 0);

        floorNumber.showIcon(currentFloorNumberStr);
        showingCurrentFloorNumber = currentFloorNumber;
        showingCurrentStatus = currentStatus;
    }
    CDialog::OnTimer(nIDEvent);
}
