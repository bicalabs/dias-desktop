#if !defined(AFX_NUMEDITCTRL_H__0F59A3BE_5CC8_408B_A912_634FF6774369__INCLUDED_)
#define AFX_NUMEDITCTRL_H__0F59A3BE_5CC8_408B_A912_634FF6774369__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumEditCtrl window

class CNumEditCtrl : public CStatic {
// Construction
public:
	CNumEditCtrl();

// Attributes
public:
	typedef void	(UpdateFn)(CDialog *);
	UpdateFn* Update;

protected:
	rtbyte m_rTransform;
	rtbyte	m_rValue;
	bool	m_blMono;
	ubyte	m_nUnits;
	CString	m_strUnits1[2];
	CString	m_strUnits2[2];

protected:
	CRect		m_rectBtn, m_rectText;
	CEdit		*m_pEdit;
	CFont		m_fntText;
	CSpinButtonCtrl	*m_pSpin;

// Operations
public:
	void Init (rtbyte rVal, CString strUn1Abr, CString strUn1Name);
	void Init (rtbyte rVal, ubyte nUnits, CString strUn1Abr, CString strUn1Name, CString strUn2Abr, CString strUn2Name);
	rtbyte GetValue ();
	void SetValue (rtbyte rValue);
	void SetTransform (rtbyte rTrans);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEditCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNumEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumEditCtrl)
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
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDITCTRL_H__0F59A3BE_5CC8_408B_A912_634FF6774369__INCLUDED_)
