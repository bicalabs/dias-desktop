#if !defined(AFX_MARKCOMBODLG_H__103BD312_61C6_4086_8E9D_E25208CA3410__INCLUDED_)
#define AFX_MARKCOMBODLG_H__103BD312_61C6_4086_8E9D_E25208CA3410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkComboDlg.h : header file
//

#include "AimComboDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMarkComboDlg dialog

class CMarkComboDlg : public CAimComboDlg {
// Construction
public:
	CMarkComboDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMarkComboDlg)
	enum { IDD = IDD_COMBODLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	virtual void Update ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool	m_blLock;
	CImageList m_ilKernels;

	// Generated message map functions
	//{{AFX_MSG(CMarkComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKCOMBODLG_H__103BD312_61C6_4086_8E9D_E25208CA3410__INCLUDED_)
