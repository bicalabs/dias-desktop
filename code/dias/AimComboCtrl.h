#if !defined(AFX_AIMCOMBOCTRL_H__A86375FB_F5DB_4DFB_AC1B_6EFE6480881E__INCLUDED_)
#define AFX_AIMCOMBOCTRL_H__A86375FB_F5DB_4DFB_AC1B_6EFE6480881E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AimComboCtrl.h : header file
//

class CAimComboDlg;

/////////////////////////////////////////////////////////////////////////////
// CAimComboCtrl window

class CAimComboCtrl : public CStatic {
// Construction
public:
	CAimComboCtrl();

// Attributes
public:
	uint		m_nSizeX;
	uint		m_nSizeY;
	CBitmap		*m_pbmpImage;
	CAimComboDlg	*m_pdlgCombo;

protected:
	CRect		m_rectBtn, m_rectText;
	void virtual	Paint (CDC& dc) = 0;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAimComboCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAimComboCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAimComboCtrl)
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnClose();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIMCOMBOCTRL_H__A86375FB_F5DB_4DFB_AC1B_6EFE6480881E__INCLUDED_)
