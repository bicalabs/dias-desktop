#if !defined(AFX_AIMSTATUSBAR_H__19C4D139_BB70_4D92_A03D_B71F0A7676D7__INCLUDED_)
#define AFX_AIMSTATUSBAR_H__19C4D139_BB70_4D92_A03D_B71F0A7676D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AimStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAimStatusBar window

class CAimStatusBar : public CStatusBar {
// Construction
public:
	CAimStatusBar();

// Attributes
public:
	CBitmap	*m_pBitmaps;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAimStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAimStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAimStatusBar)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIMSTATUSBAR_H__19C4D139_BB70_4D92_A03D_B71F0A7676D7__INCLUDED_)
