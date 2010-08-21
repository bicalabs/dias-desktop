#if !defined(AFX_COMBODLG_H__CA91FE14_E004_4FDE_A898_D4B8FE755987__INCLUDED_)
#define AFX_COMBODLG_H__CA91FE14_E004_4FDE_A898_D4B8FE755987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboDlg.h : header file
//

#include "ImgBtnCtrl.h"

class CAimComboCtrl;

/////////////////////////////////////////////////////////////////////////////
// CAimComboDlg dialog

class CAimComboDlg : public CDialog {
// Construction
public:
	CAimComboDlg(CWnd* pParent = NULL);   // standard constructor

	CAimComboCtrl	*m_pCombo;

public:
	virtual void Update () = 0;

protected:
	UINT	m_nMenu;

// Dialog Data
	//{{AFX_DATA(CAimComboDlg)
	enum { IDD = IDD_COMBODLG };
	CImgBtnCtrl	m_btnUp;
	CImgBtnCtrl	m_btnTop;
	CImgBtnCtrl	m_btnNew;
	CImgBtnCtrl	m_btnMenu;
	CImgBtnCtrl	m_btnDown;
	CImgBtnCtrl	m_btnDelete;
	CImgBtnCtrl	m_btnBottom;
	CListCtrl	m_ctrlList;
	CStatic	m_ctrlGripper;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAimComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAimComboDlg)
	afx_msg void OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHeaderClickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMenu();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg void OnTop();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnBottom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBODLG_H__CA91FE14_E004_4FDE_A898_D4B8FE755987__INCLUDED_)
