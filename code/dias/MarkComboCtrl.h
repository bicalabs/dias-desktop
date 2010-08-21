#if !defined(AFX_MARKCOMBOCTRL_H__ED18EDAE_4EFA_49B8_9B2F_0C4CA2834208__INCLUDED_)
#define AFX_MARKCOMBOCTRL_H__ED18EDAE_4EFA_49B8_9B2F_0C4CA2834208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkComboCtrl.h : header file
//

#include "AimComboCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMarkComboCtrl window

class CMarkComboCtrl : public CAimComboCtrl {
// Construction
public:
	CMarkComboCtrl();

// Attributes
public:
	CBitmap	*m_pbmpNone;
	CBitmap	*m_pbmpRound;
	CBitmap	*m_pbmpCross;
	CBitmap	*m_pbmpX;

// Operations
public:
	void	Update ();

protected:
	virtual void Paint (CDC& dc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkComboCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMarkComboCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMarkComboCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKCOMBOCTRL_H__ED18EDAE_4EFA_49B8_9B2F_0C4CA2834208__INCLUDED_)
