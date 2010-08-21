#if !defined(AFX_DOCNEWDLG_H__EFF8331A_9034_4BC6_955B_5D8D2983E546__INCLUDED_)
#define AFX_DOCNEWDLG_H__EFF8331A_9034_4BC6_955B_5D8D2983E546__INCLUDED_

#pragma once

#include "TxtBtnCtrl.h"

class CDocNewDlg : public CDialog {
// Construction
public:
	CDocNewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDocNewDlg)
	enum { IDD = IDD_DOC_NEW };
	CTxtBtnCtrl	m_btnSave;
	CTxtBtnCtrl	m_btnImport;
	CTxtBtnCtrl	m_btnDelete;
	CListCtrl	m_ctrlModels;
	CComboBox	m_ctrlSource;
	CString	m_strDimX;
	CString	m_strDimY;
	CString	m_strDescription;
	long	m_nCount;
	CString	m_strName;
	CImageList m_imgList;
	//}}AFX_DATA
	ubyte	m_nModel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocNewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDocNewDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCNEWDLG_H__EFF8331A_9034_4BC6_955B_5D8D2983E546__INCLUDED_)
