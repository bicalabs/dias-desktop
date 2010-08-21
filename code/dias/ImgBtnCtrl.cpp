// ImgBtnCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "ImgBtnCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgBtnCtrl

CImgBtnCtrl::CImgBtnCtrl () {
	m_nState = 0;
	Update = NULL;
}

CImgBtnCtrl::~CImgBtnCtrl () {
}


BEGIN_MESSAGE_MAP(CImgBtnCtrl, CStatic)
	//{{AFX_MSG_MAP(CImgBtnCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgBtnCtrl message handlers

void CImgBtnCtrl::OnPaint () {
	CPaintDC dc (this);
	CRect	rect;
	GetClientRect (&rect);
	dc.DrawIcon (0, 0, theApp.LoadIcon ((m_nState == 1) ? m_nIDOn : m_nIDOff));
	dc.DrawEdge (rect, (m_nState == 0) ? BDR_RAISEDINNER : BDR_SUNKENOUTER, BF_RECT);
}

void CImgBtnCtrl::OnLButtonDown (UINT nFlags, CPoint point) {
	CRect	rect;
	GetClientRect (&rect);
	if (!rect.PtInRect (point))
		return;
	SetCapture ();
	CStatic::OnLButtonDown(nFlags, point);
}

void CImgBtnCtrl::OnLButtonUp (UINT nFlags, CPoint point) {
	if (GetCapture() != this)
		return;
	m_nState = 1 - m_nState;
	ReleaseCapture ();
	RedrawWindow ();
	if (Update)
		(*Update) ((CDialog*)GetParent());
	CStatic::OnLButtonUp(nFlags, point);
}
