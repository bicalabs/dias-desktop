// MainFrame.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Dias.h"

#include "MainFrame.h"

#include "GeomProp.h"
#include "DensProp.h"
#include "MenuCntDlg.h"
#include "Splash.h"
#include "TitlesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_GEOMSCALES, OnEditGeomScales)
	ON_COMMAND(ID_EDIT_DENSSCALES, OnEditDensScales)
	ON_COMMAND(ID_INDICATOR_GEOMSCALE, OnIndGeomScale)
	ON_COMMAND(ID_INDICATOR_DENSSCALE, OnIndDensScale)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_GEOMSCALE, OnUpdate_IndGeomScale)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DENSSCALE, OnUpdate_IndDensScale)
	ON_COMMAND_EX_RANGE(ID_TOOLS_GEOMSCALE_1, ID_TOOLS_GEOMSCALE_999, OnSelectGeomScale)
	ON_COMMAND_EX_RANGE(ID_TOOLS_DENSSCALE_1, ID_TOOLS_DENSSCALE_999, OnSelectDensScale)
	ON_COMMAND(ID_MARKER_STYLE_ADD, OnMarkerStyleAdd)
	ON_COMMAND(ID_MARKER_STYLE_DELETE, OnMarkerStyleDelete)
	ON_COMMAND(ID_MARKER_STYLE_EXPORT, OnMarkerStyleExport)
	ON_COMMAND(ID_MARKER_STYLE_IMPORT, OnMarkerStyleImport)
	ON_COMMAND(ID_MARKER_STYLE_RENAME, OnMarkerStyleRename)
	ON_COMMAND(ID_MARKER_STYLE_DUPLICATE, OnMarkerStyleDuplicate)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_TOOL,
	ID_INDICATOR_GEOMSCALEICO,
	ID_INDICATOR_GEOMSCALE,
	ID_INDICATOR_DENSSCALEICO,
	ID_INDICATOR_DENSSCALE,
	ID_INDICATOR_SAVE,
	ID_INDICATOR_PRINTICO,
	ID_INDICATOR_PRINT,
	ID_INDICATOR_PROGRAMICO,
	ID_INDICATOR_PROGRAM,
	ID_INDICATOR_IMGICO,
	ID_INDICATOR_IMG,
	ID_INDICATOR_CNLICO,
	ID_INDICATOR_CNL,
	ID_INDICATOR_PTCICO,
	ID_INDICATOR_PTC,
	ID_INDICATOR_MRKICO,
	ID_INDICATOR_MRK,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame () {
}

CMainFrame::~CMainFrame () {
}

