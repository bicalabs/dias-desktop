#if !defined(AFX_SMALLIMGCTRL_H__ABF04AA8_690E_4DDA_9AD9_1CE80D009CB4__INCLUDED_)
#define AFX_SMALLIMGCTRL_H__ABF04AA8_690E_4DDA_9AD9_1CE80D009CB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmallImgCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmallImgCtrl window

class CSmallImgCtrl : public CStatic
{
// Construction
public:
	CSmallImgCtrl();

// Attributes
public:
	UINT	m_nID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmallImgCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSmallImgCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSmallImgCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLIMGCTRL_H__ABF04AA8_690E_4DDA_9AD9_1CE80D009CB4__INCLUDED_)
