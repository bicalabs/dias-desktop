#if !defined(AFX_ADDIMAGESDLG_H__123B22E3_1756_411E_9ECA_6404D4CB0EB6__INCLUDED_)
#define AFX_ADDIMAGESDLG_H__123B22E3_1756_411E_9ECA_6404D4CB0EB6__INCLUDED_

#pragma once

class CAddImagesDlg : public CDialog {
// Construction
public:
	CAddImagesDlg (CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddImagesDlg)
	enum { IDD = IDD_DOC_ADD_IMAGES };
	UINT	m_nCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddImagesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddImagesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDIMAGESDLG_H__123B22E3_1756_411E_9ECA_6404D4CB0EB6__INCLUDED_)
