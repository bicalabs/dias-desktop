// AimColorCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "AimColorCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAimColorCtrl

CAimColorCtrl::CAimColorCtrl () {
	m_col = 0;
}

CAimColorCtrl::~CAimColorCtrl () {
}


BEGIN_MESSAGE_MAP (CAimColorCtrl, CStatic)
	//{{AFX_MSG_MAP(CAimColorCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// CAimColorCtrl message handlers

void CAimColorCtrl::OnPaint () {
	CRect rect, rcBtn, rcCol;
	CPaintDC dc(this);

	GetClientRect (&rect);
	rcCol = rcBtn = rect;
	rcCol -= CRect (0,0,11,0);
	rcBtn.left = rcCol.right + 1;
	dc.FillSolidRect (rcCol, m_col);
	dc.FillSolidRect (rcBtn, ::GetSysColor (COLOR_BTNFACE));
	dc.DrawIcon (rcBtn.TopLeft (), theApp.LoadIcon (IDI_PIC_RIGTHARROW));
	dc.DrawEdge (rcBtn, BDR_RAISEDINNER, BF_RECT);
}

COLORREF CAimColorCtrl::GetColor () {
	return (m_col);
}

void CAimColorCtrl::SetColor (COLORREF col) {
	m_col = col;
	Invalidate (false);
	RedrawWindow ();
}

/*void CAimColorCtrl::OnLButtonDown (UINT nFlags, CPoint point) {
	SetCapture ();
	CStatic::OnLButtonDown (nFlags, point);
}

void CAimColorCtrl::OnLButtonUp (UINT nFlags, CPoint point) {
	if (GetCapture () != this) {
		CStatic::OnLButtonUp(nFlags, point);
		return;
	}
	ReleaseCapture ();
	CColorDialog dlgCol (m_col, CC_FULLOPEN | CC_ANYCOLOR, theApp.m_pMainWnd);
	if (dlgCol.DoModal () != IDOK)
		return;
	m_col = dlgCol.GetColor ();
	Invalidate (false);
	RedrawWindow ();
	CStatic::OnLButtonUp(nFlags, point);
}*/

void CAimColorCtrl::OnClicked () {
	CColorDialog dlgCol (m_col, CC_FULLOPEN | CC_ANYCOLOR, theApp.m_pMainWnd);
	if (dlgCol.DoModal () != IDOK)
		return;
	m_col = dlgCol.GetColor ();
	Invalidate (false);
	RedrawWindow ();
}
