// DlgDataShow.cpp : 实现文件
//

#include "stdafx.h"
#include "BlueToothExc.h"
#include "DlgDataShow.h"

CDlgDataShow *CDlgDataShow::m_pDlg = NULL;

// CDlgDataShow 对话框

IMPLEMENT_DYNAMIC(CDlgDataShow, CDialog)

CDlgDataShow::CDlgDataShow(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDataShow::IDD, pParent)
{

}

CDlgDataShow::~CDlgDataShow()
{
}

void CDlgDataShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Curve, m_staticCurve);
	DDX_Control(pDX, IDC_SLIDER_StartPos, m_SliderGraph);
}


BEGIN_MESSAGE_MAP(CDlgDataShow, CDialog)
//	ON_WM_PAINT()
ON_WM_SIZE()
ON_WM_GETMINMAXINFO()
ON_BN_CLICKED(IDC_CHECK_Dynamic, &CDlgDataShow::OnBnClickedButtonDynamic)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Step, &CDlgDataShow::OnDeltaposSpinStep)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Interval, &CDlgDataShow::OnDeltaposSpinInterval)
ON_EN_CHANGE(IDC_EDIT_Step, &CDlgDataShow::OnEnChangeEditStep)
ON_EN_CHANGE(IDC_EDIT_Interval, &CDlgDataShow::OnEnChangeEditInterval)
ON_BN_CLICKED(IDC_BUTTON_Zoomin, &CDlgDataShow::OnBnClickedButtonZoomin)
ON_BN_CLICKED(IDC_BUTTON_Zoomout, &CDlgDataShow::OnBnClickedButtonZoomout)
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_BUTTON_FromFile, &CDlgDataShow::OnBnClickedButtonFromfile)
END_MESSAGE_MAP()


// CDlgDataShow 消息处理程序

