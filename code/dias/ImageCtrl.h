#if !defined(AFX_IMAGECTRL_H__87965AB3_5F60_46B9_A2C1_41482D5B611C__INCLUDED_)
#define AFX_IMAGECTRL_H__87965AB3_5F60_46B9_A2C1_41482D5B611C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageCtrl window

class CImageCtrl : public CStatic
{
// Construction
public:
	CImageCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageCtrl)
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGECTRL_H__87965AB3_5F60_46B9_A2C1_41482D5B611C__INCLUDED_)
