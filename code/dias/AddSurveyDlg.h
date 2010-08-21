#if !defined(AFX_ADDSURVEYDLG_H__224B432C_1E51_4FE1_94D8_5ED85F19F26D__INCLUDED_)
#define AFX_ADDSURVEYDLG_H__224B432C_1E51_4FE1_94D8_5ED85F19F26D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSurveyDlg.h : header file
//

#include "ImgBtnCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CAddSurveyDlg dialog

class CAddSurveyDlg : public CDialog
{
// Construction
public:
	CAddSurveyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddSurveyDlg)
	enum { IDD = IDD_DOC_ADD_SURVEY };
	CStatic	m_ctrlDescript;
	CComboBoxEx	m_ctrlObject;
	CImgBtnCtrl	m_btnRemove;
	CImgBtnCtrl	m_btnDown;
	CImgBtnCtrl	m_btnUp;
	CListCtrl	m_ctrlList;
	CTreeCtrl	m_ctrlTree;
	//}}AFX_DATA
public:
	CStorageDoc	*m_pDoc;
	CSurvey		*m_pSurvey;
protected:
	ubyte		m_nObject;
	CImageList	m_ilObjects;
	CImageList	m_ilTypes;
	CArray <HTREEITEM,HTREEITEM> m_claRoots;
	CArray <HTREEITEM,HTREEITEM> m_claItems;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddSurveyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateTree ();
	void UpdateList ();
	// Generated message map functions
	//{{AFX_MSG(CAddSurveyDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelChangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetFocusTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetFocusList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnRemove();
	afx_msg void OnSelchangeObject();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSURVEYDLG_H__224B432C_1E51_4FE1_94D8_5ED85F19F26D__INCLUDED_)