BOOL CDlgDataShow::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemInt ( IDC_EDIT_Step, m_staticCurve.GetDynamicStep(), FALSE );
	SetDlgItemInt ( IDC_EDIT_Interval, 300, FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CDlgDataShow* CDlgDataShow::GetInstance(void)
{
	if ( m_pDlg ) return m_pDlg;
	m_pDlg = ::TGetInstance ( &m_pDlg, CDlgDataShow::IDD, CWnd::GetDesktopWindow() );
	return m_pDlg;
}

void CDlgDataShow::DeleteInstance(void)
{
	::DeleteInstance ( (CWnd**)&m_pDlg );
}

void CDlgDataShow::OnCancel(void)
{
}

void CDlgDataShow::OnClose(void)
{
}

void CDlgDataShow::OnOK(void)
{
}

void CDlgDataShow::Align(void)
{
	if ( !IsWindow(m_hWnd) || !GetDlgItem(IDC_STATIC_Curve) )
		return;

	CRect rcClient, rcCtrl;
	GetClientRect ( &rcClient );

	CRect rcIDC_BUTTON_Zoomout;
	GetDlgItem(IDC_BUTTON_Zoomout)->GetWindowRect ( &rcCtrl );
	rcIDC_BUTTON_Zoomout.right = rcClient.right-4;
	rcIDC_BUTTON_Zoomout.left = rcIDC_BUTTON_Zoomout.right - rcCtrl.Width();
	rcIDC_BUTTON_Zoomout.bottom = rcClient.bottom - 4;
	rcIDC_BUTTON_Zoomout.top = rcIDC_BUTTON_Zoomout.bottom - rcCtrl.Height();
	GetDlgItem(IDC_BUTTON_Zoomout)->MoveWindow ( rcIDC_BUTTON_Zoomout );

	CRect rcIDC_BUTTON_Zoomin = rcIDC_BUTTON_Zoomout;
	rcIDC_BUTTON_Zoomin.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_BUTTON_Zoomin)->MoveWindow ( rcIDC_BUTTON_Zoomin );

	CRect rcIDC_STATIC_Zoom = rcIDC_BUTTON_Zoomin;
	GetDlgItem(IDC_STATIC_Zoom)->GetWindowRect ( &rcCtrl );
	rcIDC_STATIC_Zoom.right = rcIDC_STATIC_Zoom.left + rcCtrl.Width ();
	rcIDC_STATIC_Zoom.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_STATIC_Zoom)->MoveWindow ( rcIDC_STATIC_Zoom );

	CRect rcIDC_SPIN_Interval = rcIDC_STATIC_Zoom;
	GetDlgItem(IDC_SPIN_Interval)->GetWindowRect ( &rcCtrl );
	rcIDC_SPIN_Interval.right = rcIDC_SPIN_Interval.left + rcCtrl.Width ();
	rcIDC_SPIN_Interval.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_SPIN_Interval)->MoveWindow ( rcIDC_SPIN_Interval );

	CRect rcIDC_EDIT_Interval = rcIDC_SPIN_Interval;
	GetDlgItem(IDC_EDIT_Interval)->GetWindowRect ( &rcCtrl );
	rcIDC_EDIT_Interval.right = rcIDC_EDIT_Interval.left + rcCtrl.Width ();
	rcIDC_EDIT_Interval.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_EDIT_Interval)->MoveWindow ( rcIDC_EDIT_Interval );

	CRect rcIDC_STATIC_Interval = rcIDC_EDIT_Interval;
	GetDlgItem(IDC_STATIC_Interval)->GetWindowRect ( &rcCtrl );
	rcIDC_STATIC_Interval.right = rcIDC_STATIC_Interval.left + rcCtrl.Width ();
	rcIDC_STATIC_Interval.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_STATIC_Interval)->MoveWindow ( rcIDC_STATIC_Interval );

	CRect rcIDC_SPIN_Step = rcIDC_STATIC_Interval;
	GetDlgItem(IDC_SPIN_Step)->GetWindowRect ( &rcCtrl );
	rcIDC_SPIN_Step.right = rcIDC_SPIN_Step.left + rcCtrl.Width ();
	rcIDC_SPIN_Step.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_SPIN_Step)->MoveWindow ( rcIDC_SPIN_Step );

	CRect rcIDC_EDIT_Step = rcIDC_SPIN_Step;
	GetDlgItem(IDC_EDIT_Step)->GetWindowRect ( &rcCtrl );
	rcIDC_EDIT_Step.right = rcIDC_EDIT_Step.left + rcCtrl.Width ();
	rcIDC_EDIT_Step.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_EDIT_Step)->MoveWindow ( rcIDC_EDIT_Step );

	CRect rcIDC_STATIC_Step = rcIDC_EDIT_Step;
	GetDlgItem(IDC_STATIC_Step)->GetWindowRect ( &rcCtrl );
	rcIDC_STATIC_Step.right = rcIDC_STATIC_Step.left + rcCtrl.Width ();
	rcIDC_STATIC_Step.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_STATIC_Step)->MoveWindow ( rcIDC_STATIC_Step );

	CRect rcIDC_CHECK_Dynamic = rcIDC_STATIC_Step;
	GetDlgItem(IDC_CHECK_Dynamic)->GetWindowRect ( &rcCtrl );
	rcIDC_CHECK_Dynamic.right = rcIDC_CHECK_Dynamic.left + rcCtrl.Width ();
	rcIDC_CHECK_Dynamic.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_CHECK_Dynamic)->MoveWindow ( rcIDC_CHECK_Dynamic );

	CRect rcIDC_STATIC_StartPos = rcIDC_CHECK_Dynamic;
	GetDlgItem(IDC_STATIC_StartPos)->GetWindowRect ( &rcCtrl );
	rcIDC_STATIC_StartPos.right = rcIDC_STATIC_StartPos.left + rcCtrl.Width ();
	rcIDC_STATIC_StartPos.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_STATIC_StartPos)->MoveWindow ( rcIDC_STATIC_StartPos );

	CRect rcIDC_BUTTON_FromFile = rcIDC_STATIC_StartPos;
	GetDlgItem(IDC_BUTTON_FromFile)->GetWindowRect ( &rcCtrl );
	rcIDC_BUTTON_FromFile.right = rcIDC_BUTTON_FromFile.left + rcCtrl.Width ();
	rcIDC_BUTTON_FromFile.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	GetDlgItem(IDC_BUTTON_FromFile)->MoveWindow ( rcIDC_BUTTON_FromFile );

	CRect rcIDC_SLIDER_StartPos = rcIDC_BUTTON_FromFile;
	GetDlgItem(IDC_SLIDER_StartPos)->GetWindowRect ( &rcCtrl );
	rcIDC_SLIDER_StartPos.right = rcIDC_SLIDER_StartPos.left + rcCtrl.Width ();
	rcIDC_SLIDER_StartPos.OffsetRect ( -(rcCtrl.Width()+4), 0 );
	rcIDC_SLIDER_StartPos.left = 4;
	GetDlgItem(IDC_SLIDER_StartPos)->MoveWindow ( rcIDC_SLIDER_StartPos );

	CRect rcIDC_STATIC_Curve;
	m_staticCurve.GetWindowRect ( &rcCtrl );
	rcIDC_STATIC_Curve.left = 4;
	rcIDC_STATIC_Curve.right = rcClient.right-4;
	rcIDC_STATIC_Curve.top = 4;
	rcIDC_STATIC_Curve.bottom = rcIDC_BUTTON_Zoomin.top - 4;
	m_staticCurve.MoveWindow ( rcIDC_STATIC_Curve );
	
	Invalidate ( FALSE );
}

