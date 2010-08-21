// MarkComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dias.h"
#include "MarkComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkComboDlg dialog


CMarkComboDlg::CMarkComboDlg(CWnd* pParent /*=NULL*/)
	: CAimComboDlg(pParent) {
	//{{AFX_DATA_INIT(CMarkComboDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
/*	m_ilKernels.Create (16, 16, ILC_COLOR8 | ILC_MASK, 4, 1);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_NONE), 0xFFFFFF);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_ELLIPSE), 0xFFFFFF);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_TRIANGLE), 0xFFFFFF);
	m_ilKernels.Add (theApp.LoadBitmap (IDB_MARKER_SHPSTYLE_RECTANGLE), 0xFFFFFF);*/

	m_nMenu = IDR_POPUP_MARKER_STYLE;
}


void CMarkComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CAimComboDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkComboDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMarkComboDlg, CAimComboDlg)
	//{{AFX_MSG_MAP(CMarkComboDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CD_LIST, OnItemChangedList)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkComboDlg message handlers

BOOL CMarkComboDlg::OnInitDialog () {
	CAimComboDlg::OnInitDialog();
	Update ();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMarkComboDlg::OnItemChangedList (NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if (m_ctrlList.GetSelectionMark () != -1 && aimGetSelListItem (m_ctrlList, false) != -1 &&
		aimGetSelListItem (m_ctrlList, false) != theApp.MarkStyles[aimActive].GetPos ()) {
		theApp.MarkStyles.Select (m_ctrlList.GetItemText (aimGetSelListItem (m_ctrlList, false), 0));
		theApp.Update (UPDHA_MARKSTYLE);
	}

	if (m_blLock)	return;
//	SetTimer (1, 1000, NULL);
}

void CMarkComboDlg::OnTimer (UINT nIDEvent) {
	CAimComboDlg::OnTimer(nIDEvent);
	ShowWindow (false);
	KillTimer (nIDEvent);
}

void CMarkComboDlg::Update () {
	if (!m_ctrlList.m_hWnd && !IsWindow (m_ctrlList.m_hWnd))
		return;

	m_blLock = true;
	m_ctrlList.DeleteAllItems ();
	m_ctrlList.DeleteColumn (1);
	m_ctrlList.DeleteColumn (0);
//	m_ctrlList.SetImageList (&m_ilKernels, LVSIL_SMALL);
	m_ctrlList.InsertColumn (0, theApp.LoadString (IDS_MRKSTYLE_NAME), LVCFMT_LEFT, 75, 0);
	m_ctrlList.InsertColumn (1, theApp.LoadString (IDS_MRKSTYLE_DESCR), LVCFMT_LEFT, 125, 0);

	for (uvar32_64 n = 0, cnt = theApp.MarkStyles.GetCount (); n < cnt; ++n) {
		m_ctrlList.InsertItem (n, theApp.MarkStyles[n].GetName (), 0);
		m_ctrlList.SetItemText (n, 1, theApp.MarkStyles[n].GetDescr ());
	}
	m_ctrlList.SetItemState (theApp.MarkStyles[aimActive].GetPos (), LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_ctrlList.EnsureVisible (theApp.MarkStyles[aimActive].GetPos (), false);
	m_blLock = false;

}
