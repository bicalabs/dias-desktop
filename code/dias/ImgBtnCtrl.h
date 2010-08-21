#if !defined(AFX_IMGBTNCTRL_H__421EF75C_FB08_4DC4_AD9E_65A5CB59E3C6__INCLUDED_)
#define AFX_IMGBTNCTRL_H__421EF75C_FB08_4DC4_AD9E_65A5CB59E3C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImgBtnCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImgBtnCtrl window

class CImgBtnCtrl : public CStatic
{
// Construction
public:
	CImgBtnCtrl();

// Attributes
public:
	UINT	m_nIDOn;
	UINT	m_nIDOff;
	ubyte	m_nState;
	typedef void	(UpdateFn)(CDialog *);
	UpdateFn* Update;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgBtnCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgBtnCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImgBtnCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGBTNCTRL_H__421EF75C_FB08_4DC4_AD9E_65A5CB59E3C6__INCLUDED_)
