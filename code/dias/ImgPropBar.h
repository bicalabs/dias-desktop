#if !defined(AFX_IMGPROPBAR_H__D0C07B75_CA29_4E95_9C25_446322FBC721__INCLUDED_)
#define AFX_IMGPROPBAR_H__D0C07B75_CA29_4E95_9C25_446322FBC721__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImgPropBar.h : header file
//

#include "TxtBtnCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CImgPropBar dialog

class CImgPropBar : public CDialog
{
// Construction
public:
	CImgPropBar(CWnd* pParent = NULL);   // standard constructor

	void Update ();

// Dialog Data
	//{{AFX_DATA(CImgPropBar)
	enum { IDD = IDD_TBP_IMAGE };
	CTxtBtnCtrl	m_btnDescr;
	CTxtBtnCtrl	m_btnText;
	CEdit	m_ctrlDescr;
	CEdit	m_ctrlName;
	//}}AFX_DATA

// Data
public:
	bool	m_blLock;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgPropBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImgPropBar)
	afx_msg void OnChangeName();
	afx_msg void OnChangeDescr();
	virtual BOOL OnInitDialog();
	afx_msg void OnShow();
	afx_msg void OnHide();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROPBAR_H__D0C07B75_CA29_4E95_9C25_446322FBC721__INCLUDED_)
