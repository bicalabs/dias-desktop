// KrnlComboCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "KrnlComboDlg.h"
#include "KrnlComboCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKrnlComboCtrl

CKrnlComboCtrl::CKrnlComboCtrl () {
	CAimComboCtrl::CAimComboCtrl ();
	m_pdlgCombo = new CKrnlComboDlg ();
	m_pbmpNone = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_NONE);
	m_pbmpRound = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_ROUND);
	m_pbmpCross = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_CROSS);
	m_pbmpX = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_X);
	m_pbmpImage = m_pbmpRound;
	m_nSizeX = 125;
	m_nSizeY = 100;
}

CKrnlComboCtrl::~CKrnlComboCtrl () {
	CAimComboCtrl::~CAimComboCtrl ();
}


BEGIN_MESSAGE_MAP(CKrnlComboCtrl, CAimComboCtrl)
	//{{AFX_MSG_MAP(CKrnlComboCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKrnlComboCtrl message handlers

void CKrnlComboCtrl::Update () {
	CMark::MarkKernel krnl;
//	if (theApp.Documents[aimActive].Images[aimActive].Marks(aimActive).GetCount ())
//		krnl = theApp.Documents[aimActive].Images[aimActive].Marks(aimActive)[0].GetKernel ();
//	else
		krnl = theApp.MarkStyles[aimActive].GetStyle().GetKernel ();
	m_pbmpImage = (krnl == CMark::krnlNone) ? m_pbmpNone : (
	              (krnl == CMark::krnlRound) ? m_pbmpRound : (
	              (krnl == CMark::krnlPlus) ? m_pbmpCross : m_pbmpX));
	Invalidate ();
	RedrawWindow ();
}

void CKrnlComboCtrl::Paint (CDC& dc) {
	CSize szShape;
	CRect rectCtrl;
	CMark mrkStyle;
	uvar32_64 szKernel;

	dc.FillSolidRect (m_rectText, ::GetSysColor (COLOR_WINDOW));
	mrkStyle = theApp.MarkStyles[aimActive].GetStyle();
	szKernel = mrkStyle.GetKernelSize ();

	m_rectText.DeflateRect (4, 4);
	m_rectText.left -= (m_rectText.Height() - m_rectText.Width ()) / 2;
	m_rectText.right += (m_rectText.Height() - m_rectText.Width ()) / 2;
	GetClientRect (&rectCtrl);
	mrkStyle.SetPoint (CPoint ((rectCtrl.Width () -13 )/ 2, rectCtrl.Height () / 2));
	mrkStyle.SetKernelSize ((szKernel > m_rectText.Height())?m_rectText.Height():szKernel);
	mrkStyle.PaintKernel (dc);
}
