#if !defined(AFX_STARTDLG_H__F795198C_457A_460B_B6A0_803F187074FA__INCLUDED_)
#define AFX_STARTDLG_H__F795198C_457A_460B_B6A0_803F187074FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartDlg dialog

class CStartDlg : public CDialog
{
// Construction
public:
	CStartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartDlg)
	enum { IDD = IDD_START };
	CListBox	m_ctrlList;
	BOOL	m_blDefault;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTDLG_H__F795198C_457A_460B_B6A0_803F187074FA__INCLUDED_)
