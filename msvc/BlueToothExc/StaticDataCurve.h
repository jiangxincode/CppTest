#pragma once

#include "PublicFunc.h"

// CStaticDataCurve

// 正常比例下X轴的步长
#define NORMAL_SCALE_STEP_X		5
// 多少字节表示一个点
#define CELL_SIZE				1

class CStaticDataCurve : public CStatic
{
	DECLARE_DYNAMIC(CStaticDataCurve)

public:
	CStaticDataCurve();
	virtual ~CStaticDataCurve();
	void DrawDataCurve(BYTE* data, int size);
	void SetForeColor ( COLORREF clrLinePallid, COLORREF clrLineHighlight );
	void SetBkColor(COLORREF clr);
	BOOL SetCurStartPos(int nCurStartPos);
	void Dynamic(int speed);
	void StopDynamic(void);
	BOOL SetScale(int nScale);
	int GetCurScale() { return m_nCurScale; }
	int GetDynamicStep() { return m_nDynamicStep; }
	BOOL SetDynamicStep(int nDynamicStep);
	int GeCurStartPos () { return m_nCurStartPos; }

protected:
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
private:
	BYTE* m_data;
	int m_size;
	COLORREF m_clrLinePallid;			// 线条暗淡色
	COLORREF m_clrLineHighlight;		// 线条加亮色
	CBrush m_brsBkGnd;					// 背景刷

	int m_nCurScale;					// 当前显示比例，100表示100%
	int m_nCurStartPos;					// 当前显示数据是从缓冲哪个位置开始的
	int m_nDynamicStep;					// 动态显示时每次跳动的步长

private:
	int CalcShowDataBytes(CRect& rcClient, float nStepX);
	BYTE* GetSingleDrawingData(CRect &rcClient, int& size);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	float CalcStepX(void);
};


