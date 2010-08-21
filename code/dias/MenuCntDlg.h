#if !defined(AFX_MENUCNTDLG_H__E4281516_10DD_490B_8A78_560DFF878EE2__INCLUDED_)
#define AFX_MENUCNTDLG_H__E4281516_10DD_490B_8A78_560DFF878EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuCntDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuCntDlg dialog

class CMenuCntDlg : public CDialog {
// Construction
public:
	CMenuCntDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMenuCntDlg)
	enum { IDD = IDD_MENUCOUNT };
	CSliderCtrl	m_ctrlSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuCntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Attributes
public:
	UINT	m_nX, m_nY, m_nMin, m_nMax;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMenuCntDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSliderChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUCNTDLG_H__E4281516_10DD_490B_8A78_560DFF878EE2__INCLUDED_)
