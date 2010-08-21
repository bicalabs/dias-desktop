#if !defined(AFX_KRNLCOMBOCTRL_H__ED18EDAE_4EFA_49B8_9B2F_0C4CA2834208__INCLUDED_)
#define AFX_KRNLCOMBOCTRL_H__ED18EDAE_4EFA_49B8_9B2F_0C4CA2834208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KrnlComboCtrl.h : header file
//

#include "AimComboCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CKrnlComboCtrl window

class CKrnlComboCtrl : public CAimComboCtrl {
// Construction
public:
	CKrnlComboCtrl();

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
	//{{AFX_VIRTUAL(CKrnlComboCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKrnlComboCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CKrnlComboCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KRNLCOMBOCTRL_H__ED18EDAE_4EFA_49B8_9B2F_0C4CA2834208__INCLUDED_)
