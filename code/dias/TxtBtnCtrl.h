#if !defined(AFX_TXTBTNCTRL_H__25EB6BDA_D48E_4314_AEF3_5D39923293F4__INCLUDED_)
#define AFX_TXTBTNCTRL_H__25EB6BDA_D48E_4314_AEF3_5D39923293F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TxtBtnCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTxtBtnCtrl window

class CTxtBtnCtrl : public CStatic
{
// Construction
public:
	CTxtBtnCtrl();

// Attributes
public:
	CString	m_strTitle;
protected:
	CFont	m_fntText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxtBtnCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTxtBtnCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTxtBtnCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXTBTNCTRL_H__25EB6BDA_D48E_4314_AEF3_5D39923293F4__INCLUDED_)