int CMainFrame::OnCreate (LPCREATESTRUCT lpCreateStruct) {
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CSplashWnd::ShowSplashScreen(this);

	// Status Bar Creation
	m_wndStatusBar.Create (this);
	m_wndStatusBar.m_pMainFrame = this;
	m_wndStatusBar.SetIndicators (indicators, sizeof(indicators)/sizeof(UINT));
	//%%m_wndStatusBar.SetMinHeight (40);
	m_wndStatusBar.SetPaneInfo (1, ID_INDICATOR_TOOL, SBPS_NORMAL, 100);
	m_wndStatusBar.SetPaneInfo (2, ID_INDICATOR_GEOMSCALEICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (3, ID_INDICATOR_GEOMSCALE, SBPS_NOBORDERS, 100);
	m_wndStatusBar.SetPaneInfo (4, ID_INDICATOR_DENSSCALEICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (5, ID_INDICATOR_DENSSCALE, SBPS_NOBORDERS, 100);
	m_wndStatusBar.SetPaneInfo (6, ID_INDICATOR_SAVE, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (7, ID_INDICATOR_PRINTICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (8, ID_INDICATOR_PRINT, SBPS_NOBORDERS, 24);
	m_wndStatusBar.SetPaneInfo (9, ID_INDICATOR_PROGRAMICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (10, ID_INDICATOR_PROGRAM, SBPS_NOBORDERS, 100);
	m_wndStatusBar.SetPaneInfo (11, ID_INDICATOR_IMGICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (12, ID_INDICATOR_IMG, SBPS_NOBORDERS, 24);
	m_wndStatusBar.SetPaneInfo (13, ID_INDICATOR_CNLICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (14, ID_INDICATOR_CNL, SBPS_NOBORDERS, 24);
	m_wndStatusBar.SetPaneInfo (15, ID_INDICATOR_PTCICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (16, ID_INDICATOR_PTC, SBPS_NOBORDERS, 24);
	m_wndStatusBar.SetPaneInfo (17, ID_INDICATOR_MRKICO, SBPS_NOBORDERS, 16);
	m_wndStatusBar.SetPaneInfo (18, ID_INDICATOR_MRK, SBPS_NOBORDERS, 24);

	m_wndStatusBar.GetStatusBarCtrl().SetIcon (2, theApp.LoadIcon (IDI_INDICATOR_GEOMSCALE));
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (4, theApp.LoadIcon (IDI_INDICATOR_DENSSCALE));
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (9, theApp.LoadIcon (IDI_INDICATOR_PRG_STOP));
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (11, theApp.LoadIcon (IDI_INDICATOR_IMGICO));
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (13, theApp.LoadIcon (IDI_INDICATOR_CNLICO));
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (15, theApp.LoadIcon (IDI_INDICATOR_PTCICO));
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (17, theApp.LoadIcon (IDI_INDICATOR_MRKICO));

	m_wndStatusBar.SetPaneText (12, "0", TRUE);
	m_wndStatusBar.SetPaneText (14, "0", TRUE);
	m_wndStatusBar.SetPaneText (16, "0", TRUE);
	m_wndStatusBar.SetPaneText (18, "0", TRUE);

	// ToolBar Creation
	m_ilTbxStd.Create (24, 24, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_ilTbxStd.Add (theApp.LoadBitmap (IDB_TBX_STD_N), 0xFFFFFF);
	m_ilTbxHotStd.Create (24, 24, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_ilTbxHotStd.Add (theApp.LoadBitmap (IDB_TBX_STD_H), 0xFFFFFF);
	m_ilTbxDisStd.Create (24, 24, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_ilTbxDisStd.Add (theApp.LoadBitmap (IDB_TBX_STD_D), 0xFFFFFF);

	m_wndToolBar.CreateEx (this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_LIST);
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle (TBSTYLE_EX_DRAWDDARROWS);
	m_wndToolBar.LoadToolBar (IDR_MAINFRAME);
	m_wndToolBar.GetToolBarCtrl().SetImageList (&m_ilTbxStd);
	m_wndToolBar.GetToolBarCtrl().SetHotImageList (&m_ilTbxHotStd);
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList (&m_ilTbxDisStd);

	// Tool Box Creation
	m_ilTbxImg.Create (24, 24, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_ilTbxImg.Add (theApp.LoadBitmap (IDB_TBX_IMG_N), 0xFFFFFF);
	m_ilTbxHotImg.Create (24, 24, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_ilTbxHotImg.Add (theApp.LoadBitmap (IDB_TBX_IMG_H), 0xFFFFFF);
	m_ilTbxDisImg.Create (24, 24, ILC_COLOR8 | ILC_MASK, 10, 1);
	m_ilTbxDisImg.Add (theApp.LoadBitmap (IDB_TBX_IMG_N), 0xFFFFFF);

	m_wndToolBox.CreateEx (this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_LEFT);
	m_wndToolBox.GetToolBarCtrl().SetExtendedStyle (TBSTYLE_EX_DRAWDDARROWS);
	m_wndToolBox.LoadToolBar (IDR_TBX_IMAGES);
	m_wndToolBox.GetToolBarCtrl().SetImageList (&m_ilTbxImg);
	m_wndToolBox.GetToolBarCtrl().SetHotImageList (&m_ilTbxHotImg);
	m_wndToolBox.GetToolBarCtrl().SetDisabledImageList (&m_ilTbxDisImg);

	// Property Bars Creation
	m_barImages.Create (IDD_TBP_IMAGE, this);
//	m_barPointer.Create (IDD_TBP_IMAGE, this);
	m_barSelect.Create (IDD_TBP_IMAGE, this);
	m_barInfo.Create (IDD_TBP_IMAGE, this);
	m_barZoom.Create (IDD_TBP_IMAGE, this);
	m_barPatch.Create (IDD_TBP_IMAGE, this);
	m_barMeter.Create (IDD_TBP_IMAGE, this);
	m_barMarkers.Create (IDD_TBP_MRKCREATE, this);
	m_barText.Create (IDD_TBP_IMAGE, this);

	// Re Bar Creation
	m_wndReBar.Create (this);
	m_wndReBar.AddBar (&m_wndToolBar, NULL, NULL, RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);

	m_wndReBar.AddBar (&m_barImages, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
//	m_wndReBar.AddBar (&m_barPointer, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barSelect, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barInfo, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barZoom, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barPatch, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barMeter, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barMarkers, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	m_wndReBar.AddBar (&m_barText, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);

	// Re Box Creatin
	m_wndReBox.Create (this, RBS_BANDBORDERS, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT);
	m_wndReBox.AddBar (&m_wndToolBox, NULL, NULL, RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
	
/*	m_wndToolBox.CreateEx (this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_GRIPPER);
	m_wndToolBox.GetToolBarCtrl().SetExtendedStyle (TBSTYLE_EX_DRAWDDARROWS);
	m_wndToolBox.LoadToolBar (IDR_TBX_IMAGES);
	m_wndToolBox.SetWindowText (theApp.LoadString (IDS_TBX_IMG));
	m_wndToolBox.EnableDocking (CBRS_ALIGN_ANY);
	m_wndToolBox.SetBorders (2, 2, 2, 2);
	EnableDocking (CBRS_ALIGN_ANY);
	DockControlBar (&m_wndToolBox, AFX_IDW_DOCKBAR_LEFT);*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow (CREATESTRUCT& cs) {
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

void CMainFrame::Update (udword action) {
	if (action & UPDHA_MODE) {
		for (int i = 0 ; i < 8 ; ++i)
			m_wndReBar.GetReBarCtrl().ShowBand (i + 1, i == theApp.GetMode () / 100);
		m_wndReBar.GetReBarCtrl().ShowBand (theApp.GetMode () / 100 + 1, true);
	}
	if (action & UPDHA_IMAGE) {
		m_barImages.m_blLock = true;
		// #### TODO: Uncomment the following code
		if (theApp.Documents.GetCount() == 0 || 
		    theApp.Documents[aimActive].Images.GetCount() == 0 ||
		    theApp.Documents[aimActive].Images(aimActive).GetCount() == 0) {
//			m_barImages.m_ctrlName.EnableWindow (false);
//			m_barImages.m_ctrlDescr.EnableWindow (false);
//			m_barImages.m_ctrlName.SetWindowText ("");
//			m_barImages.m_ctrlDescr.SetWindowText ("");
		} else {
//			m_barImages.m_ctrlName.EnableWindow (true);
//			m_barImages.m_ctrlDescr.EnableWindow (true);
//			m_barImages.m_ctrlName.SetWindowText (theApp.Documents[aimActive].Images[aimActive].GetName ());
//			m_barImages.m_ctrlDescr.SetWindowText (theApp.Documents[aimActive].Images[aimActive].GetDescription ());
		}
		m_barImages.Update ();
		m_barImages.m_blLock = false;
	}
	if (action & UPDHA_SURVEY) {
		m_barSurveis.m_blLock = true;
		// #### TODO: Update surveis bar here
		m_barSurveis.m_blLock = false;
	}
	if (action & UPDHA_MARKSTYLE || action & UPDHA_MARK)
		m_barMarkers.Update ();
	if (action & UPDHA_DENSSCALE)
		m_wndStatusBar.SetPaneText (5, theApp.DensScales[aimActive].GetName ());
	if (action & UPDHA_GEOMSCALE)
		m_wndStatusBar.SetPaneText (3, theApp.GeomScales[aimActive].GetName ());
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::ToolbarMenu (CToolBar& wndToolbar, UINT nID) {
	int i, n, count;
	CMenu menu;
	CBitmap *bmp;
	CRect rect1, rect2;
	menu.CreatePopupMenu ();
	count = theSettings.GetSetting (nID, CSettings::sqCount);
	for (i = 0; i < count; ++i) {
		menu.AppendMenu (MF_STRING, n = theSettings.GetSetting (nID, CSettings::sqMenuID, true, (UINT)i), theSettings.GetSetting (nID, CSettings::sqName, (UINT)i));
		bmp = theApp.LoadBitmap (theSettings.GetSetting (nID, CSettings::sqBmpID, true, (UINT)i));
		menu.SetMenuItemBitmaps (n, MF_BYCOMMAND, bmp, bmp);
	}
	menu.CheckMenuRadioItem (0, count, theSettings.GetSetting (nID, CSettings::sqCurrent), MF_BYPOSITION);
	wndToolbar.GetWindowRect (&rect1);
	wndToolbar.GetToolBarCtrl ().GetRect (nID, &rect2);
	menu.TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON, rect1.left + rect2.left, rect1.top + rect2.bottom, this);
}
/*
LONG CMainFrame::OnColorChange(UINT wParam, LONG lParam) {
	theSettings.SetSetting (m_nID, lParam);
	return 0;
}
*/
void CMainFrame::OnEditGeomScales () {
	CGeomProp pageGeom;
	CPropertySheet sheetPref (theApp.LoadString (IDS_PREFERENCES));

	sheetPref.AddPage (&pageGeom);
	sheetPref.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	sheetPref.DoModal ();
}
void CMainFrame::OnEditDensScales () {
	CDensProp pageDens;
	CPropertySheet sheetPref (theApp.LoadString (IDS_PREFERENCES));

	sheetPref.AddPage (&pageDens);
	sheetPref.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	sheetPref.DoModal ();
}
void CMainFrame::OnIndGeomScale() { OnEditGeomScales (); }
void CMainFrame::OnIndDensScale() { OnEditDensScales (); }
void CMainFrame::OnUpdate_IndGeomScale(CCmdUI* pCmdUI) { pCmdUI->SetText (theApp.GeomScales[aimActive].GetName()); }
void CMainFrame::OnUpdate_IndDensScale(CCmdUI* pCmdUI) { pCmdUI->SetText (theApp.DensScales[aimActive].GetName()); }
void CMainFrame::OnSelectGeomScale (UINT nID) {	theApp.GeomScales[nID - ID_TOOLS_GEOMSCALE_1].Activate (); }
void CMainFrame::OnSelectDensScale (UINT nID) {	theApp.DensScales[nID - ID_TOOLS_DENSSCALE_1].Activate (); }

void CMainFrame::OnMarkerStyleAdd () {
	CString strText, strTitle;
	CTitlesDlg dlgTitles;
$Repeat:
	if (dlgTitles.DoModal () != IDOK)
		return;
	CMark mrkStyle = theApp.MarkStyles[aimActive].GetStyle ();
	CMarkStyle *pStyle = new CMarkStyle (dlgTitles.m_strTitle, dlgTitles.m_strDescr, mrkStyle);
	if (theApp.MarkStyles.Insert (theApp.MarkStyles[aimActive].GetPos (), *pStyle) == -1) {
		strText.LoadString (IDS_MBTEXT_COLLISION);
		strTitle.LoadString (IDS_MBTITLE_COLLISION);
		if (MessageBox (strText, strTitle, MB_YESNO | MB_ICONQUESTION) == IDYES)
			goto $Repeat;
		else
			return;
	}
	Update (UPDHA_MARKSTYLE);
}

void CMainFrame::OnMarkerStyleDelete () {
	CString strText, strTitle;
	if (theApp.MarkStyles[aimActive].GetPos () == 0) {
		strText.LoadString (IDS_MBTEXT_BUILTINDELETION);
		strTitle.LoadString (IDS_MBTITLE_ERROR);
		MessageBox (strText, strTitle, MB_OK | MB_ICONSTOP);
		return;
	}
	strText.LoadString (IDS_MBTEXT_DELETE);
	strTitle.LoadString (IDS_MBTITLE_DELETE);
	if (MessageBox (strText, strTitle, MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;
	theApp.MarkStyles.Delete (theApp.MarkStyles[aimActive].GetPos ());
	Update (UPDHA_MARKSTYLE);
}

void CMainFrame::OnMarkerStyleExport () {
}

void CMainFrame::OnMarkerStyleImport () {
}

void CMainFrame::OnMarkerStyleRename () {
	CTitlesDlg dlgTitles;
	dlgTitles.m_strTitle = theApp.MarkStyles[aimActive].GetName ();
	dlgTitles.m_strDescr = theApp.MarkStyles[aimActive].GetDescr ();
	if (dlgTitles.DoModal () != IDOK)
		return;
	CMark mrkStyle = theApp.MarkStyles[aimActive].GetStyle ();
	theApp.MarkStyles[aimActive].SetName (dlgTitles.m_strTitle);
	theApp.MarkStyles[aimActive].SetDescr (dlgTitles.m_strDescr);
	Update (UPDHA_MARKSTYLE);
}

void CMainFrame::OnMarkerStyleDuplicate () {
	CString strText, strTitle;
	CTitlesDlg dlgTitles;
	dlgTitles.m_strTitle = theApp.MarkStyles[aimActive].GetName ();
	dlgTitles.m_strDescr = theApp.MarkStyles[aimActive].GetDescr ();
$Repeat:
	if (dlgTitles.DoModal () != IDOK)
		return;
	CMark mrkStyle = theApp.MarkStyles[aimActive].GetStyle ();
	CMarkStyle *pStyle = new CMarkStyle (dlgTitles.m_strTitle, dlgTitles.m_strDescr, mrkStyle);
	if (theApp.MarkStyles.Insert (theApp.MarkStyles[aimActive].GetPos (), *pStyle) == -1) {
		strText.LoadString (IDS_MBTEXT_COLLISION);
		strTitle.LoadString (IDS_MBTITLE_COLLISION);
		if (MessageBox (strText, strTitle, MB_YESNO | MB_ICONQUESTION) == IDYES)
			goto $Repeat;
		else
			return;
	}
	Update (UPDHA_MARKSTYLE);
}
