// ShapeComboCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "ShapeComboDlg.h"
#include "ShapeComboCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShapeComboCtrl

CShapeComboCtrl::CShapeComboCtrl () {
	CAimComboCtrl::CAimComboCtrl ();
	m_pdlgCombo = new CShapeComboDlg ();
	m_pbmpNone = theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_NONE);
	m_pbmpRound = theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_ELLIPSE);
	m_pbmpCross = theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_TRIANGLE);
	m_pbmpX = theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_RECTANGLE);
	m_pbmpImage = m_pbmpNone;
	m_nSizeX = 125;
	m_nSizeY = 100;
}

CShapeComboCtrl::~CShapeComboCtrl () {
	CAimComboCtrl::~CAimComboCtrl ();
}


BEGIN_MESSAGE_MAP(CShapeComboCtrl, CAimComboCtrl)
	//{{AFX_MSG_MAP(CShapeComboCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShapeComboCtrl message handlers

int CShapeComboCtrl::OnCreate (LPCREATESTRUCT lpCreateStruct) {
	if (CAimComboCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	Update ();
	return 0;
}

void CShapeComboCtrl::Update () {
	CMark::MarkShape shp;
//	if (theApp.Documents[aimActive].Images[aimActive].Marks(aimActive).GetCount ())
//		shp = theApp.Documents[aimActive].Images[aimActive].Marks(aimActive)[0].GetShape ();
//	else
		shp = theApp.MarkStyles[aimActive].GetStyle().GetShape ();
	m_pbmpImage = (shp == CMark::shpNone) ? m_pbmpNone : (
	              (shp == CMark::shpEllipse) ? m_pbmpRound : (
	              (shp == CMark::shpTriangle) ? m_pbmpCross : m_pbmpX));
	RedrawWindow ();
}

void CShapeComboCtrl::Paint (CDC& dc) {
	CSize szShape;
	CRect rectCtrl;
	CMark mrkStyle;

	dc.FillSolidRect (m_rectText, ::GetSysColor (COLOR_WINDOW));
	mrkStyle = theApp.MarkStyles[aimActive].GetStyle();
	szShape = mrkStyle.GetShapeSize ();

	m_rectText.DeflateRect (4, 4);
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
	mrkStyle.SetPoint (CPoint ((rectCtrl.Width () -13 )/ 2, rectCtrl.Height () / 2));
	mrkStyle.SetShapeSize (CSize (m_rectText.Width () - 8, m_rectText.Height () - 8));
	mrkStyle.PaintShape (dc);
}