void CDlgDataShow::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	Align ();
}

void CDlgDataShow::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 200;
	CSize szArea = GetWorkAreaSize ();
	lpMMI->ptMaxTrackSize.x = szArea.cx;
	lpMMI->ptMaxTrackSize.y = szArea.cy;
}

void CDlgDataShow::OnBnClickedButtonDynamic()
{
	if ( ( (CButton*)GetDlgItem(IDC_CHECK_Dynamic) )->GetCheck () )
	{
		m_staticCurve.Dynamic ( GetDlgItemInt(IDC_EDIT_Interval) );
		OnEnChangeEditStep ();
	}
	else
	{
		m_staticCurve.StopDynamic ();
	}
}

void CDlgDataShow::OnDeltaposSpinStep(NMHDR *pNMHDR, LRESULT *pResult)
{
	HandleSpanClick ( this, IDC_EDIT_Step, pNMHDR, pResult, 100, 1 );
}

void CDlgDataShow::OnDeltaposSpinInterval(NMHDR *pNMHDR, LRESULT *pResult)
{
	HandleSpanClick ( this, IDC_EDIT_Interval, pNMHDR, pResult, 10000, 10, 50 );
}

void CDlgDataShow::OnEnChangeEditStep()
{
	if ( ( (CButton*)GetDlgItem(IDC_CHECK_Dynamic) )->GetCheck () )
	{
		m_staticCurve.SetDynamicStep ( GetDlgItemInt(IDC_EDIT_Step,NULL,FALSE) );
	}
}

void CDlgDataShow::OnEnChangeEditInterval()
{
	if ( ( (CButton*)GetDlgItem(IDC_CHECK_Dynamic) )->GetCheck () )
	{
		m_staticCurve.Dynamic ( GetDlgItemInt(IDC_EDIT_Interval,NULL,FALSE) );
	}
}

void CDlgDataShow::OnBnClickedButtonZoomin()
{
	m_staticCurve.SetScale ( m_staticCurve.GetCurScale () + 5 );
	ShowScale ();
}

void CDlgDataShow::OnBnClickedButtonZoomout()
{
	m_staticCurve.SetScale ( m_staticCurve.GetCurScale () - 5 );
	ShowScale ();
}

void CDlgDataShow::ShowScale(void)
{
	CString csScale;
	csScale.Format ( _T("%d %%"), m_staticCurve.GetCurScale() );
	SetDlgItemText ( IDC_STATIC_Zoom, csScale );
}

void CDlgDataShow::ShowCurStartPos(int nCurStartPos)
{
	SetDlgItemInt ( IDC_STATIC_StartPos, nCurStartPos, FALSE );
	m_SliderGraph.SetPos(nCurStartPos);
}

void CDlgDataShow::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ( pScrollBar->GetSafeHwnd() == m_SliderGraph.GetSafeHwnd() )
	{
		if ( !m_staticCurve.SetCurStartPos ( m_SliderGraph.GetPos() ) )
			m_SliderGraph.SetPos ( 0 );
		SetDlgItemInt ( IDC_STATIC_StartPos, m_SliderGraph.GetPos(), FALSE );
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CDlgDataShow::DrawDataCurve(BYTE* data, int size)
{
	m_staticCurve.DrawDataCurve ( data, size);
	// 初始化滑动条
	m_SliderGraph.SetRange(0,size);
	m_SliderGraph.SetPos(m_staticCurve.GeCurStartPos());
}

void CDlgDataShow::OnBnClickedButtonFromfile()
{
	// 用户选择文件
	CString csFileName = CommonFileDialog ( _T("CDlgDataShow::OnBnClickedButtonFromfile()"), TRUE, NULL, NULL, NULL, 
		this, _T("Please enter out file"), 
		NULL, _T("All Files(*.*)|*.*|") );
	if ( csFileName.IsEmpty () ) return;

	int nFileSize = hwGetFileAttr ( csFileName );
	if ( nFileSize < 1 ) return;
	char* data = new char[nFileSize];
	if ( !data ) return;
	int nReadBytes = ReadDataFromFile ( csFileName, data, nFileSize );
	char* RealData = new char[nReadBytes];
	if ( !RealData )
	{
		delete[] data;
		return;
	}

	if ( nReadBytes > 1 )
	{
		for ( int j=CELL_SIZE, i=0; i<nReadBytes; i+=4*CELL_SIZE )
		{
			memcpy ( &RealData[j], &data[i], CELL_SIZE );
			j += CELL_SIZE;
		}
		DrawDataCurve ( (BYTE*)RealData, nReadBytes/4);
	}
	delete[] RealData;
	delete[] data;
}
