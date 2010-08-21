// MarkComboCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "MarkComboDlg.h"
#include "MarkComboCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkComboCtrl

CMarkComboCtrl::CMarkComboCtrl () {
	CAimComboCtrl::CAimComboCtrl ();
	m_pdlgCombo = new CMarkComboDlg ();
	m_pbmpNone = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_NONE);
	m_pbmpRound = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_ROUND);
	m_pbmpCross = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_CROSS);
	m_pbmpX = theApp.LoadBitmap (IDB_MARKER_KRNLSTYLE_X);
	m_pbmpImage = m_pbmpNone;
	m_nSizeX = 250;
	m_nSizeY = 350;
}

CMarkComboCtrl::~CMarkComboCtrl () {
	CAimComboCtrl::~CAimComboCtrl ();
}


BEGIN_MESSAGE_MAP(CMarkComboCtrl, CAimComboCtrl)
	//{{AFX_MSG_MAP(CMarkComboCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkComboCtrl message handlers

int CMarkComboCtrl::OnCreate (LPCREATESTRUCT lpCreateStruct) {
	if (CAimComboCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	Update ();
	return 0;
}

void CMarkComboCtrl::Update () {
	CMark::MarkKernel krnl;
//	if (theApp.Documents[aimActive].Images[aimActive].Marks(aimActive).GetCount ())
//		krnl = theApp.Documents[aimActive].Images[aimActive].Marks(aimActive)[0].GetKernel ();
//	else
		krnl = theApp.MarkStyles[aimActive].GetStyle().GetKernel ();
	m_pbmpImage = (krnl == CMark::krnlNone) ? m_pbmpNone : (
	              (krnl == CMark::krnlRound) ? m_pbmpRound : (
	              (krnl == CMark::krnlPlus) ? m_pbmpCross : m_pbmpX));
	RedrawWindow ();
	m_pdlgCombo->Update ();
}

void CMarkComboCtrl::Paint (CDC& dc) {
	CSize szShape;
	CRect rectCtrl, rectLabel;
	CMark mrkStyle;
	CFont fntDeflt;
	uvar32_64 szKernel;

	dc.FillSolidRect (m_rectText, ::GetSysColor (COLOR_WINDOW));
	mrkStyle = theApp.MarkStyles[aimActive].GetStyle();
	szShape = mrkStyle.GetShapeSize ();
	szKernel = mrkStyle.GetKernelSize ();

	m_rectText.DeflateRect (4, 4);
	rectLabel = m_rectText;
	m_rectText.right -= 100;
	rectLabel.left = m_rectText.right + 1;
	m_rectText.left -= (m_rectText.Height() - m_rectText.Width ()) / 2;
	m_rectText.right += (m_rectText.Height() - m_rectText.Width ()) / 2;
	if (szShape.cx >= szShape.cy) {
		m_rectText.top += (szShape.cx - szShape.cy) / 2;
		m_rectText.bottom -= (szShape.cx - szShape.cy) / 2;
	} else {
		m_rectText.left += (szShape.cy - szShape.cx) / 2;
		m_rectText.right -= (szShape.cy - szShape.cx) / 2;
	}
	GetClientRect (&rectCtrl);
	mrkStyle.SetPoint (CPoint ((rectCtrl.Width () - 115 )/ 2, rectCtrl.Height () / 2));
	mrkStyle.SetShapeSize (CSize (m_rectText.Width () - 2, m_rectText.Height () - 2));
	mrkStyle.SetKernelSize ((szKernel > m_rectText.Height())?m_rectText.Height():szKernel);
	mrkStyle.Paint (dc);

	fntDeflt.CreatePointFont (80, "Tahoma", &dc);
	CFont *pFont = dc.SelectObject (&fntDeflt);
	dc.DrawText (theApp.MarkStyles[aimActive].GetName (), rectLabel, DT_END_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS);
	dc.SelectObject (pFont);
	fntDeflt.DeleteObject ();
}
