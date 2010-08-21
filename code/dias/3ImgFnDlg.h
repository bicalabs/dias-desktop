#if !defined(AFX_3IMGFNDLG_H__BD7474B5_303F_4AEE_A03C_8FD46F7F3C08__INCLUDED_)
#define AFX_3IMGFNDLG_H__BD7474B5_303F_4AEE_A03C_8FD46F7F3C08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3ImgFnDlg.h : header file
//

#include "ImgBtnCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// C3ImgFnDlg dialog

class C3ImgFnDlg : public CDialog
{
// Construction
public:
	C3ImgFnDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C3ImgFnDlg)
	enum { IDD = IDD_FN_3IMG };
	CImgBtnCtrl	m_btnToggle;
	CImgBtnCtrl	m_btnFit;
	CImgBtnCtrl	m_btnZoom1;
	CImgBtnCtrl	m_btnZoom;
	CImgBtnCtrl	m_btnHand;
	CImgBtnCtrl	m_btnAuto;
	CImgBtnCtrl	m_btnPreview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3ImgFnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3ImgFnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnReset();
	afx_msg void OnApply();
	afx_msg void OnPreview();
	afx_msg void OnAuto();
	afx_msg void OnHand();
	afx_msg void OnZoom();
	afx_msg void OnZoom1();
	afx_msg void OnZoomFit();
	afx_msg void OnToggle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3IMGFNDLG_H__BD7474B5_303F_4AEE_A03C_8FD46F7F3C08__INCLUDED_)
