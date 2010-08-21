// StorageFrame.cpp : implementation of the CStorageFrame class
//

#include "stdafx.h"
#include "Dias.h"
#include "DocList.h"
#include "DocPane.h"
#include "ImageWnd.h"
#include "DataWnd.h"
#include "ReportWnd.h"
#include "StorageFrame.h"
#include "StorageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStorageFrame

IMPLEMENT_DYNCREATE(CStorageFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CStorageFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CStorageFrame)
	ON_COMMAND(ID_EDIT_RENAME, OnEditRename)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RENAME, OnUpdateEditRename)
	ON_UPDATE_COMMAND_UI (ID_INDICATOR_IMG, OnUpdatePane )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStorageFrame construction/destruction


CStorageFrame::CStorageFrame ( ) {
}

CStorageFrame::~CStorageFrame ( ) {
}

BOOL CStorageFrame::OnCreateClient (LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext) {
	// STAGE 0: Creating statusbar
	UINT indicators[10];
	m_wndStatusBar.Create (this);
	m_wndStatusBar.SetIndicators (indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo (0, ID_SEPARATOR, SBPS_STRETCH | SBPS_NOBORDERS, 100);
	m_wndStatusBar.SetPaneInfo (1, ID_INDICATOR_IMG, SBPS_NORMAL, 150);
	m_wndStatusBar.SetPaneInfo (2, ID_INDICATOR_SRV, SBPS_NORMAL, 30);
	m_wndStatusBar.SetPaneInfo (3, ID_INDICATOR_REP, SBPS_NORMAL, 30);
	m_wndStatusBar.SetPaneInfo (4, ID_INDICATOR_SIZEICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (5, ID_INDICATOR_SIZE, SBPS_NOBORDERS, 30);
	m_wndStatusBar.SetPaneInfo (6, ID_INDICATOR_CMICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (7, ID_INDICATOR_CM, SBPS_NOBORDERS, 30);
	m_wndStatusBar.SetPaneInfo (8, ID_INDICATOR_BPP, SBPS_NOBORDERS, 30);
	m_wndStatusBar.SetPaneInfo (9, ID_INDICATOR_TIME, SBPS_NORMAL, 75);
	m_wndStatusBar.SetPaneText (1, "0", TRUE);


	m_barImages.Create (this, m_pView, 0);
	m_barData.Create (this, m_pView, 1);
	m_barReports.Create (this, m_pView, 2);

	REBARBANDINFO rbbi;
	rbbi.cbSize = sizeof (rbbi);
	rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_SIZE;
	rbbi.cx = 500;
	rbbi.cxMinChild = 0;
	rbbi.cyChild = 200;
	rbbi.cyMinChild = 100;
	rbbi.cyMaxChild = 500;
	rbbi.cyIntegral = 1;
	m_barShortcuts.Create (this, CCS_NODIVIDER | RBS_VARHEIGHT | RBS_BANDBORDERS | RBS_FIXEDORDER | /*RBS_VERTICALGRIPPER | *//*RBS_AUTOSIZE |*/ CCS_LEFT,
	                       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_ALIGN_LEFT);
	m_barShortcuts.SetBorders (0, 0, 0, 0);
	m_barShortcuts.AddBar (&m_barImages, theApp.LoadString (IDS_TBX_DOC_IMAGES), NULL, RBBS_VARIABLEHEIGHT | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_barShortcuts.AddBar (&m_barData, theApp.LoadString (IDS_TBX_DOC_DB), NULL, RBBS_VARIABLEHEIGHT | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_barShortcuts.AddBar (&m_barReports, theApp.LoadString (IDS_TBX_DOC_REPORTS), NULL, RBBS_VARIABLEHEIGHT | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_barShortcuts.GetReBarCtrl().SetBandInfo (0, &rbbi);
	rbbi.cx = 0;
	rbbi.cxMinChild = 0;
	m_barShortcuts.GetReBarCtrl().SetBandInfo (1, &rbbi);
	m_barShortcuts.GetReBarCtrl().SetBandInfo (2, &rbbi);


	// STAGE 1: Creating toolbars
	m_wndToolBar.CreateEx (this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_LIST);
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle (TBSTYLE_EX_DRAWDDARROWS);
	m_wndToolBar.LoadToolBar (IDR_TBX_DOC_IMG);
	m_wndToolBar.SetButtonText (0, theApp.LoadString (IDS_TBX_DOC_ADD_IMAGE));
	m_wndToolBar.SetButtonText (2, theApp.LoadString (IDS_TBX_DOC_ADD_ACQUIRE));
	m_wndToolBar.SetButtonText (3, theApp.LoadString (IDS_TBX_DOC_REMOVE));
	m_wndToolBar.SetButtonText (5, theApp.LoadString (IDS_TBX_DOC_IMPORT));
	m_wndToolBar.SetButtonText (6, theApp.LoadString (IDS_TBX_DOC_EXPORT));
	m_wndToolBar.SetButtonText (8, theApp.LoadString (IDS_TBX_DOC_UP));
	m_wndToolBar.SetButtonText (11, theApp.LoadString (IDS_TBX_DOC_ZOOM));

	m_wndToolBar.SetButtonStyle (0, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (1, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (2, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (3, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (5, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (6, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (8, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (9, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (11, TBBS_AUTOSIZE | TBBS_DROPDOWN);
	m_wndToolBar.SetButtonStyle (13, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (14, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (15, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (16, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (17, TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle (18, TBBS_AUTOSIZE);

	rbbi.cx = 34;
	rbbi.cyChild = 34;
	rbbi.cyMinChild = 34;
	rbbi.cyMaxChild = 34;
	rbbi.cyIntegral = 1;
	rbbi.cxMinChild = 34;
	m_wndReBar.Create (this, RBS_VARHEIGHT | RBS_BANDBORDERS | RBS_AUTOSIZE | RBS_DBLCLKTOGGLE |
	                   CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_BOTTOM,
	                   WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_ALIGN_BOTTOM);
	m_wndReBar.AddBar (&m_wndToolBar, NULL, NULL, RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.SetBorders (0, 0, 0, 0);
	m_wndReBar.GetReBarCtrl ().SetBandInfo (0, &rbbi);

	// STAGE 2: Creating views

/*	m_wndSplitter.CreateStatic (this, 1, 2);
	m_wndSplitter.CreateView (0, 1, RUNTIME_CLASS (CStorageView), CSize (200, 200), pContext);
	m_wndSplitter.CreateView (0, 0, RUNTIME_CLASS (CDocPane), CSize (130, 130), pContext);
	m_wndSplitter.RecalcLayout ();
	m_pView = (CStorageView*)m_wndSplitter.GetPane (0, 1);
	SetActiveView (STATIC_DOWNCAST (CView, m_wndSplitter.GetPane (0, 1)));

	m_pShortcuts = STATIC_DOWNCAST (CDocPane, m_wndSplitter.GetPane (0, 0));
//	m_pShortcuts->ModifyBarStyle (0, SEC_OBS_ANIMATESCROLL);
	m_pShortcuts->m_pView = STATIC_DOWNCAST (CStorageView, m_wndSplitter.GetPane (0, 1));

	m_barImages.Create (m_pShortcuts, m_pView, 0);
	m_barData.Create (m_pShortcuts, m_pView, 1);
	m_barReports.Create (m_pShortcuts, m_pView, 2);
	m_pShortcuts->AddBar (&m_barImages, theApp.LoadString (IDS_TBX_DOC_IMAGES));
	m_pShortcuts->AddBar (&m_barData, theApp.LoadString (IDS_TBX_DOC_DB));
	m_pShortcuts->AddBar (&m_barReports, theApp.LoadString (IDS_TBX_DOC_REPORTS));
//	m_pShortcuts->ActivateBar (0);*/

	return true;
}

void CStorageFrame::OnUpdatePane (CCmdUI *pCmdUI) {
	pCmdUI->Enable ();
}

BOOL CStorageFrame::PreCreateWindow (CREATESTRUCT& cs) {
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStorageFrame diagnostics

#ifdef _DEBUG
void CStorageFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CStorageFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

BOOL CStorageFrame::OnNotify (WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
	CRect rect1, rect2;
	CMenu menu;
	switch (LPNMHDR(lParam)->code) {
		case TBN_DROPDOWN:
			if (LPNMTOOLBAR(lParam)->iItem == ID_VIEW_ZOOM)
				menu.LoadMenu (IDR_POPUP_DOC_ZOOM);
			else
				break;
			goto trackPopup;
	}
	return CMDIChildWnd::OnNotify(wParam, lParam, pResult);
trackPopup:
	m_wndToolBar.GetWindowRect (&rect1);
	m_wndToolBar.GetToolBarCtrl ().GetRect (LPNMTOOLBAR(lParam)->iItem, &rect2);
	CMenu *pMenu = menu.GetSubMenu (0);
	pMenu->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON, rect1.left + rect2.left, rect1.top + rect2.bottom, this);
	return false;
}

CStorageDoc& CStorageFrame::GetDocument () {
	return (*(CStorageDoc*)(m_pView->GetDocument()));
}

UINT CStorageFrame::GetActiveImageNo () {
	return (aimGetSelListItem (m_barImages, false));
}
void CStorageFrame::SetActiveImageNo (UINT no) {
	aimSetSelListItem (m_barImages, no);
}
void CStorageFrame::EnsureVisibleImageNo (UINT no) {
	m_barImages.EnsureVisible (no, FALSE);
}
UINT CStorageFrame::GetActiveSurveyNo () {
	return (aimGetSelListItem (m_barData, false));
}

UINT CStorageFrame::GetActiveReportNo () {
	return (aimGetSelListItem (m_barReports, false));
}

POSITION CStorageFrame::GetFirstSelectedImageNo () {
	return (m_barImages.GetFirstSelectedItemPosition());
}

int CStorageFrame::GetNextSelectedImageNo (POSITION& pos) {
	return (m_barImages.GetNextSelectedItem(pos));
}

POSITION CStorageFrame::GetFirstSelectedSurveyNo () {
	return (m_barData.GetFirstSelectedItemPosition());
}

int CStorageFrame::GetNextSelectedSurveyNo (POSITION& pos) {
	return (m_barData.GetNextSelectedItem(pos));
}

void CStorageFrame::OnEditRename () {
	int active = m_barShortcuts.GetActiveIndex ();
	if (active == 0)
		m_barImages.OnEditRename ();
	else if (active == 1)
		m_barData.OnEditRename ();
	else
		m_barReports.OnEditRename ();
}

void CStorageFrame::OnUpdateEditRename (CCmdUI* pCmdUI) {
	pCmdUI->Enable (GetFocus () != m_pView);
}
