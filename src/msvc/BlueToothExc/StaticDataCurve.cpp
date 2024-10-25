// StaticDataCurve.cpp : 实现文件
//

#include "stdafx.h"
#include "BlueToothExc.h"
#include "StaticDataCurve.h"
#include "DlgDataShow.h"

// CStaticDataCurve

IMPLEMENT_DYNAMIC(CStaticDataCurve, CStatic)

CStaticDataCurve::CStaticDataCurve()
	: m_data ( NULL )
	, m_size ( 0 )
	, m_nCurScale ( 100 )
	, m_nCurStartPos(0)
	, m_nDynamicStep ( 1 )
{
	m_clrLinePallid = RGB(0,128,0);
	m_clrLineHighlight = RGB(0,255,0);
}

CStaticDataCurve::~CStaticDataCurve()
{
	if ( m_brsBkGnd.GetSafeHandle() )
	{
		m_brsBkGnd.DeleteObject();
	}
	if ( m_data ) delete[] m_data;
	m_data = NULL;
}


BEGIN_MESSAGE_MAP(CStaticDataCurve, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CStaticDataCurve::OnEraseBkgnd(CDC* pDC) 
{
	if ( m_brsBkGnd.GetSafeHandle() )
	{
		CRect rcClient(0,0,0,0);
		GetClientRect ( &rcClient );
		pDC->FillRect ( &rcClient, &m_brsBkGnd );
	}

	return TRUE;
}

// CStaticDataCurve 消息处理程序

void CStaticDataCurve::DrawDataCurve(BYTE* data, int size)
{
	if ( m_data && size==m_size && memcmp(m_data,data,size)==0 )
	{
		TRACE ( _T("Not changed\n") );
	}
	else
	{
		if ( m_data ) delete[] m_data;
		m_data = new BYTE[size];
		memcpy ( m_data, data, size );
		m_size = size;
	}

	if ( IsWindow(m_hWnd) )
	{
		Invalidate ();
	}
}


void CStaticDataCurve::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC *pDC = &dc;
	CRect rcClient(0,0,0,0);
	GetClientRect ( &rcClient );

	// 画数据曲线
	int size = 0;
	BYTE *data = GetSingleDrawingData ( rcClient, size );
	if ( data )
	{
		rcClient.DeflateRect ( 4, 4 );
		DrawCurveByDataBuffer ( &dc, rcClient, m_clrLineHighlight, data, size, CELL_SIZE );
		delete[] data;
		data = NULL;
	}
}

void CStaticDataCurve::SetBkColor(COLORREF clr)
{
	if ( m_brsBkGnd.GetSafeHandle() )
	{
		m_brsBkGnd.DeleteObject();
	}
	m_brsBkGnd.CreateSolidBrush ( clr );
	if ( ::IsWindow ( m_hWnd ) )
		Invalidate ();
}

void CStaticDataCurve::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();

	SetBkColor ( RGB(0,0,0) );
}

//
// 设置前景线条和文字的颜色
//
void CStaticDataCurve::SetForeColor(COLORREF clrLinePallid, COLORREF clrLineHighlight)
{
	m_clrLinePallid = clrLinePallid;
	m_clrLineHighlight = clrLineHighlight;
	if ( ::IsWindow ( m_hWnd ) )
		Invalidate ();
}

//
// 计算当前的X轴步长
//
float CStaticDataCurve::CalcStepX(void)
{
	ASSERT ( m_nCurScale > 0 );
	float fStepX = (float)m_nCurScale * (float)NORMAL_SCALE_STEP_X / (float)100;
	if ( fStepX < 1.0 ) fStepX = 1.0;
	return fStepX;
}

//
// 设置显示比例
//
BOOL CStaticDataCurve::SetScale(int nScale)
{
	if ( nScale < 10 || nScale > 1000 ) return FALSE;
	if ( nScale == m_nCurScale ) return TRUE;
	m_nCurScale = nScale;
	if ( ::IsWindow ( m_hWnd ) )
		Invalidate ();

	return TRUE;
}

//
// 计算当前可以显示多少个字节的数据
//
int CStaticDataCurve::CalcShowDataBytes(CRect& rcClient, float fStepX)
{
	ASSERT ( fStepX > 0.0 );
	return (int)((float)CELL_SIZE * (float)rcClient.Width() / fStepX);
}

//
// 得到单次用来画线的数据，注意：及时用 delete[] 删除返回的数据
//
BYTE* CStaticDataCurve::GetSingleDrawingData(CRect &rcClient, OUT int& size)
{
	if ( m_size <= 0 ) return NULL;
	ASSERT ( m_nCurStartPos < m_size );
	float fStepX = CalcStepX ();
	ASSERT ( fStepX > 0.0 );
	int nShowDataBytes = CalcShowDataBytes ( rcClient, fStepX );
	BYTE *data = new BYTE[nShowDataBytes];
	if ( !data ) return NULL;

	// 先从 m_nCurStartPos 开始处取尾部的数据
	size = nShowDataBytes;
	int nCopyBytes = m_size - m_nCurStartPos;
	if ( nCopyBytes > nShowDataBytes )
		nCopyBytes = nShowDataBytes;
	memcpy ( data, m_data+m_nCurStartPos, nCopyBytes );
	if ( nCopyBytes >= nShowDataBytes ) return data;
	
	// 数据不够时循环使用前面的数据接上来使用
	while ( nShowDataBytes - nCopyBytes > 0 )
	{
		int nCanCopyBytes = MIN(m_size,nShowDataBytes - nCopyBytes);
		memcpy ( data+nCopyBytes, m_data, nCanCopyBytes );
		nCopyBytes += nCanCopyBytes;
	}

	return data;
}

//
// 设置当前起始位置
//
BOOL CStaticDataCurve::SetCurStartPos(int nCurStartPos)
{
	if ( m_size < 1 ) return FALSE;
	if ( nCurStartPos < 0 )
		return FALSE;
	nCurStartPos %= m_size;
	if ( m_nCurStartPos == nCurStartPos )
		return TRUE;
	m_nCurStartPos = nCurStartPos;
	if ( ::IsWindow ( m_hWnd ) )
		Invalidate ();

	return TRUE;
}

void CStaticDataCurve::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == 1 )
	{
		if ( !SetCurStartPos ( m_nCurStartPos+m_nDynamicStep ) )
			m_nCurStartPos = 0;
		( (CDlgDataShow*)GetParent() )->ShowCurStartPos ( m_nCurStartPos );
	}

	CStatic::OnTimer(nIDEvent);
}

void CStaticDataCurve::Dynamic(int speed)
{
	if ( m_size < 1 ) return;
	KillTimer ( 1 );
	SetTimer ( 1, speed, NULL );
}

void CStaticDataCurve::StopDynamic(void)
{
	KillTimer ( 1 );
}

BOOL CStaticDataCurve::SetDynamicStep(int nDynamicStep)
{
	if ( nDynamicStep < 1 || nDynamicStep >= m_size )
		return FALSE;

	m_nDynamicStep = nDynamicStep;

	return TRUE;
}
