// diti.h : main header file for the DITI application
//

#if !defined(AFX_DITI_H__1AA1D9B8_7126_4DEC_B9B0_9D0593ECF222__INCLUDED_)
#define AFX_DITI_H__1AA1D9B8_7126_4DEC_B9B0_9D0593ECF222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDitiApp:
// See diti.cpp for the implementation of this class
//

class CDitiApp : public CWinApp
{
public:
	CDitiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDitiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDitiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DITI_H__1AA1D9B8_7126_4DEC_B9B0_9D0593ECF222__INCLUDED_)
