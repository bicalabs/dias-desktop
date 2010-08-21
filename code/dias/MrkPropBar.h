#if !defined(AFX_MRKPROPBAR_H__AA83FF3C_EABF_4E7A_BA8D_B813700F4D18__INCLUDED_)
#define AFX_MRKPROPBAR_H__AA83FF3C_EABF_4E7A_BA8D_B813700F4D18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MrkPropBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMrkPropBar dialog

#include "AimColorCtrl.h"
#include "SmallImgCtrl.h"
#include "ImgBtnCtrl.h"
#include "NumEditCtrl.h"
#include "MarkComboCtrl.h"
#include "KrnlComboCtrl.h"
#include "ShapeComboCtrl.h"

class CMrkPropBar : public CDialog {
// Construction
public:
	CMrkPropBar(CWnd* pParent = NULL);   // standard constructor

	void Update ();

// Dialog Data
	//{{AFX_DATA(CMrkPropBar)
	enum { IDD = IDD_TBP_MRKCREATE };
	CAimColorCtrl	m_colShp;
	CAimColorCtrl	m_colKrnl;
	CAimColorCtrl	m_colFill;
	CImgBtnCtrl	m_lockSize;
	CMarkComboCtrl	m_cmbStyle;
	CKrnlComboCtrl	m_cmbKernel;
	CShapeComboCtrl	m_cmbShape;
	CNumEditCtrl	m_numRot;
	CNumEditCtrl	m_numShpY;
	CNumEditCtrl	m_numShpX;
	CNumEditCtrl	m_numKernel;
	CImgBtnCtrl	m_lockShpCol;
	CSmallImgCtrl	m_icoKrnlSize;
	CSmallImgCtrl	m_icoShpRot;
	CSmallImgCtrl	m_icoFillCol;
	CSmallImgCtrl	m_icoShpCol;
	CSmallImgCtrl	m_icoShpY;
	CSmallImgCtrl	m_icoShpX;
	CSmallImgCtrl	m_icoKrnlCol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMrkPropBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMrkPropBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnKrnlColor();
	afx_msg void OnShpColor();
	afx_msg void OnFillColor();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRKPROPBAR_H__AA83FF3C_EABF_4E7A_BA8D_B813700F4D18__INCLUDED_)
