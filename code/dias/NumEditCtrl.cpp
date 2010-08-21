// NumEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "NumEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumEditCtrl

CNumEditCtrl::CNumEditCtrl () {
	m_pEdit = new CEdit ();
	m_fntText.CreateFont (12, 0, 0, 0, FW_NORMAL, false, false, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	                      CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
	Update = NULL;
}

CNumEditCtrl::~CNumEditCtrl () {
	delete m_pEdit;
}

void CNumEditCtrl::Init (rtbyte rVal, CString strUn1Abr, CString strUn1Name) {
	m_blMono = true;
	m_rValue = rVal;
	m_nUnits = 0;
	m_strUnits1[0] = strUn1Abr;
	m_strUnits1[1] = strUn1Name;
	m_strUnits2[0] = "";
	m_strUnits2[1] = "";

	CRect rect;
	GetClientRect (&rect);
	m_rectBtn = rect;
	m_rectBtn.left = rect.right - 10;
	m_rectText = rect;
	m_rectText.right = rect.right - 15;
	m_pEdit->Create (WS_CHILD | ES_LEFT | ES_AUTOHSCROLL | WS_VISIBLE, m_rectText, this, 0);
	CString strFormat;
	strFormat.Format ("%g", m_rValue);
	m_pEdit->SetWindowText (strFormat);
}

void CNumEditCtrl::Init (rtbyte rVal, ubyte nUnits, CString strUn1Abr, CString strUn1Name, CString strUn2Abr, CString strUn2Name) {
	m_blMono = false;
	m_rValue = rVal;
	m_nUnits = nUnits;
	m_strUnits1[0] = strUn1Abr;
	m_strUnits1[1] = strUn1Name;
	m_strUnits2[0] = strUn2Abr;
	m_strUnits2[1] = strUn2Name;

	CRect rect;
	GetClientRect (&rect);
	m_rectBtn = rect;
	m_rectBtn.left = rect.right - 10;
	m_rectText = rect;
	m_rectText.right = m_rectBtn.left - 15;
	m_pEdit->Create (WS_CHILD | ES_LEFT | ES_AUTOHSCROLL | WS_VISIBLE, m_rectText, this, 0);
	m_pEdit->SetFont (&m_fntText);
	CString strFormat;
	strFormat.Format ("%g", m_rValue);
	m_pEdit->SetWindowText (strFormat);
}

rtbyte CNumEditCtrl::GetValue () {
	CString txt;
	m_pEdit->GetWindowText (txt);
	m_rValue = atof (txt);
	return (m_rValue);
}

void CNumEditCtrl::SetValue (rtbyte rValue) {
	m_rValue = rValue;
	CString strFormat;
	strFormat.Format ("%g", m_rValue);
	m_pEdit->SetWindowText (strFormat);
	RedrawWindow ();
}

void CNumEditCtrl::SetTransform (rtbyte rTrans) {
	m_rTransform = rTrans;
	CString strFormat;
	strFormat.Format ("%g", m_rValue);
	m_pEdit->SetWindowText (strFormat);
	RedrawWindow ();
}

BEGIN_MESSAGE_MAP(CNumEditCtrl, CStatic)
	//{{AFX_MSG_MAP(CNumEditCtrl)
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
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_PARENTNOTIFY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumEditCtrl message handlers

void CNumEditCtrl::OnLButtonDown (UINT nFlags, CPoint point) {
	SetCapture ();
	m_pEdit->SetFocus ();
//	CStatic::OnLButtonDown(nFlags, point);
}

void CNumEditCtrl::OnLButtonUp(UINT nFlags, CPoint point) {
	if (GetCapture () != this)
		CStatic::OnLButtonUp(nFlags, point);
	ReleaseCapture ();
	m_pEdit->ShowWindow (true);
}

void CNumEditCtrl::OnLButtonDblClk (UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonDblClk(nFlags, point);
}

void CNumEditCtrl::OnMButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMButtonDown(nFlags, point);
}

void CNumEditCtrl::OnMButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMButtonUp(nFlags, point);
}

void CNumEditCtrl::OnMButtonDblClk(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMButtonDblClk(nFlags, point);
}

void CNumEditCtrl::OnRButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnRButtonDown(nFlags, point);
}

void CNumEditCtrl::OnRButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnRButtonUp(nFlags, point);
}

void CNumEditCtrl::OnRButtonDblClk(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnRButtonDblClk(nFlags, point);
}

void CNumEditCtrl::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMouseMove(nFlags, point);
}

BOOL CNumEditCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	// TODO: Add your message handler code here and/or call default
	
	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}

void CNumEditCtrl::OnPaint () {
	CFont *pFont;
	CRect rectUnits;
	CPaintDC dc (this);
	rectUnits = m_rectText;
	rectUnits.left = m_rectBtn.left - 15;
	rectUnits.right = m_rectBtn.left - 1;
	pFont = dc.SelectObject (&m_fntText);
	dc.SetBkMode (TRANSPARENT);
	dc.FillSolidRect (rectUnits, ::GetSysColor (COLOR_WINDOW));
	dc.FillSolidRect (m_rectBtn, ::GetSysColor (COLOR_BTNFACE));
	dc.DrawIcon (m_rectBtn.TopLeft (), theApp.LoadIcon (IDI_PIC_RIGTHARROW));
	dc.DrawEdge (m_rectBtn, BDR_RAISEDINNER, BF_RECT);
	dc.DrawText ((m_nUnits == 0) ? m_strUnits1[0] : m_strUnits2[0], rectUnits, DT_VCENTER | DT_END_ELLIPSIS | DT_RIGHT | DT_SINGLELINE);
	dc.SelectObject (pFont);
	m_pEdit->RedrawWindow ();
}

BOOL CNumEditCtrl::OnSetCursor (CWnd* pWnd, UINT nHitTest, UINT message) {
	// TODO: Add your message handler code here and/or call default
	
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CNumEditCtrl::OnKillFocus (CWnd* pNewWnd) {
	if (Update)
		(*Update) ((CDialog*)GetParent());
	CStatic::OnKillFocus(pNewWnd);
}

void CNumEditCtrl::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) {
	;
}

void CNumEditCtrl::OnParentNotify(UINT message, LPARAM lParam) {
	if (Update)
		(*Update) ((CDialog*)GetParent());
	CStatic::OnParentNotify(message, lParam);
}
