#if !defined(AFX_IMAGEWND_H__F7A49C14_9A93_48EE_BD0A_ADC4E68AD96C__INCLUDED_)
#define AFX_IMAGEWND_H__F7A49C14_9A93_48EE_BD0A_ADC4E68AD96C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageWnd window

class CStorageDoc;
class CStorageView;
class CStorageFrame;

class CImageWnd : public CWnd {
// Construction
public:
	CImageWnd();

// Attributes
public:
	CStorageDoc*	m_pDoc;
	CStorageView*	m_pView;
	CStorageFrame*	m_pFrame;
	int		m_nHScrollPos;
	int		m_nVScrollPos;

protected:
	CPen		*m_ppenLine;
	CPen		*m_ppenBoundary;
	CPen		*m_ppenChord;

	CBitmap		m_bmpImage;
	CBitmap		*m_pbmpOld;
	BYTE		*m_pbBits;
	UINT		m_nImage;

	uvar32_64	m_nStart;
	CPoint		m_pntOld;
	CPoint		m_pntStart;
	ubyte		m_nCaptureMode;
	CMark*		m_pMarkActive;

// Operations
public:
	void CreateImage (CPaintDC *dcThis = NULL);
	void PaintMark (uvar32_64 n);

	void UpdateScroll ();

protected:
	CPoint MapPntToScrCoord (const CPoint pnt);
	void MapPntToScrCoord (CPoint* ppnt, uvar32_64 cnt);
	CRect GetImageRect (int& width, int& height);
	void PaintActiveMark ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageWnd)
public:
	afx_msg void OnPaint();
protected:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEWND_H__F7A49C14_9A93_48EE_BD0A_ADC4E68AD96C__INCLUDED_)
