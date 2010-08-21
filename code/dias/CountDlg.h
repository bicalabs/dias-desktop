#if !defined(AFX_COUNTDLG_H__D2819B16_7583_4010_A3C8_13E6D06CFF09__INCLUDED_)
#define AFX_COUNTDLG_H__D2819B16_7583_4010_A3C8_13E6D06CFF09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CountDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountDlg dialog

class CCountDlg : public CDialog
{
// Construction
public:
	CCountDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCountDlg)
	enum { IDD = IDD_COUNT };
	int		m_iValue;
	CString	m_strPrompt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCountDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTDLG_H__D2819B16_7583_4010_A3C8_13E6D06CFF09__INCLUDED_)
