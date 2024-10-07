#pragma once

#include "PublicFunc.h"

// CStaticDataCurve

// ����������X��Ĳ���
#define NORMAL_SCALE_STEP_X		5
// �����ֽڱ�ʾһ����
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
	COLORREF m_clrLinePallid;			// ��������ɫ
	COLORREF m_clrLineHighlight;		// ��������ɫ
	CBrush m_brsBkGnd;					// ����ˢ

	int m_nCurScale;					// ��ǰ��ʾ������100��ʾ100%
	int m_nCurStartPos;					// ��ǰ��ʾ�����Ǵӻ����ĸ�λ�ÿ�ʼ��
	int m_nDynamicStep;					// ��̬��ʾʱÿ�������Ĳ���

private:
	int CalcShowDataBytes(CRect& rcClient, float nStepX);
	BYTE* GetSingleDrawingData(CRect &rcClient, int& size);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	float CalcStepX(void);
};


