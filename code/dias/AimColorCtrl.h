#if !defined(AFX_AIMCOLORCTRL_H__2DB4BAA2_096E_44AF_AAFF_686EBAECDCE1__INCLUDED_)
#define AFX_AIMCOLORCTRL_H__2DB4BAA2_096E_44AF_AAFF_686EBAECDCE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AimColorCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAimColorCtrl window

class CAimColorCtrl : public CStatic
{
// Construction
public:
	CAimColorCtrl();

// Attributes
protected:
	COLORREF	m_col;

// Operations
public:
	void OnClicked ();
	COLORREF GetColor ();
	void SetColor (COLORREF col);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAimColorCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAimColorCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAimColorCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIMCOLORCTRL_H__2DB4BAA2_096E_44AF_AAFF_686EBAECDCE1__INCLUDED_)
