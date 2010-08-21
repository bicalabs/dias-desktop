#if !defined(AFX_SHAPECOMBODLG_H__103BD312_61C6_4086_8E9D_E25208CA3410__INCLUDED_)
#define AFX_SHAPECOMBODLG_H__103BD312_61C6_4086_8E9D_E25208CA3410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShapeComboDlg.h : header file
//

#include "AimComboDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CShapeComboDlg dialog

class CShapeComboDlg : public CAimComboDlg {
// Construction
public:
	CShapeComboDlg(CWnd* pParent = NULL);   // standard constructor

	virtual void Update ();

// Dialog Data
	//{{AFX_DATA(CShapeComboDlg)
	enum { IDD = IDD_COMBODLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShapeComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool	m_blLock;
	CImageList m_ilKernels;

	// Generated message map functions
	//{{AFX_MSG(CShapeComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAPECOMBODLG_H__103BD312_61C6_4086_8E9D_E25208CA3410__INCLUDED_)
