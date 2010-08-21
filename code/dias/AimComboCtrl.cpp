// AimComboCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "AimComboDlg.h"
#include "AimComboCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAimComboCtrl

CAimComboCtrl::CAimComboCtrl () {
	m_pdlgCombo = NULL;
	m_pbmpImage = NULL;
}

CAimComboCtrl::~CAimComboCtrl () {
}


BEGIN_MESSAGE_MAP(CAimComboCtrl, CStatic)
	//{{AFX_MSG_MAP(CAimComboCtrl)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAimComboCtrl message handlers

void CAimComboCtrl::OnPaint () {
	CRect rect;
	CPaintDC dc (this);
	GetClientRect (&rect);

	m_rectBtn = rect;
	m_rectBtn.left = rect.right - 13;
	m_rectText = rect;
	m_rectText.right = rect.right - 13;
	m_rectText.DeflateRect (2, 1);
	dc.FillSolidRect (rect, ::GetSysColor (COLOR_WINDOW));
	dc.FillSolidRect (m_rectBtn, ::GetSysColor (COLOR_BTNFACE));
	dc.DrawIcon (m_rectBtn.CenterPoint () - CSize (5, 5), theApp.LoadIcon (IDI_PIC_DOWNARROW));
	dc.DrawEdge (m_rectBtn, BDR_RAISEDINNER, BF_RECT);

	CDC dcMem;
	dcMem.CreateCompatibleDC (&dc);
	CBitmap *pOld = dcMem.GetCurrentBitmap ();
	dcMem.SelectObject (m_pbmpImage);
	dc.SetBkMode (TRANSPARENT);
	//dc.SetROP2 (R2_NOP);
	//dc.SetStretchBltMode (STRETCH_HALFTONE);
	//dc.StretchBlt (m_rectText.left, m_rectText.top, m_rectText.Width(), m_rectText.Height (), &dcMem, 0, 0, 
	//               16, 16, SRCCOPY);
	dcMem.SelectObject (pOld);
	dcMem.DeleteDC ();

	Paint (dc);
}

void CAimComboCtrl::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnChar(nChar, nRepCnt, nFlags);
}

void CAimComboCtrl::OnLButtonDown (UINT nFlags, CPoint point) {
	SetCapture ();
}

void CAimComboCtrl::OnLButtonUp (UINT nFlags, CPoint point) {
	if (GetCapture () != this) {
		ReleaseCapture ();
		return;
	}
	ReleaseCapture ();
	if (!m_pdlgCombo->m_hWnd) {
		CRect rect;
		GetWindowRect (rect);
		m_pdlgCombo->Create (IDD_COMBODLG, this);
		m_pdlgCombo->SetWindowPos (NULL, rect.left, rect.bottom, m_nSizeX, m_nSizeY, SWP_NOZORDER);
		m_pdlgCombo->ShowWindow (false);
	}
	if (m_pdlgCombo->IsWindowVisible ())
		m_pdlgCombo->ShowWindow (false);
	else
		m_pdlgCombo->ShowWindow (true);
}

void CAimComboCtrl::OnLButtonDblClk (UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonDblClk(nFlags, point);
}

void CAimComboCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMButtonDown(nFlags, point);
}

void CAimComboCtrl::OnMButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMButtonUp(nFlags, point);
}

void CAimComboCtrl::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMButtonDblClk(nFlags, point);
}

void CAimComboCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnRButtonDown(nFlags, point);
}

void CAimComboCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnRButtonUp(nFlags, point);
}

void CAimComboCtrl::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnRButtonDblClk(nFlags, point);
}

void CAimComboCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMouseMove(nFlags, point);
}

BOOL CAimComboCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}

void CAimComboCtrl::OnClose () {
	m_pdlgCombo->DestroyWindow ();
	delete m_pdlgCombo;
	m_pdlgCombo = NULL;
	CStatic::OnClose();
}
